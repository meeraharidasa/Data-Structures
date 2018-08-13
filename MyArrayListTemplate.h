
//
// CS251 Data Structures
// Resizable Array Template
//

#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
using namespace std; 

// This is a resizable array for elements of type Data
template <typename Data>
class MyArrayListTemplate {
    // The current maximum capacity of the array
    int maxCapacity;
    // Number of current Data elements in the array
    int size;
    // Array of the Data elements
    Data * arrayList;

public:
    MyArrayListTemplate(int initialSize);

    // Add an Data element to the end of the array and return true if successful
    bool addAtEnd(Data value);

    // puts the Data element at index in retval and returns true. returns false if no Data element at given index
    bool elementAtIndex( int index, Data & retval);

    // Add a Data element to index position in the array and return true if successful.
    bool addAtIndex(int index, Data value);

    // Remove the Data element at index position in the array and return true if successful.
    bool removeAtIndex(int index);

    // return the current size of the array (# of stored elements).
    int length();

    // return the current Capacity of the array (total size of the array).
    int capacity();

    // Substitute element at index and return true if successful
    bool replaceAtIndex(int index, Data value);

    // Search for Data and return true if element exists in the array
    bool find(Data value);

    // Print all the Data elements in the array
    void print();
};


template <typename Data>
MyArrayListTemplate<Data>::MyArrayListTemplate(int initialSize)
{
    // Add implementation here
  arrayList = new Data[initialSize];
  size = 0;
  maxCapacity = initialSize; 
}

template <typename Data>
bool MyArrayListTemplate<Data>::addAtEnd(Data value)
{
    // Add implementation here
  if(size == maxCapacity){
    Data * arrayListTemp = new Data[maxCapacity* sizeof(Data)];
    for(int i = 0; i<maxCapacity; i++){
      arrayListTemp[i] = arrayList[i];
    }

    delete [] arrayList;
    //arrayList = arrayListTemp;
    arrayList = new Data[maxCapacity *2* sizeof(Data)];
    maxCapacity *= 2;
    for(int j = 0; j<maxCapacity; j++){
      arrayList[j] = arrayListTemp[j];
    }
    delete [] arrayListTemp;
    arrayList[size] = value;
    size++;
    return true;
  }
  else{
    arrayList[size] = value;
    size++;
    return true;
  }
  return false;
}

template <typename Data>
bool MyArrayListTemplate<Data>::elementAtIndex( int index, Data & retval)
{
    // Add implementation here
  if(index < 0 || index >= size){
    return false;
  }

  retval = arrayList[index];
  return true;

    
    
}

template <typename Data>
bool MyArrayListTemplate<Data>::addAtIndex(int index, Data value)
{
    // Add implementation here
  if(index <0 || index > size){
    return false;
  }
  else if(size == maxCapacity){
    Data * arrayListTemp = new Data[maxCapacity * 2 * (sizeof(Data)) ];
    for(int i = 0; i<maxCapacity; i++){
      arrayListTemp[i] = arrayList[i];
    }
    delete [] arrayList;
    //arrayList = arrayListTemp;
    arrayList = new Data[maxCapacity *2 * (sizeof(Data))];
    maxCapacity *= 2;
    for(int j = 0; j<maxCapacity; j++){
      arrayList[j] = arrayListTemp[j];
    }
    delete [] arrayListTemp;

    for(int i = size -1; i>=index; i--){
      arrayList[i+1] = arrayList[i];
    }
    arrayList[index] = value;
    size++;
    return true;

  }
  else{
    for(int i = size - 1; i>=index; i--){
      arrayList[i+1] = arrayList[i];
    }
    arrayList[index] = value;
    size++;
    return true;
  }
  return false;
}

template <typename Data>
bool MyArrayListTemplate<Data>::removeAtIndex(int index)
{
    // Add implementation here
  if(index <0 || index >= size){
    return false;
  }
  else{
    for(int i = index +1; i<size; i++){
      arrayList[i-1] = arrayList[i];
    }
    size--;
  }
  if(size <= (0.25 * maxCapacity)){
    Data * arrayListTemp = new Data[maxCapacity* sizeof(Data)];
    for(int i = 0; i<maxCapacity; i++){
      arrayListTemp[i] = arrayList[i];
    }
    delete [] arrayList;
    //arrayList = arrayListTemp;
    arrayList = new Data[(maxCapacity / 2)* sizeof(Data)];
    maxCapacity = maxCapacity / 2;
    for(int j = 0; j<maxCapacity; j++){
      arrayList[j] = arrayListTemp[j];
    }
    delete [] arrayListTemp;

  }
  return true;
}

template <typename Data>
int MyArrayListTemplate<Data>::length()
{
    // Add implementation here
    return size;
}

template <typename Data>
int MyArrayListTemplate<Data>::capacity()
{
    // Add implementation here
  return maxCapacity;
}


template <typename Data>
bool MyArrayListTemplate<Data>::replaceAtIndex(int index, Data value)
{
    // Add implementation here
  if(index < 0 || index >= size){
    return false;
  }
  arrayList[index] = value;
  return true;
}

template <typename Data>
bool MyArrayListTemplate<Data>::find(Data value)
{
    // Add implementation here
  for(int i = 0; i<size; i++){
    if(arrayList[i] == value){
      return true;
    }
  }
  return false;
}

template <typename Data>
void MyArrayListTemplate<Data>::print()
{
    // Add implementation here
  cout<<"[";
  int i;
  for(i = 0; i<size-1; i++){
    cout <<arrayList[i];
    cout<<", ";
  }

  cout<<arrayList[i];

  cout<<"]";
}
