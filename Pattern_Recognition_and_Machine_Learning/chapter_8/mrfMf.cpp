/*
 * @file mrfBethe.cpp
 * @Description Compute Bethe Energy: H(b)=-sum(sum(b*ln(b/P(x))));
 *              Akin to Kullbeck Leibler distance: D(b,P(x))=sum(b*ln(b/P(x)));
 *              Evaluates current work (or energy) and the work of further choices in structured trees.
 */

#include "nr3.h"
#include <csmath>
#include <iostream>

/*
 *Input:
 * A[mxn]: Data Structure
 * nodePot[struct]: node energy
 * edgePot[struct]: edge energy
 * nodeBel[struct]: node Bethe Approximation
 * edgeBel[struct]: edge Beth Approximation
 *Output:
 * edgeCor[struct]: edge correlation
*/

void mrfBethe(MatDoub A, VecDoub nodePot, VecDoub edgePot, VecDoub nodeBel, VecDoub edgeBel){

}

int main(){
  Int i,j,n,m,lamda;
  n=3;
  m=3;
  MatDoub A(m,n); //m is node, n is distance
  VecDoub nodePot(m),edgePot(m),nodeBel(m),edgeBel(,);

  for(i=0;i<m;i++){
      nodePot[i]=rand()%10;
      edgePot[i]=rand()%10;
    }
  } 
  mrfBethe(A,nodePot,edgePot,nodeBel,edgeBel);
}
