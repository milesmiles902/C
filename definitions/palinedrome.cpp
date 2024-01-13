#include <deque>
#include <fstream>
#include <iostream>
#include <string>
#include "stdlib.h"
#include <algorithm>
using namespace std;

string processor(string aString){
  int strLen = aString.length();
  string str="";
  for(int i=0;i<strLen;i++){
    str+=tolower(aString[i]);
  }
  str.erase(remove(str.begin(),str.end(), ' '),str.end());
  str.erase(remove(str.begin(),str.end(), '.'),str.end());
  str.erase(remove(str.begin(),str.end(), '?'),str.end());
  str.erase(remove(str.begin(),str.end(), '!'),str.end());
  str.erase(remove(str.begin(),str.end(), ','),str.end());
  str.erase(remove(str.begin(),str.end(), ';'),str.end());
  str.erase(remove(str.begin(),str.end(), ':'),str.end());
  str.erase(remove(str.begin(),str.end(), '#'),str.end());
  str.erase(remove(str.begin(),str.end(), '"'),str.end());
  str.erase(remove(str.begin(),str.end(), '\''),str.end());
  str.erase(remove(str.begin(),str.end(), '-'),str.end());
  str.erase(remove(str.begin(),str.end(), '('),str.end());
  str.erase(remove(str.begin(),str.end(), ')'),str.end());
  
  return str;
}

bool palchecker(string aString){
  aString=processor(aString);
  deque<char> chardeque;
  int strLen=aString.length();
  for(int i=0;i<strLen;i++){
    chardeque.push_back(aString[i]);
  }
  bool stillEqual=true;

  while(chardeque.size() > 1 && stillEqual){
    char first = chardeque.front();
    chardeque.pop_front();
    char last = chardeque.back();
    if(first!=last){
      stillEqual=false;
    }   
  }
  return stillEqual;
}

int main(){
  cout << palchecker("Radar") << endl;
  cout << palchecker("Are we note sure?");
  cout << palchecker("Barge in! Relate mere war");
  cout << palchecker("not a palindrom") << endl;
}


