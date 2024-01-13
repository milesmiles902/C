/*
 * @brief Evaluate recurrence relation using [matrix exponentiation]
 * @details
 * Given the recurrence relation; evaluate the value of the nth term;
 */

namespace math{
  namespace linear_recurrence_matrix{
    template <typename T = int64_t>
    std::vector<std::vector<T>> matrix_multiplication(
    const std::vector<std::vector<T>>& _mat_a,
    const std::vector<std::vector<T>>& _mat_b, const int64_t mod = 1000000007){
      assert(_mat_a[0].size() == mat_b.size());
      std::vector<std::vector<T>> _mat_c(_mat_a.size(),
                                         std::vector<T>(_mat_b[0].size(), 0));
      for (uint32_t = 0; i < mat_a.size(); ++i) {
        for (uint32_t j = 0; j < _mat_b[0].size(); ++j){
          for(uint32_t k = 0; k< _mat_b.size(); ++k){
            _mat_c[i][j] = (_mat_c[i][j] = (_mat_c[i][j] % mod + (_mat_a[i][k] % mod * _mat_b[k][j] % mod) % mod) % mod;
          }
        }
      }
      return _mat_c;
    }

    template <typename T = int64_t>
    bool is_zero_matrix(const std::vector<std::vector<T>>& _mat){
      for(uint32_t i = 0; i<_mat.size(); ++i){
        for(uint32_t j = 0; j < _mat[i].size(); ++j){
          if (_mat[i][j] != 0) {
            return false;
          }
        } 
      }
      return true;
    }
    
    template <typename T = int64_t>
    std::vector<std::vector<T>> matrix_exponentiation(
      std::vector<std::vector<T>> _mat, uint64_t power,
      const int64_t mod = 1000000007){
      if (is_zero_matrix(_mat)){
        return _mat;
      }
      std::vector<std::vector<T>> _mat_answer(_mat.size(), std::vector<T>(_mat.size(), 0));
      for(uint32_t i = 0; i<_mat.size();++i){
        _mat_answer[i][i] = 1;
      }
      
    }
  }
}
