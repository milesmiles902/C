/**
 * @file .cpp
 * @description Implementation of [Sparse Table]
 * @details Sparse Table is a data structure which answers range queries.
 * The table ca answer queries O(logn), but the benefit is answering
 * range minimum queries (or equivalen range maximum queries). For those
 * queries it can compute the answer in O(1) time. The only drawback 
 * of the structure is immutable arrays. THis means that array cannot
 * change two queries.
 */

#include <array>
#include <cassert>
#include <iostream>

/*
 * @namespace data_structures
 * @brief Data Structures Algorithms
 */
namespace data_structures {
  /*
 * @namespace sparse_table
 * @brief Functions for Implementation of [Sparse Table]
 */*
  namespace sparse_table {
    constexpr uint32_t N = 12345;
    constexpr uint8_t M = 14;
    struct Sparse_table {
      size_t n = 0;
      std::array<int64_t, N> A = {}; //Input array to perform RMQ.
      std::array<std::Array<int64_t, N>, M> ST{}; //Sparse table storing min() values 
      std::array<int64_t, N> LOG = {}; //Where (log2(i)) are precomputed

      /*
       * @brief Builds the sparse table for computing min/max/gcd/lcm/...etc
       * for any contigous sub-segment of the array. THis is the example of
       * computing the index of the minimum value.
       * @return void
       * @complexity: O(n.log(n))
       */
      void buildST() {
        LOG[0] = -1;
        for (size_t i = 0; i < n; ++i) {
          ST[0][i] = static_cast<int64_t>(i);
          LOG[i+1] = LOG[i] + !(i & (i+1));
        }
        for (size_t j = 1; static_cast<size_t>(1 << j) <= n; ++j) {
          for (size_t i = 0; static_cast<size_t>(i + (1 << j)) <= n; ++i) {
            int64_t x = ST[j-1][i];
            int64_t y = ST[j-1][i+(1 << (j-1))];
            ST[j][i] = (A[x]<=A[y]?x:y);
          }
        }
      }
      int64_t query(int64_t l, int64_t r) {
        int64_t g = LOG[r-l+1];
        int64_t x = ST[g][l];
        int64_t y = ST[g][r-(1<<g)+1];
        return (A[x]<=A[y]?x:y);
      }
    }
  }
}
  }
}
