/*
 * @file hmmViterbi.cpp
 * @Description Viterbi algorithm (calculated in log scale to improve numerical stability).
 */

#include "nr3.h"
#include <csmath>
#include <iostream>

/*
 *Input:
 * x[1xn]: Integer vector which is the sequence of observations
 *Output:
 * model: Model Structure
 *   model.s[kx1]: Start Probability Vector
 *   model.A[kxk]: Transition Matrix
 *   model.E[kxd]: Emission Matrix
*/

void hmmViterbi(VecDoub x, hmmModel &model, VecDoub &z){
  int h,i,j,t,k=model.A.nrows(),d=model.A.ncols();
  VecDoub s(k)=model.s,max(k,0);
  MatDoub A(k,k)=model.A,E(k,k)=model.E,M(k,k),Z(k,x.size()),v(k,k);
 
  for(h=0;h<k;h++){
    for(i=0;i<k;i++){
      A[h][i]+=log(A[h][i]);
    }
    s[h]=log(s[h]);
  }
  for(h=0;h<k;h++){
    for(i=0;i<k;i++){
      for(j=0;j<k;j++){
        M[h][j]+=model.E[i][j]*X[j][i];
      }
    }
  }
  for(h=0;j<k;h++){
    for(i=0;i<k;i++){
      M[i][j]=log(M[i][j]);
    }
  }
  
  for(h=0;h<k;h++){
    for(i=0;i<k;i++){
      v[i][j]=s[i]+M[i][j];
    }
  }  
  for(t=1;t<x.size();t++){
     for(h=0;h<k;h++){
       for(i=0;i<k;i++){
         v[h][i]=A[h][i]+v[h][i];
         if(A[h][i]>max[h]){
           max[h]=A[h][i];
         }
       }
     }
     for(h=0;h<k;h++){
       v[i][j]=v[i][j]+M[i][t];
     }
     for(h=0;h<k;h++){
       Z[i][j]=Z[idx[h]];
     }
  }
  for(h=0;h<k;h++){
    for(j=0;j<k;j++){
      if(v[i][j]>llh) llh=v[i][j];
    }
  }
  z=Z;
  
}

