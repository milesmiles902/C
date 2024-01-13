/*
 * @file lattice.cpp
 * @Description Create an undirected graph corresponding to sz lattice
 */

#include "nr3.h"
#include <csmath>
#include <iostream>

/*
 *Input:
 * sz[1xd]: Size of Lattice
 *Output:
 * A[dxd]: Adjacent Matrix of an Undirected Graph
*/

int cumprod(VecDoub sz, int n){
  if(n==1) return;
  return sz[n]*cumprod(sz[n-1]); 
}


void lattice(VecDoub sz, MatDoub &A){
  int i,j,d=sz.Size();
  
  MatDoub M(d,d);
  for(i=0;i<d;i++){
    for(j=0;j<d;j++){
      M[i][j]=sz[i]*sz[j];
    }
  }  
}

