#include <stdio.h>
#include "simple.h"

int main(int argc, char* argv[]){
  int nFirst = first_function(1,3);
  int nSecond = second_function(2);
  int nFourth = fourth_function(4);
  int nRetValue = nFirst + nSecond + nFourth;
  return nRetValue;
}
