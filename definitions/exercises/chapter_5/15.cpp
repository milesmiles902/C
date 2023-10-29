#include <iostream>
#include <string>
#include <bits/stdc++.h>
using namespace std;

int min(int x, int y, int z) { return min(min(x,y),z);}

int distance(string str1, string str2,int m,int n) {
  if(m==0){
    return n;
  }
  if(n==0){
    return m;
  }
  if (str1[m-1]==str2[n-1]){
    return distance(str1,str2,m-1,n-1);
  }
  return 1+min(distance(str1,str2,m,n-1), distance(str1,str2,m-1,n), distance(str1,str2,m-1,n-1));
};

int main(){
  string str1 = "algorithm";
  string str2 = "alligator";
  
  cout << distance(str1,str2,str1.length(),str2.length());
  return 0;
}
