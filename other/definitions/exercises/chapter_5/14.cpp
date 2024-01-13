#include <iostream>
#include <array>
using namespace std;

void maxProfit(int item[], int weight[],int value[],int n){
  if(n==1) return;
  int i, count = 0;
  for(i=0;i<n-1;i++)
    if(weight[i]*value[i]<weight[i+1]*value[i+1]){
      swap(item[i],item[i+1]);
      swap(weight[i],weight[i+1]);
      swap(value[i],value[i+1]);
      count++;
    }
    if(count==0)
      return;
    maxProfit(item,weight,value,n-1);
}

int main(){
  int item[5] = {1, 2, 3, 4, 5};
  int weight[5] = {2, 3, 4, 5, 9};
  int value[5] = {3, 4, 8, 8, 10};
  int total = new int[5];
  int carry = 0, total_weight = 20;
  cout << "The order of items to steal is: " << endl;
  maxProfit(item,weight,value,5);
  for(int i=0;i<5;i++){
    total=weight[i]*value[i];
    if(total<total_weight && carry<total_weight){
      carry+=total;
      cout << "Item: " << item[i] << endl;
    }
  }
}
