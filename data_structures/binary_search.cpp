/*
 * @file .cpp
 * @brief [Binary search algorithm]
 * @details
 * Binary search is a search algorithm that finds the position of a target value within a sorted array.
 * Binary search compares the target value to the middle element of the array. If they are not equal,
 * the half in which the target cannot lie is elimited and the search continues on the remaining half,
 * again taking the middle element to compare to the target value, and repeating this until the
 * target value is found. If the search ends with the remaining half being empty, the target is not 
 * in the array.
 *
 * ### Implementation
 *
 * Binary search works on sorted arrays. Binary search begins by comparing an element
 * in the middle of the array with the target value. If the target value
 * matches the element, its position in the array is returned. If the target value
 * is less than the element, the search continues in the lower half of the array.
 * If the target value is greater than the element, the search continues in 
 * the upper half of the array. By doing this, the algorithm eliminates the half
 * in which the target value cannot lie in the iteration.
 *
 * ### Complexities
 *
 * //n is the number of elements in the array
 *
 * Worst-case time complexity O(log n)
 * Best-case time complexity O(1)
 * Average time complexity O(log n)
 * Worse-case space complexity O(1)
 */

#include <algorithm> /// for std::Sort function
#include <cassert> /// for std:::assert
#include <iostream> /// for IO operations
#include <vector> /// for std:::vector

/*
 * @namespace search
 * @brief Searching algorithms
 */
namespace search {
  /*
   * @namespace binary search
   * @brief Binary search searching algorithm
   */
  namespace binary_search{
    /*
     *@brief The main function which implements binary search
     *@param arr vector to be searched in
     *@param val value to be searched
     *@returns @param int index of value in vector arr
    */
    uint64_t binarySearch(std::vector<uint64_t> arr, uint64_t val){
      uint64_t low = 0; //set the lowest point in the vector
      uint64_t high = arr.size() - 1;
      while (low <= high) {
        uint64_t m = low + (high - low) / 2; //set the pivot point
        if (val == arr[m]){
          return m;
        }
        else if (val < arr[m]) {
          high = m -1;
        } else {
            low = m + 1;
        }
      }
      return -1;
    }
  }
}

static void test1() {
  std::vector<uint64_t> arr = {{1, 3, 5, 7, 9, 8, 6, 4, 2}};
  std::sort(arr.begin(), arr.end());
  uint64_t expected_ans = 3;
  uint64_t derived_ans = search::binary_search::binarySearch(arr, 4);
  std::cout << "Test #1: ";
  assert(derived_ans == expected_ans);
  std::cout << "Passed!" << std::endl;
}

int main() {
  test1();
  return 0;
}
