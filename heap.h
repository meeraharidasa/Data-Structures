#ifndef LAB3_SRC_HEAP_H_
#define LAB3_SRC_HEAP_H_

#include <cstddef>

#include <string>
#include <stdlib.h>

using namespace std; 

// generic heap that stores pairs (Key, Object)
template <typename Key, typename Object>
class Heap {
    // each heap entry stores a key, object pair
    struct HeapEntry {
        Key _key;
        Object _object;
    };

    // array wilth all the heap entries
    HeapEntry * _heap;


    // number of elements in heap
    int _last;

    // maximum space in heap before extending
    int _max;

 public:
    Heap();
    void addElement(Key key, Object object);
    Object removeMin();
    int size() { return _last; }
    Key keyAt(int i);
    Object objectAt(int i);
    Key minKey();
    Object minElement(); 
};

#define iparent(ch)(((ch)-1)/2)
#define ileft(p) (2*(p)+1)
#define iright(p) (2*(p)+2)

// Heap constructor
template <typename Key, typename Object>
Heap<Key, Object>::Heap() {
  _last = 0;
  _max = 100;
  _heap = new HeapEntry[100]; 
}

  
// add a key,object pair to the heap
template <typename Key, typename Object>
void Heap<Key, Object>::addElement(Key key, Object object) {
  HeapEntry entry; 
  entry._key = key;
  entry._object = object; 
  _heap[_last] = entry;
  _last++;
  int child = _last - 1;
  int parent = iparent(child);
  //int iterator  = _last; 
  while(child > 0){
    if(_heap[child]._key > _heap[parent]._key){
      break;
    }
    HeapEntry temp = _heap[child];
    _heap[child] = _heap[parent];
    _heap[parent] = temp;
    child = parent;
    parent = iparent(child);
    //iterator--;
 
  } 
}

// remove the minimum element from the heap. Return corresponding object.
template <typename Key, typename Object>
Object Heap<Key, Object>::removeMin() {
  Object min =  _heap[0]._object;
  _last--;
  if(_last == 0){
    return _heap[0]._object;
  }
  _heap[0] = _heap[_last];
  int parent = 0;
  int left = ileft(parent);
  int right = iright(parent);
  while(left < _last){
    int minChild = left;
    if(right < _last && (_heap[right]._key < _heap[left]._key)){
      minChild = right;
    }
    if(_heap[parent]._key < _heap[minChild]._key){
      break;
    }
    HeapEntry temp = _heap[minChild];
    _heap[minChild] = _heap[parent];
    _heap[parent] = temp;
    parent = minChild;
    left = ileft(parent);
    right = iright(parent);
  }
  return min; 
}

// return object at location
template <typename Key, typename Object>
Key Heap<Key, Object>::keyAt(int i) {
  return _heap[i]._key;
}

template <typename Key, typename Object>
Object Heap<Key, Object>::objectAt(int i) {
  return _heap[i]._object; 
}

template <typename Key, typename Object>
Key Heap<Key, Object>::minKey() {
  Key min = _heap[0]._key; 
  for(int j = 0; j<_last; j++){
    if(_heap[j]._key < min){
      min = _heap[j]._key;
    }
  }
  return min; 
}

template <typename Key, typename Object>
Object Heap<Key, Object>::minElement() {
  Object obj = _heap[0]._object;
  for(int j = 0; j<_last; j++){
    if(_heap[j]._object < obj){
      obj = _heap[j]._object;
    }
  }
  return obj;
}

#endif  // LAB3_SRC_HEAP_H_
