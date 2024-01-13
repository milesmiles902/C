/*
 * @file .cpp
 * @brief Implementation [Count number of bits to be flipped to convert to A to B]
 *
 * Worst Case Time Complexity: O(log n)
 * Space Complexity: O(1)
 */

#include <cassert>
#include <iostream>

namespace bit_manipulation{
  namespace count_bits_flip{
    /*
     * @brief The main function implements count of bits flip required
     * @param A is the given number whose bits will be flipped
     * @param B is the given target number
     * @returns total number of bits needed to be flipped to convert A to B
     */
    std::uint64_t countBitsFlip(std::int64_t A, std::int64_t B){
      int count = 0;
      A = A ^ B;
      while (A) {
        A = A & (A-1);
        count++;
      }
      return count;
    }
  }
}

static void test() {
    // A = 10, B = 20 return 4
    assert(bit_manipulation::count_bits_flip::countBitsFlip(10, 20) == 4);
    // A = 20, B = 25 return 3
    assert(bit_manipulation::count_bits_flip::countBitsFlip(20, 25) == 3);
    // A = 7, B = 10 return 3
    assert(bit_manipulation::count_bits_flip::countBitsFlip(7, 10) == 3);
    // A = 17, B = 25 return 1
    assert(bit_manipulation::count_bits_flip::countBitsFlip(17, 25) == 1);
    // A = 11, B = 8 return 2
    assert(bit_manipulation::count_bits_flip::countBitsFlip(11, 8) == 2);
    // A = 21, B = 22 return 2
    assert(bit_manipulation::count_bits_flip::countBitsFlip(21, 22) == 2);
    // A = 7, B = 786 return 5
    assert(bit_manipulation::count_bits_flip::countBitsFlip(7, 786) == 5);
    std::cout << "All test cases successfully passed!" << std::endl;
}
/**
 * @brief Main function
 * @returns 0 on exit
 */
int main() {
    test();  // run self-test implementations
    return 0;
}
