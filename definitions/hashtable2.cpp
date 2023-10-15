#include <iostream>
#include <unordered_map>
#include <string>
using namespace std;

int main(){
  unordered_map<string,string> spnumbers;
  
  spnumbers = { {"one","uno"},{"two","dos"},{"three","tres"},{"four","cuatro"},{"five","cinco"}};
  
  for(auto i=spnumbers.begin(); i!=spnumbers.end();i++){
    cout << i->first << ":";
    cout << i->second << endl;
  }
}
