/**
 * @file
 * @brief This program calculates GCD of n numbers by division
 */

#include <iostream>

int gcd(int *a, int n){
  int j = 1;
  int gcd = a[0];
  while (j<n){
    if (a[j] % gcd == 0)
      j++;
    else
      gcd = a[j] % gcd;
  }
  return gcd;
}
int main(){
  int n;
  std::cout << "Enter value of n:" << std::endl;
  std::cin >> n;
  int *a = new int[n];
  int i;
  std::cout << "Enter the n numbers:" << std::endl;
  for (i = 0; i<n;i++) std::cin >> a[i];
 
  std::cout << "GCD of entered n numbers:" << gcd(a, n) << std::endl;
  
  delete[] a;
  return 0;
}
