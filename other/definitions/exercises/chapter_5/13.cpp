#include <iostream>
using namespace std;

int pascalcol(int n,int k){
  int i,r=1;
  if(k>n-k) k=n-k;
  for(i=0;i<k;++i){
    r*=n-i;
    r/=i+1;
  } 
  return r;
}

void pascalrow(int n){
  int i,j;
  for(i=0;i<n;i++){
    for(j=0;j<=i;j++){
      cout << " " << pascalcol(i,j);
    }
    cout << endl;
  }
}

int main(){
  int n=10;
  pascalrow(n);
  return 0; 
}
