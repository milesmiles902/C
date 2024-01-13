#include <iostream>
#include <vector>
using namespace std;

void test1(int num){
  vector<int> vect;
  for(int i=0;i<num;i++){
    vect.push_back(i);
  }
}

int main(){
  int numruns = 10000;
  clock_t begin_t1=clock();
  for(int i=0;i<numruns;i++){
    test1(numruns);
  }
  clock_t end_t1 = clock();
  double elapsed_secs = double(end_t1-begin_t1)/CLOCKS_PER_SEC;
  cout << fixed << endl;
  cout << "push_back" << elapsed_secs << " milliseconds" << endl;

  return 0;
}
