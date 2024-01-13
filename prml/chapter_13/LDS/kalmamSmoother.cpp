/*
 * @file kalmanSmoother.cpp
 * @Description Kalman smoother (forward-backward algorithm for linear dynamical systems)
 * @Eqns #13.88: P = AVA+Gam
 *       #13.92: K = PC/(CPC+Sigma)
 *       #13.89: mu = Amu+K(x-CAmu)
 *       #13.90: V =(I-KC)P
 *       #13.91: c = N(x|CAmuCPC+Sigma) 
 *       #13.102: J = VA/P
 *       #13.100: mu = mu+J(mu-Amu)
 *       #13.101: V = V+JV-P)J
 *       #13.107: E[zz]=V+mu*mu
 *       #13.106: E[zz_{n-1}]=JC+mu*mu
 */

#include "nr3.h"
#include <csmath>
#include <iostream>

/*
 *Input:
 *  X[dxn]: Data Matrix
 *Output:
 *
*/

void XXX(MatDoub X, VecDoub t, int lambda){

}

