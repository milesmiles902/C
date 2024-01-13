/*
 * @file plotgm.cpp
 * @Description Plot 2D Gaussian Mixture Model 
 */

#include "nr3.h"
#include "mgson.cpp"
#include <cmath>
#include <iostream>
#include <random>

int main(){
  int level = 64, n = 256;
  Doub minX,minY,maxX,maxY; 
  VecDoub Y(n,0.1), xind(n);
  MatDoub X(n,n); 
  
  char filename[] = "2D Gaussians"
  char xlabel[] = "X-Values"
  char ylabel[] = "Y-Values"

  for(i=0;i<n;i++){
    for(j=0;j<n;j++){
      X[i][j]=1/sqrt(2*PI())*exp(-rand()^2/(2));
      if(X[i][j]<minX) minX=X[i][j];
      if(X[i][j]>maxX) maxX=X[i][j]; 
    }
    if(i>=1) Y[i]+=Y[i-1];
  }
  minY=0.1;
  maxY=n*0.1;

  makeplott(filename, xlabel, ylabel, X, Y, minX, minY, maxX, maxY, xind);
}
