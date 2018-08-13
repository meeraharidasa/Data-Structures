
// Implementation of a dictionary using an array and sequential search
// The array will be dynamically resized if necessary

#include <stdlib.h>
#include "array-dictionary.h"
//#include "webcrawl.h"
#include <map>
#include <string>
#include <string.h>
#include <iostream> 
#include <fstream> 
#include <vector>
#include <algorithm> 

using namespace std; 

// Constructor
ArrayDictionary::ArrayDictionary()
{   
  // Add needed code
}

// Add a record to the dictionary. Returns false if key already exists
bool
ArrayDictionary::addRecord( KeyType key, DataType record)

{
	KeyType word = key;
	_arrayVector.push_back(std::make_pair(word,(URLRecordList *)record));

	// std::vector< pair <KeyType,DataType> >::iterator it;
	// for(it = _arrayVector.begin(); it != _arrayVector.end(); it++){
	// 	URLRecordList * list = (URLRecordList *)(it->second); 
	// 	while(list != NULL){
	// 		cout << list->_urlRecord << ' '; 
	// 		list = list->_next; 
	// 	} 
	// 	cout << endl; 
	// }

  // Add needed code
  	return true;
}

// Find a key in the dictionary and return corresponding record or NULL
DataType
ArrayDictionary::findRecord( KeyType key)
{

  // Add needed code
	std::vector< pair <KeyType,DataType> >::iterator it;
	for(it = _arrayVector.begin(); it != _arrayVector.end(); it++){
		if(strcmp(it->first,key) == 0){
			return it->second;
		}
	}
	//if(it != _arrayVector.end()){
		//return it->second; 
	//}
	

  return NULL;
}
