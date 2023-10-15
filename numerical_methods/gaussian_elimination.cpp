/*
 * @file .cpp
 * @brief [Gaussian Elimination Method]
 */

#include <iostream>
#include <cstdlib>

int main() {
  int mat_size,i,j,step;
  std::cout << "Matrix size: ";
  std::cin >> mat_size;
  
  double **mat = new double *[mat_size+1], **x = new double *[mat_size];
  for (i=0;i<=mat_size;i++){
    mat[i] = new double[mat_size + 1]; 
    if (i<mat_size)
      x[i] = new double[mat_size + 1];
  }
  std::cout << std::endl << "Enter the value of the matrix: " << std::endl;
  for (i=0;i<mat_size;i++){
    for (j=0;j<=mat_size;j++){
      std::cin >> mat[i][j];
    }
  }
  for (step=0;step<mat_size - 1; step++){
     for (i=step;i<mat_size -1; i++){
       double a = (mat[i+1][step] / mat[step][step]);
       
       for (j=step;j<= mat_size;j++)
         mat[i+1][j]=mat[i+1][j]-(a*mat[step][j]);
     }
  }
  std::cout << std::endl << "Matrix using Gaussian Elimination method: " << std::endl;
  for (i=0;i<mat_size;i++){
    for (j=0;j<mat_size;j++){
      x[i][j]=mat[i][j];
      std::cout << mat[i][j] << " ";
    }
    std::cout << std::endl;
  } 
  std::cout << std::end << "Value of the Gaussian Elimination method: " << std::endl;
  for (i=mat_size - 1; i >= 0; i--){
    double sum = 0;
    for (j=mat_size - 1; j>i; j--){
      x[i][j] = x[j][j] * x[i][j];
      sum = x[i][j]+sum;
    }
    if (x[i][i] == 0)
      x[i][i] = 0;
    else 
      x[i][i] = (x[i][mat_size]-sum)/(x[i][i]);
    std::cout << "x" << i << "= " << x[i][i] << std::endl;
  }
  for (i = 0; i< mat_size; i++){
    delete[] mat[i];
    if(i<mat_size)
      delete[] x[i];
  }
  delete[] mat;
  delete[] x;
}
