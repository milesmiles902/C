/*
 * @file .cpp
 * @brief Compute linear regression model response y=w'*X+w0 and liklihood
 * @Eqns: 3.56-3.59
 */

#include "nr3.h"
#include <cstdlib>
#include <cmath>
#include <iostream>


void printVecDoub(VecDoub j) {
  for(int i=0;i<j.size();i++){
    std::cout << j[i] << std::endl;
  }
}

void printMatDoub(MatDoub m) {
  int i,j;
  for(i=0;i<m.nrows();i++){ 
    for(j=0;j<m.ncols();j++){
      std::cout << m[i][j] << " "; 
    } std::cout << std::endl;
  }
}
/*
 * Input:
 * X(dxn): Test Data
 * t(1xn): Test Response
 *
 * Output:
 * y(nxn): Prediction
 * sigma: Variance
 * p(1xn) likelihood of t
 */

void linRegPred(MatDoub X, MatDoub W, int row, int col, VecDoub t){
  MatDoub Xbar(row,col), XU(row,row), U(row,row), y(row,row), p(row,row), sigma(row,row);
  Doub Xmean, w0, beta;
  int i,j,k;
  w0=5;
  for(i=0;i<row;i++){
    for(j=0;j<col;j++){
      for(k=0;k<row;k++){
        XU[i][j]+=W[i][k]*X[j][k];
      }
      y[i][j]=XU[i][j]+w0;
    }
  }
  
  std::cout << "W" << std::endl;
  printMatDoub(W);
  std::cout << "w0" << std::endl;
  std::cout << w0 << std::endl;
  std::cout << "y" << std::endl;
  printMatDoub(y);
  std::cout << "X: " << std::endl;
  printMatDoub(X);
  for(i=0;i<row;i++){
    for(j=0;j<col;j++){
      Xmean+=X[i][j]/(row*col);
    }
  }
  std::cout << "Xmean: " << Xmean << std::endl;

  for(i=0;i<row;i++) for(j=0;j<col;j++)
    Xbar[i][j]=X[i][j]-Xmean;
  std::cout << "Xbar: " << std::endl;
  printMatDoub(Xbar);
  
  for(i=0;i<row;i++) for(j=0;j<col;j++)
    XU[i][j]=W[i][j]/Xbar[i][j];  
  std::cout << "XU: " << std::endl;
  printMatDoub(XU);

  for(i=0;i<row;i++) { 
    for(j=0;j<col;j++) for(k=0;k<row;k++)
    U[i][j]+=XU[i][j]*XU[k][j];
  }
  std::cout << "U: " << std::endl;
  printMatDoub(U);
  
  beta=0.2;  
  for(i=0;i<row;i++) for(j=0;j<row;j++)
    sigma[i][j]=sqrt((1+U[i][j])/beta);
  std::cout << "Sigma: " << std::endl;
  printMatDoub(sigma);
  if(y[0][0]!=0){
   for(i=0;i<row;i++) for(j=0;j<col;j++)
     p[i][j]=exp(-0.5*pow((t[i]-y[i][j])/sigma[i][j],2)+log(2*M_PI)-log(sigma[i][j]));
  }
  std::cout << "p: " <<std::endl;
  printMatDoub(p);
}

int main(){
  int row=2;
  int col=2;
  MatDoub X(row,col), W(row,col);
  VecDoub t(col);
  int i,j;
  for(i=0;i<row;i++){
    for(j=0;j<col;j++){
      X[i][j]=rand()%5;
      std::cout << "Enter your model values: ";
      cin >> W[i][j];
    } 
    t[col]=rand();
  }
  linRegPred(X,W,row,col,t);
}
