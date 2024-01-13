#include <iostream>
#include <vector>
using namespace std;

int recDC(vector<int> coinValueList, int change, int knownResults[]){
  int minCOins,numCoins;
  minCoins=change;
  for(unsigned int i=0;i<coinValueList.size();i++){
    if(coinValueList[i]==change){
      knownResults[change]=1;
      return 1;
    } else if(knownResults[change]>0){
      return knownResults[change];
    }
  }
  for(unsigned int y=0;y<coinValueList.size();y++){
    if(coinValueList[y]<=change){
      numCoins=1+recDC(coinValueList,change-coinValue);
      if(numCoins<minCoins){
        minCoins = numCoins;
        knownResults[change] = minCoins;
      }
    }
  }
  return minCoins;
}

int main(){
  vector<int> coinValueList = {1,5,10,25};
  int change = 63;
  int knownResults[64]={0};
  cout<<recDC(coinValueList,change,knownResults)<<endl;
  return 0;
}
