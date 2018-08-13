#ifndef LAB3_SRC_HASH_TABLE_H_
#define LAB3_SRC_HASH_TABLE_H_

#include <string>
#include <string.h>
#include <stdlib.h>
#include <assert.h> 
#define INIT_SIZE (2048)

using std::string;

// each hash entry stores a key, object pair
template <typename Data>
struct HashTableEntry {
    string _key;
    Data _data;
    HashTableEntry * _next;
};

// this is a Hash table that maps string keys to objects of type Data
template <typename Data>
class HashTable {
 public:
        // number of buckets
        enum { TableSize = INIT_SIZE };

        // vector of the hash buckets.
        HashTableEntry<Data> ** _buckets;

        // obtain the hash code of a key
        int hash(string key);

 public:
        HashTable();

        // add a record to the hash table & returns true if key already exists.
        // substitute content if key already exists.
        bool insertItem(string key, Data data);

        // find a key in the dictionary and place in "data" the corresponding record
        // returns false if key is does not exist
        bool find(string key, Data * data);

        // removes an element in the hash table & return false if key does not exist.
        bool removeElement(string key);

        // returns the data that corresponds to this index.
        // data is initialized to 0s if the entry does not exist
        Data operator[] (string &key);
};

template <typename Data>
int HashTable<Data>::hash(string key) {
  int i = 0;
  int h = 0; 
  while(key[i]){
    h += key[i];
    i++;
  }
  return h % TableSize; 
}

template <typename Data>
HashTable<Data>::HashTable() {
  _buckets = new HashTableEntry<Data>*[TableSize];
  for(int i = 0; i< TableSize; i++){
    _buckets[i] = NULL;
  }
}

template <typename Data>
bool HashTable<Data>::insertItem(string key, Data data) {
  int h = hash(key);
  HashTableEntry<Data> * entry = _buckets[h];
  while(entry != NULL){
    if(!strcmp((entry->_key).c_str(), key.c_str())){
      entry->_data = data;
      return true;
    }
    entry = entry->_next;
  }
  HashTableEntry<Data> *entry1 = new HashTableEntry<Data>();
  entry1->_key = strdup(key.c_str());
  entry1->_data = data;
  entry1->_next = _buckets[h];
  _buckets[h] = entry1; 
  return false; 
}

template <typename Data>
bool HashTable<Data>::find(string key, Data * data) {
  int h = hash(key);
  HashTableEntry<Data> * entry = _buckets[h];
    while(entry != NULL){
      if(!strcmp((entry->_key).c_str(), key.c_str())){
	*data = entry->_data;
	return true;
      }
      entry = entry->_next;
    }
    return false;
}

template <typename Data>
Data HashTable<Data>::operator[] (string &key) {
  Data entryData;
  if(find(key, &entryData) == true){
    return entryData;
  }
  return NULL; 
}

template <typename Data>
bool HashTable<Data>::removeElement(string key) {
  int h= hash(key);
  HashTableEntry<Data> * entry = _buckets[h];
  HashTableEntry<Data> * prev = NULL;
  while(entry != NULL){
    if(!strcmp((entry->_key).c_str(), key.c_str())){
      if(prev != NULL){
	prev->_next = entry->_next;
      }
      else{
	_buckets[h] = entry->_next;
      }
      delete entry;
      return true;
    }
    prev = entry;
    entry = entry->_next;
  }
    return false;
}

template <typename Data>
class HashTableIterator {
    int _currentBucket;
    HashTableEntry<Data> *_currentEntry;
    HashTable<Data> * _hashTable;
 public:
    HashTableIterator(HashTable<Data> * hashTable);
    bool next(string &key, Data &data);
};

template <typename Data>
HashTableIterator<Data>::HashTableIterator(HashTable<Data> * hashTable) {
  _hashTable = hashTable;
  _currentEntry = NULL;
  _currentBucket = 0; 
}

template <typename Data>
bool HashTableIterator<Data>::next(string &key, Data &data) {
  int j = 0; 
  if(_currentEntry != NULL && _currentEntry->_next != NULL){
    key = _currentEntry->_next->_key;
    data = _currentEntry->_next->_data;
    _currentEntry = _currentEntry->_next;
    return true;
  }
  else{
    j = _currentBucket + 1;
    while(j < 2048 && _hashTable->_buckets[j] == NULL){
      j++;
    }
    if( j < 2048 && _hashTable->_buckets[j] !=  NULL){
      key = _hashTable->_buckets[j]->_key;
      data = _hashTable->_buckets[j]->_data;
      _currentBucket = j;
      _currentEntry = _hashTable->_buckets[j];
      return true;
    }
  }
  return false;
    
}

#endif  // LAB3_SRC_HASH_TABLE_H_
