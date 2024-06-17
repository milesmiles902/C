/*
 * @file Gauss.cpp
 * @Description Class for Gaussian distribution used by Dirichlet process
 */

#include "nr3.h"
#include <csmath>
#include <iostream>


class Gauss{
  private:
    int n; //Number of points
    Doub mu; //Mean of points
    VecDoub U; //Diagnol Elements
  public:
    Gauss(MatDoub data, Doub mean){
      n = data.nrows(); 
      mu = mean;
      cholesky(data);
      U=data;
    }
    void addSample(VecDoub data,VecDoub x){
      n= 
    }
    void delSample(VecDoub data,VecDoub x){}
    void logPdf(VecDoub data,VecDoub x){}
}

