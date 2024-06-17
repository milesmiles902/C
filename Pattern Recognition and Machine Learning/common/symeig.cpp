/*
 * @file symeig.cpp
 * @Description Computer eigenvalues and eigenvectors of a symmetric matrix
 * @Eqns #
 */

#include "nr3.h"
#include <csmath>
#include <iostream>

/*
 *Input:
 * S[dxd]: Input Data [Symmetric Data]
 * d: Dimensions
 * m: 0=Smallest First, 1=Largest First
 *Output:
 * V[dxd]: Output Data [Eigenvectors]
*/

void symeig(MatDoub S, int d, int m, MatDoub &V, MatDoub &A){
  int i,j;
  Symmeig s(S); 
  for(i=0;i<d;i++){
    for(j=0;j<d;j++){
      if(m) {s.sort();}
      V[i][i]=s.d[i];
    }
  }
}
