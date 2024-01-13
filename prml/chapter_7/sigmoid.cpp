/*
 * @file .cpp
 * @Description Return a sigmoid function
 * @Eqns #2.199
 */

#include "nr3.h"
#include <cmath>
#include <iostream>

/*
 *Input:
 * x(dxn): Data
 *Output:
 * y(dxn): exp(-log(1+exp(-x)))
*/

void sigmoid(MatDoub X){
  int i,j,m,n;
  m=X.nrows();
  n=X.ncols();
  MatDoub y(m,n);
  std::cout << "Y: " << std::endl;
  for(i=0;i<m;i++){
    for(j=0;j<n;j++){
      y[i][j]=-(1+exp(-X[i][j]));
      std::cout << y[i][j] << " ";
    } std::cout << std::endl;
  }
}

int main(){
  Int i,j,m,n;
  n=3;
  m=3;
  MatDoub X(m,n);
  
  for(i=0;i<m;i++){
    for(j=0;j<n;j++){
      X[i][j]=rand()%10;
    }
  } 
  sigmoid(X);
}
