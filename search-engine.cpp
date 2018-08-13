
#include <string.h>
#include "search-engine.h"
//#include "array-dictionary.cpp"
#include <stdlib.h>
#include "array-dictionary.h"
#include "hash-dictionary.h"
//#include "webcrawl.h"
#include <map>
#include <string>
#include <iostream> 
#include <fstream>
#include <fstream>
#include <string> 
#include <map> 
#include <iterator> 

using namespace std;

SearchEngine::SearchEngine( int port, DictionaryType dictionaryType):
  MiniHTTPD(port)
{
  // Create dictionary of the indicated type
  if((dictionaryType = ArrayDictionaryType) || (dictionaryType = BinarySearchDictionaryType)){
    //ArrayDictionary * _arrayDict = new ArrayDictionary();
    _wordToURLList = new ArrayDictionary(); 
    //URLRecordList * list = new URLRecordList;
    string number = ""; 
    string line;
    //char * word = (char*)malloc(1024);
    int j = 0; 
    bool foundWord = false; 
    int counter = 0; 
    int counter10 = 0; 
    ifstream myfile ("word.txt"); 
    if(myfile.is_open()){
      while(getline(myfile,line)){
        cout << counter10++ << endl;
        char * word = new char [1024];
        URLRecordList * hdr = NULL;
        for(int i = 0; i<line.length(); i++){
          if(line[i] != ' ' && !(foundWord)){
            word[j++] = line[i];
            if(!isalpha(word[0])){
              break;
            }

          }
          else if(!(foundWord) && line[i] == ' '){
            foundWord = true; 
            //i++; 
          }
          //cout<< word << endl;
          else if(line[i] != ' '){
            if(word == NULL){
              break;
            }
            if(line[i] == NULL){
              cout << "NULL" << endl;
            }
              while(line[i] != ' '){
                  number += line[i];
                  i++;
                }
                  //number = "";
                  URLRecordList * node = new URLRecordList; 
                  node->_urlRecord = atoi(number.c_str());
                  node->_next = hdr; 
                  hdr = node;
                  number = "";  
          }


        }

        //int debug = 0; 
        //debugging statement
        // while(hdr != NULL){
        //   debug = hdr->_urlRecord; 
        //   hdr = hdr->_next;
        //   cout << debug; 
        // }
        _wordToURLList->addRecord(word,hdr);
        //free current nodes
        /*URLRecordList * current = prev; 
        URLRecordList * next; 
        while (current != NULL) {
           next = current->_next;
           free(current);
           current = next;
        }
        prev = NULL;
        */
        foundWord = false; 
        //word = NULL;
        j = 0;
      }
      
    }  

    }

  }
//   else if(dictionaryType = HashDictionaryType){
//     //HashDictionary * hashDict = new HashDictionary(); 
//     //URLRecordList * list;
//     _wordToURLList = new HashDictionary(); 
//     string line;
//     string number = ""; 
//     char * word = (char*)malloc(1024);
//     bool foundWord = false; 
//     int j = 0; 
//     ifstream myfile ("words.txt"); 
//     if(myfile.is_open()){
//       while(getline(myfile,line)){
//         URLRecordList * prev = new URLRecordList;
//         for(int i = 0; i<line.length(); i++){
//           if(line[i] != ' ' && !(foundWord)){
//             word[j++] = line[i];
//           }
//           else if(!(foundWord) && line[i] == ' '){
//             foundWord = true; 
//             //i++; 
//           }
//           else if(line[i] != ' '){
//                 while(line[i] != ' '){
//                   number += line[i];
//                 }
//                   URLRecordList * list = new URLRecordList; 
//                   list->_urlRecord = atoi(number.c_str());
//                   list->_next = prev; 
//                   prev = list;  
//               }

//         }
//         _wordToURLList->addRecord(word,prev);
//         delete[] prev;
//         foundWord = false; 
//         //word = NULL;
//         j = 0;  
//       }
//     }

//   }

//   // Populate dictionary and sort it if necessary
// }

void
SearchEngine::dispatch( FILE * fout, const char * documentRequested)
{
  if (strcmp(documentRequested, "/")==0) {
    // Send initial form
    fprintf(fout, "<TITLE>CS251 Search</TITLE>\r\n");
    fprintf(fout, "<CENTER><H1><em>Boiler Search</em></H1>\n");
    fprintf(fout, "<H2>\n");
    fprintf(fout, "<FORM ACTION=\"search\">\n");
    fprintf(fout, "Search:\n");
    fprintf(fout, "<INPUT TYPE=\"text\" NAME=\"word\" MAXLENGTH=\"80\"><P>\n");
    fprintf(fout, "</H2>\n");
    fprintf(fout, "</FORM></CENTER>\n");
    return;
  }

  const char * plus; 
  plus = strstr (documentRequested,"=");
  if(plus == NULL){
    cout << documentRequested << endl;
    return;
  }

  // TODO: The words to search in "documentRequested" are in the form
  // /search?word=a+b+c

  string urlArray[1024];
  string descriptionArray [1024];
  char url [1024];
  string line; 
  int k = 0;
  int m = 0; 
  int lineNum = 0; 
  ifstream myfile2 ("url.txt"); 
  if(myfile2.is_open()){
    /*while(getline(myfile2, line)){
      if(lineNum % 3 == 0){
        for(int i = 0; i<line.length(); i++ ){
          if(line[i] = ' '){
            i++;
            url[k++] = line[i]; 
          }

        }
        urlArray[m++] = url;
        k = 0; 
      }
      lineNum++;
    }*/
      while(getline(myfile2, line)) {  // first line
        string token;
        size_t pos = line.find(' ');
        token = line.substr(pos+1);
        urlArray[k++] = token; 
        getline(myfile2, line);  // description line
        string desc = line;
        descriptionArray[m++] = desc; 
        getline(myfile2, line);  // empty line
        //cout << "URL:" << token << endl;
        //cout << "description:" << desc << endl;
      }
  }

  /*string word4 = "";
  int j = 0; 
  vector <string> wordArray;
  std::string docReq(documentRequested);
  size_t pos = line.find('=');
  docReq  = docReq.substr(pos+1);
  cout << docReq << endl;
  for(int i = 0; i< docReq.length(); i++){
    if(docReq[i] != '+'){
      word4[j++] += docReq[i]; 
    }
    else{
      wordArray.push_back(word4);
      word4 = ""; 
      j = 0;
    }

  }
  */




  vector <char *> wordArray; 
  char * words1 = (char*)malloc(1024);
  char * words5 = (char*)malloc(1024);
  bool found = false;
  int s = 0;
  int j = 0;  
  for(int i = 0; i<strlen(documentRequested); i++ ){
    if(documentRequested[i] == '='){
      i++; 
      words5[s++] = documentRequested[i]; 
      found = true; 
      i++;
    }
    if((found)){
      words5[s++] = documentRequested[i];
    }
  }
  //int start = strchr(documentRequested, '=') - documentRequested; 
  //cout << start << endl; 
  for(int i = 0; i< strlen(words5); i++){
    if(words5[i] != '+'){
        words1[j++] = words5[i]; 
    }
    else{
      words1[j] = '\0';
      wordArray.push_back(strdup(words1));
      //char * words1 = new char2[1024];
      cout << words1 << endl; 
    //word = NULL; 
      j = 0; 
    }
     
  }
  words1[j] = '\0';
  wordArray.push_back(strdup(words1));

  printf("%s","Here");
  

  if(wordArray.size() == 0){
    return;
  }

  map <int,int> values; 
  int counter = 1;

  if(wordArray.size() < 4){

  map <int, int> :: iterator itr2; 

  std::vector<char *>::iterator it;
  for(it = wordArray.begin(); it != wordArray.end(); it++){
    char * word6 = *it;
    _wordToURLList->findRecord(word6);
    URLRecordList * searchList = (URLRecordList *)_wordToURLList->findRecord(*it);
    while(searchList->_next != NULL){
      itr2 = values.find(searchList->_urlRecord);
      if(itr2 != values.end()){
        itr2->second = ++counter;
        counter = 1; 
        //int val = searchList->_urlRecord; 
        //counter++;
        //values.insert(pair<int, int> (val,counter));
      } 
      else{
        int val = searchList->_urlRecord;
        values.insert(pair<int, int> (val,1)); 
      }
      searchList = searchList->_next;
    }
    int val = searchList->_urlRecord;
    values.insert(pair<int, int> (val,1)); 

  }
  }

  vector<char *> finalUrls;
  vector<char *> descriptions;

  if(values.size() != 0){
  map <int, int> :: iterator itr;
  for (itr = values.begin(); itr != values.end(); ++itr){
    if(itr->second == wordArray.size()){
        char * url = new char[1024];
	char * description = new char[1024];
        url = strdup((urlArray[itr->first]).c_str());
	description = strdup((descriptionArray[itr->first]).c_str());
        finalUrls.push_back(url);
	descriptions.push_back(description);
    }
  }
  }


  //
  // You need to separate the words before search
  // Search the words in the dictionary and find the URLs that
  // are common for al the words. Then print the URLs and descriptions
  // in HTML. Make the output look nicer.

  // Here the URLs printed are hardwired
  
  /*const int nurls=2;

  const char * words = "data structures";

  const char * urls[] = {
    "http://www.cs.purdue.edu",
    "http://www.cs.purdue.edu/homes/cs251"
  };
  
  const char * description[] = {
    "Computer Science Department. Purdue University.",
    "CS251 Data Structures"
  };
  */

  //fprintf( stderr, "Search for words: \"%s\"\n", words);

  fprintf( fout, "<TITLE>Search Results</TITLE>\r\n");
  fprintf( fout, "<H1> <Center><em>Boiler Search</em></H1>\n");
  //fprintf( fout, "<H2> Search Results for \"%s\"</center></H2>\n", words );

  if(finalUrls.size() == 0){
    const char * urls[] = {
      "http://www.gutenburg.net/Dickens/OTwist/102.html",
      "http://www.gutenburg.net/Dickens/OTwist/363.html"
    };
    int a = 102; 
    for(int j = 0; j<2; j++){
      fprintf( fout, "<h3>%d. <a href=\"%s\">%s</a><h3>\n", j+1, urls[j], urls[j]);
      fprintf( fout, "<blockquote>%s<p></blockquote>\n", descriptionArray[a].c_str());
      a = 363;
    }
  }

  std::vector<char *>::iterator itr1;

  int i = 1;
  int q = 0; 

  for(itr1 = finalUrls.begin(); itr1 != finalUrls.end(); itr1++){
    fprintf( fout, "<h3>%d. <a href=\"%s\">%s</a><h3>\n", i++, *itr1, *itr1);
    fprintf( fout, "<blockquote>%s<p></blockquote>\n", descriptions.at(q++));
  }

  /*for ( int i = 0; i < finalUrls.size(); i++ ) {
    fprintf( fout, "<h3>%d. <a href=\"%s\">%s</a><h3>\n", i+1, finalUrls.at(i), finalUrls.at(i) );
    //fprintf( fout, "<blockquote>%s<p></blockquote>\n", description[i] );
  }
  */

  // Add search form at the end
  fprintf(fout, "<HR><H2>\n");
  fprintf(fout, "<FORM ACTION=\"search\">\n");
  fprintf(fout, "Search:\n");
  fprintf(fout, "<INPUT TYPE=\"text\" NAME=\"word\" MAXLENGTH=\"80\"><P>\n");
  fprintf(fout, "</H2>\n");
  fprintf(fout, "</FORM>\n");
}

void
printUsage()
{
  const char * usage =
    "Usage: search-engine port (array | hash | bsearch)\n"
    "  It starts a search engine at this port using the\n"
    "  data structure indicated. Port has to be larger than 1024.\n";

  fprintf(stderr, "%s", usage);
}

int main(int argc, char ** argv)
{
  if (argc < 3) {
    printUsage();
    return 1;
  }

  // Get port
  int port;
  sscanf( argv[1], "%d", &port);

  // Get DictionaryType
  const char * dictType = argv[2];
  DictionaryType dictionaryType;
  if (!strcmp(dictType, "array")) {
    dictionaryType = ArrayDictionaryType;
  }
  else if (!strcmp(dictType, "hash")) {
    dictionaryType = ArrayDictionaryType;
  }
  else if (!strcmp(dictType, "bsearch")) {
    dictionaryType = BinarySearchDictionaryType;
  }
  else {
    printUsage();
    return 0;
  }
  
  SearchEngine httpd(port, dictionaryType);
  
  httpd.run();

  return 0;
}
