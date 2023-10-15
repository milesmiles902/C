/*
 * @file .cpp
 * @brief Computer entropy of a discrete variable
 */

/*
 * @brief Function to determine entropy of a discrete variable x
 * @param x integer vector
 * @return entropy
 */

#include <cassert>
#include <cmath>
#include <array>
#include <iostream>

template <typename T, size_t size>
float entropy(std::array<T, size> &x){
  int n = x.size();

  float average;
  int counter;
  for (int i = 0; i < n; i++){
    for(int j = i+1; j < n; j++){
      if(x[i]==x[j]) { average+=x[i]; counter++; }
    }
  }
  average/=counter;

  return (-(average)*std::log2(average));
}

int main(){
  std::cout << "Testing no entropy" << std::endl;
  std::array<int, 3> x {1, 2, 3};
  std::cout << entropy(x) << std::endl;

  std::cout << "Testing small entropy" << std::endl;
  std::array<int, 3> y {1, 2, 2};
  std::cout << entropy(y) << std::endl;

  std::cout << "Testing large array" << std::endl; 
  std::array<int, 10> z {1, 2, 3, 10, 2, 13, 2, 5, 7, 9};
  std::cout << entropy(z) << std::endl;
}
