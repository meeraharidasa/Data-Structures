#include <sstream>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#define MAX_SIZE 100
using namespace std;

template <typename T>
class Stack {
  int maxCapacity = MAX_SIZE;
  int size;
  T stack[MAX_SIZE];

 public:
  Stack();
  T pop();
  bool push(T val);
  T peep();
  bool isEmpty();
  int getSize();
  string toString();
};

template<typename T>
Stack<T>::Stack(){
  size = -1; 

}

template<typename T>
T Stack<T>::pop(){
  if (!isEmpty()){
    return stack[size--];
  }
 
}

template<typename T>
bool Stack<T>::push(T val){
  if (getSize() == maxCapacity){
    return false;
  }
  size++;
  stack[size] = val;
  return true;
}

template<typename T>
T Stack<T>::peep(){
  if(!isEmpty()){
  return stack[size];
  }
}

template<typename T>
bool Stack<T>::isEmpty(){
  return (size < 0); 
}

template<typename T>
int Stack<T>::getSize(){
  return size + 1;
}

template<typename T>
string Stack<T>:: toString(){
  /*  char str[20];
  int j = 0;
  for(int i = size-1; i>=0; i--){
    str[j++] = stack[i];
  }
  str[j] = '\0';
 stringstream ss;
string s1;
ss<<str;
ss>>s1;
return s1;*/
  std::string str;
  if(size == -1){
    str = "[]";
    return str;
  }
  str += "[";
  int counter  = 0;
  for(int i: stack){
    str += std::to_string(i);
    if(counter != size){
      str += ", ";
    }
    if(counter == size){
      break;
    }
    counter++;
  }
  str += "]";
  return str; 
}
