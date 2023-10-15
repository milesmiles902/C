/*
 * @file sd2kn.cpp
 * @Description Transform a squared distance matrix to a kernel matrix.
 * The data should be already centered, i.e. H(n-1)/n; K=-(H*D*H)/2
 */

#include "nr3.h"
#include <csmath>
#include <iostream>

/*
 *Input:
 * D[nxn]: Squared Distance Matrix
 *Output:
 * K[nxn]: Kernel Matrix
*/

void sd2kn(MatDoub D){
  int i,j,xrow=D.nrows(),xcol=X.ncols();
  MatDoub K(xrow,xcol);
  Doub Dmean;
  
  for(i=0;i<xrow;i++){
    for(j=0;j<xcol;j++){
      Dmean+=D[i][j];
    }
  }
  Dmean/=(xrow*xcol);
  for(i=0;i<xrow;i++){
    for(j=0;j<xcol;j++){
      D[i][j]-=Dmean;
    }
  }
  for(i=0;i<xrow;i++){
    for(j=0;j<xcol;j++){
       K[i][j]=(D[i][j]+D[j][i])/(-4);
    }
  }
}

