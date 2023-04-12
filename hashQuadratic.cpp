//hashQuadratic.cpp
//demonstrates hash table with quadratic probing
//by Nicole Benito
//11 April 2023

#include <iostream>
#include <vector>
#include <cstdlib>                    //for random numbers
#include <ctime>                      //for random numbers

using namespace std;
////////////////////////////////////////////////////////////////

class DataItem { //(could have more data)

  public:
    int iData; //data item (key)
  //--------------------------------------------------------------
  DataItem(int ii): iData(ii) //constructor
  {}
  //--------------------------------------------------------------
}; //end class DataItem
////////////////////////////////////////////////////////////////

class HashTable {

  private:
    vector < DataItem * > hashArray; //vector holds hash table
    int arraySize;
    DataItem * pNonItem; //for deleted items
  public:
    //-------------------------------------------------------------
    HashTable(int size): arraySize(size) //constructor
    {
    arraySize = size;
    hashArray.resize(arraySize); //size the vector
    for (int j = 0; j < arraySize; j++) //initialize elements
      hashArray[j] = NULL;
    pNonItem = new DataItem(-1); //deleted item key is -1
    }
  //-------------------------------------------------------------
  void displayTable()
  {
    cout << "Table: ";
    for (int j = 0; j < arraySize; j++)
    {
      if (hashArray[j] != NULL)
        cout << hashArray[j] -> iData << " ";
      else
        cout << "** ";
    }
    cout << endl;
  }
  //-------------------------------------------------------------
  int hashFunc(int key)
  {
    return key % arraySize; //hash function
  }
  //-------------------------------------------------------------

  int quadProb(int hashVal, int i)
    {
    return (hashVal + i * i) % arraySize; //function for quad. probing
    }
    
    
  //-------------------------------------------------------------
      
  void insert(DataItem * pItem) //insert a DataItem
  //(assumes table not full)
  {
    int key = pItem -> iData; //extract key
    int hashVal = hashFunc(key); //hash the key
    int i = 0;
    
      // until empty cell or -1,
    while (hashArray[hashVal] != NULL &&
      hashArray[hashVal] -> iData != -1)
    {
        i++;
        hashVal = quadProb(hashVal, i);
    }
    
    hashArray[hashVal] = pItem; //insert item
  } //end insert()

  //-------------------------------------------------------------
  DataItem * remove(int key) //remove a DataItem
  {
    int hashVal = hashFunc(key); //hash the key
    int i = 0;
      
    while (hashArray[hashVal] != NULL) //until empty cell,
    { //found the key?
      if (hashArray[hashVal] -> iData == key) {
        DataItem * pTemp = hashArray[hashVal]; //save item
        hashArray[hashVal] = pNonItem; //delete item
        return pTemp; //return item
      }
        i++;
        hashVal = quadProb(hashVal, i);     //quadratic probing!
    }
    return NULL; //can't find item
  } //end remove()

  //-------------------------------------------------------------
  DataItem * find(int key) //find item with key
  {
    int hashVal = hashFunc(key); //hash the key
    int i = 0;
    while (hashArray[hashVal] != NULL) //until empty cell,
    { //found the key?
      if (hashArray[hashVal] -> iData == key)
        return hashArray[hashVal]; //yes, return item
    i++;
    hashVal = quadProb(hashVal, i);     //quadratic probing
    }
    return NULL; //can't find item

  } //-------------------------------------------------------------
}; //end class HashTable
////////////////////////////////////////////////////////////////

int main()
{
  DataItem * pDataItem;
  int aKey, size, n, keysPerCell;
  time_t aTime;
  char choice = 'b';
  //get sizes
  cout << "Enter size of hash table: ";
  cin >> size;
  cout << "Enter initial number of items: ";    //if user enters 0, NO random items generated
  cin >> n;
  keysPerCell = 10;
  //make table
  HashTable theHashTable(size);
    
    //allows user to choose btwn randomly generated items or entering
    //their own keys. by entering 0 when asked for initial # of items,
    //a user can enter all their own keys (ex. {12, 18, 13, 2, 3, 23, 5, 15, 22}
    if (n>0)
    {
        srand(static_cast < unsigned > (time( & aTime)));
        for (int j = 0; j < n; j++) //insert data
        {
          aKey = rand() % (keysPerCell * size);
          pDataItem = new DataItem(aKey);
          theHashTable.insert(pDataItem);
        }
    }
    
  while (choice != 'x') //interact with user
  {
    theHashTable.displayTable();                    //display table before menu
    cout << "\nenter letter () for action: " <<
      "(s)how, (i)nsert, (d)elete, (f)ind or e(x)it: ";
    cin >> choice;
    switch (choice)
    {
    case 's':
    //  theHashTable.displayTable();
      break;
    case 'i':
      cout << "Enter key value to insert: ";
      cin >> aKey;
      pDataItem = new DataItem(aKey);
      theHashTable.insert(pDataItem);
      break;
    case 'd':
      cout << "Enter key value to delete: ";
      cin >> aKey;
      theHashTable.remove(aKey);
      break;
    case 'f':
      cout << "Enter key value to find: ";
      cin >> aKey;
      pDataItem = theHashTable.find(aKey);
      if (pDataItem != NULL)
        cout << "Found " << aKey << endl;
      else
        cout << "Could not find " << aKey << endl;
      break;
    case 'x':
        cout << "Exiting----> " << endl;
        break;
    default:
      cout << "Invalid entry\n";
      break;
    } //end switch

  } //end while
  return 0;
} //end main()
