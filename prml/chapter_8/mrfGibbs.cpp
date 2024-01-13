/*
 * @file mrfBp.cpp
 * @Description Undirected graph propagation of beliefs for MRF;
 */

#include "nr3.h"
#include <csmath>
#include <iostream>

void reverseDirection(){}

void undirectedEdge(){}

/*
 *Input:
 * A[mxn]: Data Structure of undirected graph, where edge is index
 * nodePot[kxn]: node energy
 * edgePot[kxkxm]: edge energy
 *Output:
 * nodeBel[kxn]: node belief
 * edgeBel[kxkxn]: edge belief
 * L: Variational Lower bound (Bethe Energy)
*/

void mrfBp(MatDoub A, Doub nodePot, Doub edgePot, Doub &nodeBel, VecDoub &edgeBel, VecDoub &L){
  int i,j,epoch,iter,row,col;
  row=nodePot.nrows();
  col=nodePot.cols();
  MatDoub expNodePot(row,col),expEdgePot(row,col),upperA(row,col),mu(row,2*col),in(row,col),nb(row,col);
  Doub prodmu;

  for(i=0;i<row;i++){
    for(j=0;j<col;j++){
      expNodePot[i][j]=exp(nodePot[i][j]);
      expEdgePot[i][j]=exp(edgePot[i][j]);
      if(j>=i){
        upperA[i][j]=A[i][j];
      }
    }
  }
  
  for(i=0;i<row;i++){
    for(j=0;j<col;j++){
      mu[i][j]=1/row;
    }
  }   
  
  for(i=0;i<row;i++){
    for(j=0;j<col;j++){
      nodeBel[i][j]=0;
    }
    for(j=0;j<row;j++){
      for(k=0;k<col;k++){
        edgeBel[i][j][k]=0;
      } 
    }
  }
  epoch=L.size();
  for(iter=0;iter<epoch;iter++){
    for(i=0;i<row;i++){
      for(j=0;j<col;j++){  
        if(A[i][j]!=0){
          prodmu*=mu[i][j];
        }
      }
    }
    for(i=0;i<row;i++){
      nb[i][j]=expNodePot[i][j]*prodmu;
      if(A[i][j]!=0){
        for(j=0;j<row;j++){
          for(k=0;k<col;k++){
            ep[i][j][k]=expEdgePot[i][j][k];
            norm+=ep[i][j][j]*nb[i][j]/mu[i][j];
          }
        }
      }
    }
    for(i=0;i<row;i++){
      for(j=0;j<row;j++){
        for(k=0;k<col;k++){
          mu[i][j]=ep[i][j][j] //Possible inconsistency because 3D->2D matrix;
        }
      }
    }  
  }
}

int main(){
  Int i,j,k,l,m,n,epoch;
  k=5;
  n=3;
  m=3;
  epoch=1000;
  MatDoub A(n,n),nodePot(k,n),nodeBel(k,n,0);
  VecDoub L(epoch,0);
  Doub edgePot[k][k][m], edgeBel[k][k][n];
  for(i=0;i<m;i++){
    for(j=0;j<n;j++){
      nodePot[i][j]=rand()%10;
    }
  }
  for(i=0;i<k;i++){
    for(j=0;j<k;j++){
      for(l=0;l<m;j++){
        edgePot[i][j][l]=rand()%10;
      }
    }
  }
  mrfBP(A,nodePot,edgePot,nodeBel,edgeBel,L);
}
