/*
 * @file hmmRnd.cpp
 * @Description Generate a data sequence from a hidden Markov model
 */

#include "nr3.h"
#include <csmath>
#include <iostream>

/*
 *Input:
 * d: Dimension of Data
 * k: Dimension of Latent Variable
 * n: Number of Data
 *Output:
 * X[dxn]: Data Matrix
 * model: Model Structure
*/

void hmmRnd(hmmModel &model){
  MatDoub A(d,n,rand()),E(d,n,rand()),s(d,n,rand());
  model.A=A;
  model.E=E;
  model.s=s;
}

