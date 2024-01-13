#include <iostream>
#include <string>
using namespace std;

string reverse(string toRev){
  if(toRev.size()==1){
    return toRev;
  } else {
    return reverse(toRev.substr(1,toRev.length()-1)) + toRev[0];
  }
}

int main(){
  string toRev = "Help";
  cout << reverse(toRev);
  return 0;
}
