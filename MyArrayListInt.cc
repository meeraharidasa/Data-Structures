
//
// CS251
// Implementation of a Resizable Array for int
//

#include "MyArrayListInt.h"
#include <iostream>
using namespace std; 

// Constructor to instantiate the array with a given capacity
MyArrayListInt::MyArrayListInt(int initialSize)
{
    // Add implementation here
    arrayList = new int[initialSize];
    size = 0; 
    maxCapacity = initialSize; 
}

// Add an int element to the end of the array and return true if successful
bool MyArrayListInt::addAtEnd(int value)
{
    // Add implementation here
    if(size == maxCapacity){
        int * arrayListTemp = new int[maxCapacity * 2];
        for(int i = 0; i<maxCapacity; i++){
            arrayListTemp[i] = arrayList[i];
        }
        maxCapacity *= 2;
        delete [] arrayList;

        arrayList = arrayListTemp; 
        //arrayList = arrayListTemp;
        /*arrayList = new int[maxCapacity *2];
        maxCapacity *= 2; 
        for(int j = 0; j<maxCapacity; j++){
            arrayList[j] = arrayListTemp[j];
        }
        delete [] arrayListTemp;*/
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

// puts the int element at index in retval and returns true. returns false if no int element at given index
bool MyArrayListInt::elementAtIndex( int index, int & retval)
{
    // Add implementation here
    if(index < 0 || index >= size){
        return false;
    }

    retval = arrayList[index];
    return true;
}

// Add  int element to index position in the array and return true if successful.
bool MyArrayListInt::addAtIndex(int index, int value)
{
    // Add implementation here
    if(index <0 || index > size){
        return false;
    }
    else if(size == maxCapacity){
        int * arrayListTemp = new int[maxCapacity *2 ];
        for(int i = 0; i<maxCapacity; i++){
            arrayListTemp[i] = arrayList[i];
        }
        maxCapacity *= 2; 
        delete [] arrayList;
        arrayList = arrayListTemp;
        /*arrayList = new int[maxCapacity *2];
        //maxCapacity *= 2; 
        for(int j = 0; j<maxCapacity; j++){
            arrayList[j] = arrayListTemp[j];
        }
        delete [] arrayListTemp;*/

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

// Remove the int element at index position in the array and return true if successful.
bool MyArrayListInt::removeAtIndex(int index)
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
        int * arrayListTemp = new int[maxCapacity / 2];
        for(int i = 0; i<maxCapacity/2; i++){
            arrayListTemp[i] = arrayList[i];
        }
        maxCapacity = maxCapacity / 2; 
        delete [] arrayList;
        arrayList = arrayListTemp;
        /*arrayList = new int[maxCapacity / 2];
        maxCapacity = maxCapacity / 2; 
        for(int j = 0; j<maxCapacity; j++){
            arrayList[j] = arrayListTemp[j];
        }
        delete [] arrayListTemp;*/

    }
    return true;
}

// return the current size of the array.
int MyArrayListInt::length()
{
    // Add implementation here
    return size;
}

// return the current capacity of the array .
int MyArrayListInt::capacity()
{
    // Add implementation here
    return maxCapacity;
}

// Substitute element at index and return true if successful
bool MyArrayListInt::replaceAtIndex(int index, int value)
{
    // Add implementation here
    if(index < 0 || index >= size){
        return false;
    }
        arrayList[index] = value;
        return true;
}

// Search for int and return true if element exists in the array
bool MyArrayListInt::find(int value)
{
    // Add implementation here
    for(int i = 0; i<size; i++){
        if(arrayList[i] == value){
            return true;
        }
    }
    return false;
}

// Print all the int elements in the array
void MyArrayListInt::print()
{
    cout<<"[";
    int i; 
    for(i = 0; i<size-1; i++){
        cout <<arrayList[i];
        cout<<", ";
    }

    cout<<arrayList[i]; 

    cout<<"]";
    // Add implementation here
}
