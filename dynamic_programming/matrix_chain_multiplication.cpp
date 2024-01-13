/*
 * @file .cpp
 * @brief A function to multiple a sequence of matrices
 */

#include <climits>
#include <iostream>
using namespace std;

#define MAX 10

// Table to store solutions for already computed sub problem
int dp[MAX][MAX];

// Function to find most efficient way to multiple given sequence of matrices
int MatrixChainMultiplication(int dim[], int i, int j) {
  if (j<=i+1)
    return 0;

  int min = INT_MAX;

  //Prior Matrix
  if (dp[i][j] == 0) {
    //Take the minimum of matrices which can be split
    for (int k = i + 1; k <= j-1; k++) {
      int cost = MatrixChainMultiplication(dim, i, k);
      cost += MatrixChainMultiplication(dim, k, j);
      cost += dim[i]*dim[k]*dim[j];
      if (cost < min)
        min = cost;
    }
    dp[i][j] = min;
  }
  return dp[i][j];
}

int main(){
  int dim[] = {10, 30, 5, 60};
  int n = sizeof(dim) / sizeof(dim[0]);

  cout << "Minimum cost is " << MatrixChainMultiplication(dim, 0, n-1) << "\n";
  return 0;
}
