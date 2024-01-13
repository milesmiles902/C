#include <iostream>
using namespace std;

void swap_values(int &variable1, int &variable2){
  int temp;
  temp=variable1;
  variable1=variable2;
  variable2=temp;
}

int main(){
  int first_num,second_num;
  first_num=7;
  second_num=8;

  cout << "Two numbers before sqpa function: 1)" << first_num << " 2) " << second_num << endl;
  swap_values(first_num,second_num);
  cout << "The numbers after swap function: 1)" << first_num << " 2) " << second_num << endl;
  
  return 0;
}
