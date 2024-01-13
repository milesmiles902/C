/*
 * @file .cpp
 * @brief log(Probability) Density - Wishart Distribution
 */

#include <iostream>
#include <cstdlib>
#include <cmath>
#include "nr3.h"
#include "logMvGamma.cpp"

void subMatrix(MatDoub mat, MatDoub temp, int p, int q, int n){
  int i,j,row,col=0;
  for (row;row<n;row++){
    for(col=0;col<n;col++){
      if(row!=p&&col !=q){
        temp[i][j++]=mat[row][col];
        if(j==n-1){
          j=0;
          i++;
        }
      }
    }
  }
}

int determinant(MatDoub matrix, int n){
  int d,row,sign;
  d=0;
  row=matrix.nrows();
  MatDoub temp(row,row);
  if (row==1){
    return matrix[0][0];
  }
  if (row==2){
    return (matrix[0][0]*matrix[1][1])-(matrix[0][1]*matrix[1][0]);
  } 
  sign=1;
  for(int i=0;i<n;i++){
    subMatrix(matrix,temp,0,i,n);
    d+=sign*matrix[0][i]*determinant(temp, n-1);
    sign=-sign;
  }
  return d;
}
void logWishart(MatDoub sigma, MatDoub W, MatDoub v, Doub &y){
  int i,d,B; 
  MatDoub logGam(1,1),v2(1,1);
  v2[0][0]=v[0][0]*0.5;
  logMvGamma(v,d,logGam);
  d = sigma.nrows();
  B=-0.5*log(determinant(W, d))-v[0][0]*d*log(2)-logGam[0][0];
  y=B+0.5*(v[0][0]-d-1)*log(determinant(sigma,d));
  for(i=0;i<d;i++){
    y-=0.5*W[i][i]/sigma[i][i];
  }
}

int main(){
  Int i,j,d;
  Doub y;
  d=2;
  MatDoub sigma(d,d),sigma2(d,d), W(d,d), v(1,1);
  v[0][0]=2;
  for(i=0;i<d;i++){
    for(j=0;j<d;j++){
      sigma[i][j] = rand() % 4;
      W[i][j] = rand() % 4;
    }
  }
  for(i=0;i<d;i++){
    for(j=0;j<d;j++){
      sigma2[i][j]=sigma[i][j]*sigma[j][i];
    }
  }
  logWishart(sigma2,W,v,y);
  std::cout << y << std::endl;
}
