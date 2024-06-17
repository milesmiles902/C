#include <iostream>
#include "nr3.h"

void printVector(VecDoub y){
  for(int i=0;i<y.size();i++){
    std::cout << y[i] << " ";
  } std::cout << std::endl;
}

void printMatrix(MatDoub Y){
  for(int i=0;i<Y.nrows();i++){
    for(int j=0;j<Y.ncols();j++){
      std::cout << Y[i][j] << " ";
    }
    std::cout << std::endl;
  }
}
