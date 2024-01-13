//This program creates a simulation of hot potato.

#include <iostream>
#include <queue>
#include <string>
#include <cmath>

using namespace std;

void radixsort(int radixArray[], int num) {
  queue<int> radixbins[10];
  int max=3;
  int currentMagnitude=0;

  while (currentMagnitude < max) { 
    for (int i = 0; i < num; i++) {
      int mod=pow(10,currentMagnitude);
      int pos = radixArray[i];
      int digitValue=static_cast<int>((pos/mod)%10);
      radixbins[digitValue].push(num);
    }
    for(int i=0;i<num;i++){
      for(int k=0;k<10;k++){
        while(!radixbins[k].empty()){
          int temp=radixbins[k].front();
          radixArray[i]=temp;
          radixbins[k].pop();
        }
      }
    }
  currentMagnitude++;
  }
}

int main() {
    int s[] = {222, 333, 555, 444, 333, 666};
    for(int i=0;i<6;i++){
      cout << s[i] << endl;
    }
    return 0;
}

