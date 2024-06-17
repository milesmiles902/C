/*
 * @file sub.cpp
 * @Description sub(A,i,j,k) = A(i;j;k)
 */

#include "nr3.h"
#include <cmath>
#include <iostream>


/*
 *Input:
 * A[dxdxd]: Input data
 * varargin: Input
 *Output:
 * B: Output Value
*/

void sub(MatDoub3D A, VecDoub varargin, int &B){
  return A[varargin[0]][varargin[1]][varargin[2]];
}
