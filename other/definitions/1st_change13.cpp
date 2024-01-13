#include <iostream>
#include <vector>
using namespace std;

int dpMakeChange(vector<int> coinValueList, int change, vector<int> minCoins){
  for(int cents = 0;cents<change+1;cents++){
    int coinCount = cents;
    for(int j:coinValueList){
      if(j<=cents){
        if(minCoins[cents-j]+1<coinCount){
          coinCount = minCoins[cents-j]+1;
        }
      }
    }
    minCoins[cents]=coinCount;
  }
  return minCoins[change];
}

int main(){
  vector<int> coinValueList = {1,5,10,25};
  int change = 63;
  vector<int> minCoins(64,0);
  cout << dpMakeChange(coinValueList, change, minCoins) << endl;
  return 0;
}
