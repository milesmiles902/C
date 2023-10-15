#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int recMC_greedy(vector<int> coinValueList, int change){
  if(change==0){
    return 0;
  } else {
    int cur_max=*max_element(coinValueList.begin(),coinValueList.end());
    int count=int(change/cur_max);
    coinValueList.erase(std::remove(coinValueList.begin(),coinValueList.end(),cur_max),coinValueList.end());
    return count + recMC_greedy(coinValueList,change-cur_max*count);
  }
}

int main(){
  int arr2[] ={1,5,10,25};
  vector<int> coinValueList(arr2,arr2 + (sizeof(arr2)/sizeof(arr2[0])));
  cout<<recMC_greedy(coinValueList,63)<<endl;
  return 0;
}
