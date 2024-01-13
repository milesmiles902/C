/*
 * @file
 * @brief Returns the [Hamming distance]
 *
 * @details
 * To find hamming distance between two integers, we take their xor, which will
 * have a set bit iff those bits differ in the two numbers. Hence,
 * we return the number of such set bits.
 */

#include <cassert>
#include <iostream>

namespace bit_manipulation{
  namespace hamming_distance{
  uint64_t bitCount(uint64_t value){
    uint64_t count = 0;
    while (value){
      if (value & 1) {
        count++;
      }
      value >>= 1;
    }
    return count;
  }
  
  /*
   * This function returns the hamming distance between two integers.
   * @param a the first number
   * @param b the second number
   * @returns the number of bits differing between the two integers
   */
  uint64_t hamming_distance(uint64_t a, uint64_t b) { return bitCount(a^b);}

  uint64_t hamming_distance(const std::string& a, const std::string& b){
    assert(a.size() == b.size());
    size_t n = a.size();
    uint64_t count = 0;
    for (size_t i = 0; i<n;i++){
      count += (b[i] != a[i]);
    }
    return count;
  }
}
}

static void test() {
    assert(bit_manipulation::hamming_distance::hamming_distance(11, 2) == 2);
    assert(bit_manipulation::hamming_distance::hamming_distance(2, 0) == 1);
    assert(bit_manipulation::hamming_distance::hamming_distance(11, 0) == 3);

    assert(bit_manipulation::hamming_distance::hamming_distance("1101",
                                                                "1111") == 1);
    assert(bit_manipulation::hamming_distance::hamming_distance("1111",
                                                                "1111") == 0);
    assert(bit_manipulation::hamming_distance::hamming_distance("0000",
                                                                "1111") == 4);

    assert(bit_manipulation::hamming_distance::hamming_distance("alpha",
                                                                "alphb") == 1);
    assert(bit_manipulation::hamming_distance::hamming_distance("abcd",
                                                                "abcd") == 0);
    assert(bit_manipulation::hamming_distance::hamming_distance("dcba",
                                                                "abcd") == 4);
}

/**
 * @brief Main function
 * @returns 0 on exit
 */
int main() {
    test();           // execute the tests
    uint64_t a = 11;  // 1011 in binary
    uint64_t b = 2;   // 0010 in binary

    std::cout << "Hamming distance between " << a << " and " << b << " is "
              << bit_manipulation::hamming_distance::hamming_distance(a, b)
              << std::endl;
}
