/*
 * binPlot.cpp
 * Description: Binary classification. Section 4.1.1
 *
 */

#include "nr3.h"
#include "psplot.h"
#include <cmath>
#include <iostream>

void makeplot(char filename[], char xlabel[], char ylabel[], MatDoub X, VecDoub Y, Doub minX, Doub minY, Doub maxX, Doub maxY, VecDoub xind){
  int i;
  PSpage pg(filename);
  PSplot plot1(pg,100.,500.,100.,500.);
  plot1.setlimits(0.,5.,0.,5.);
  plot1.frame();
  plot1.autoscales();
  plot1.xlabel(xlabel);
  plot1.ylabel(ylabel);
  plot1.lineplot(xind,Y);
  char dash1[]="2 4";
  plot1.setdash(dash1); 
  for(i=0;i<X.ncols();i++) 
    plot1.pointsymbol(X[0][i],X[1][i],72.,16.);
  char font1[]="dingbat 72";
  plot1.label(font1,1.1,exp(-0.5));
  pg.close();
  pg.display();
}

void binPlot(MatDoub X, VecDoub w){
  int i,j,n;
  Doub minX,minY,maxX,maxY;
  n=X.ncols();
  VecDoub xind(n),y(n);
  
  minX=0;
  minY=0;
  maxX=0;
  maxY=0;
  for(i=0;i<n;i++){
    y[i]=w[0]*X[0][i]+w[1]*X[1][i]+w[2];
    xind[i]=i;
    if(X[0][i]<=minY) minX=X[0][i];
    else if(X[0][i]>=maxY) maxX=X[0][i];    
    if(X[1][i]<=minY) minY=X[1][i];
    else if(X[1][i]>=maxY) maxY=X[1][i];        
  }
  std::cout << "X: " << std::endl;
  for(i=0;i<n;i++){
    std::cout << "(" << X[0][i] << "," << X[1][i] << ")" << std::endl;
  }   

  std::cout << "w: " << std::endl;
  for(i=0;i<w.size();i++){
      std::cout << w[i] << " ";
  } std::cout << std::endl;

  std::cout << "minX: " << minX << std::endl;
  std::cout << "maxX: " << maxX << std::endl;
  std::cout << "minY: " << minY << std::endl;
  std::cout << "maxY: " << maxY << std::endl;

  char filename[] = "binPlot.ps";
  char xlabel[] = "x-values";
  char ylabel[] = "y-values";       
  makeplot(filename, xlabel, ylabel, X, y, minX, minY, maxX, maxY, xind);
}

int main(){
  int i,j,n=5;
  VecDoub t(3);
  MatDoub X(2,n);
  
  for(i=0;i<n;i++){
      X[0][i]=rand()%5;
      X[1][i]=rand()%5;
    if(i<3)
      t[i]=rand()%3;
  }

  binPlot(X,t);
}
