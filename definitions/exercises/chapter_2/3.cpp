#include <iostream>
#include <vector>
#include <unordered_map>
#include <ctime>
using namespace std;

int main(){
  for(int a=10000;a<100001;a=a+20000){
    vector<int> avector;
    for(int i=0;i<a;i++){
      avector.push_back(i);
    }
    clock_t begin = clock();
    for(int i=0;i<a;i++){
      avector.erase (avector.begin());
    }
    clock_t end = clock();
    double elapsed_secs=double(end-begin)/CLOCKS_PER_SEC;
   
    unordered_map<int,int> y;
    for(int j=0;j<a;j++){
      y[j]=NULL;
    }
    clock_t begin_ht=clock();
    for(int j=0;j<a;j++){
      y.erase(j);
    }
    clock_t end_ht=clock();
    double elapsed_secs_ht = double(end_ht-begin_ht)/CLOCKS_PER_SEC;

    cout << a << "\t" << elapsed_secs_ht << "\t" << elapsed_secs_ht << endl;
  }
  return 0;
}
