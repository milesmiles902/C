/*
 * @file .cpp
 * @brief Implementation to [count number of set bits of a number[
 * @details We are given an integer number. We need to calculate the number of set bits
 * in it.
 *
 * A binary number consists of two digits. They are 0 & 1. Digit 1 is known as 
 * set bit in computer terms.
 * Worst case time complexity: O(log n)
 * Space complexity: O(1)
 */

#include <cassert>
#include <iostream>

namespace bit_manipulation{
  namespace count_of_set_bits{
    std::uint64_t countSetBits(std::int64_t n){
      int count = 0;
      while (n != 0){
        ++count;
        n = (n&(n-1));
      }
      return count;
    }
  }
}

static void test(){
  assert(bit_manipulation::count_of_set_bits::countSetBits(4) == 1);
  assert(bit_manipulation::count_of_set_bits::countSetBits(6) == 2);
}

int main(){
  test();
  return 0;
}
