#include <iostream>
#include <string>
#include <algorithm>
#include <cctype>
using namespace std;

void testEqual(bool a, bool b){
    if (a == b){
        cout << "PASS" << endl;
    }
    else{
        cout << "Failed" << endl;
    }
}

string removeWhite(string s) {
    int i=0,j=0;
    while(s[i]){
      if(s[i]!=' ')
      s[j++]=s[i];
      i++;
    }
    s[j]='\0';
    return s;
}

bool isPal(string s) {
    for(int i=0;i<s.size()/2;i++){
      if(s[i]!=s[s.size()-i]){
        return false;
      }
    }    
}

int main(){
    testEqual(isPal(removeWhite("x")),true);
    testEqual(isPal(removeWhite("radar")),true);
    testEqual(isPal(removeWhite("hello")),false);
    testEqual(isPal(removeWhite("")),true);
    testEqual(isPal(removeWhite("hannah")),true);
    testEqual(isPal(removeWhite("madam i'm adam")),true);

    return 0;
}
