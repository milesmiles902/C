/*
 * @file .cpp
 * @brief Compute logarithm of multivariate Gamma Function 
 * Probability density function of the Wishart and inverse Wishart distributions.
 * Gamma_d(x) = pi^(d(d-1)/4) Gamma(x+(1-j)/2)
 * log(Gamma_d(x)) = d(d-1)/4 log (pi) + sum(log(Gamma(x+(1-j)/2)))
 */

#include <cmath>
#include <iostream>
#include "nr3.h"

using namespace std;

void logMvGamma(MatDoub x, int d, MatDoub &y){
  int i,j,k;
  
  for(i=0;i<y.nrows();i++){
    for(j=0;j<y.ncols();j++){
      y[i][j]=d*(d-1)/4*log(M_PI);
    }
  }
  for(k=1;k<=d;k++){
    for(i=0;i<x.nrows();i++){
      for(j=0;j<x.ncols();j++){
        y[i][j]+=lgamma(x[i][j]+(1-k)/2);
      }
    }
  }  
}
/*
int main(){
  MatDoub x(5,5), y(5,5);
  int d=2;
  for (int i=0;i<x.nrows();i++){
    for (int j=0;j<x.ncols();j++){
      x[i][j]=rand();
    }
  }
  logMvGamma(x,d,y);
  for (int i=0;i<y.nrows();i++){
    for (int j=0;j<y.ncols();j++){
      cout << y[i][j] << " ";
    }
    cout << endl;
  }
} 
*/
