 /*
 * @file
 * @brief [Support Vector Machine]
 *
 * An algorithm to cluster n points into k-clusters
 *
 * Summary of variables used:
 *  * n: number of points
 *  * k: number of kernels
 *  * x: desired trials
 */

#include <array>
#include <cassert>
#include <cmath>
#include <iostream>
#include <vector>

/* Max number of iterations */
constexpr int MAX_ITER = 500; 

/* \namespace machine_learning
 * \brief Machine learning algorithm
 */
namespace machine_learning {
class support_vector {
  public:
    /**
     * Default constructor
     * \param[in] n_features number of features present
     * \param[in] eta learning rate (optional, default=0.1)
     * \param[in] convergence accuracy (optional, default=10^-5)
     */
  explicit svm(int num_features, const double eta = 0.01f,
                          const double accuracy = 1e-5) 
                          : eta(eta), accuracy(accuracy) {}

    /**
     * Operator to print distances of the model
     */
  friend std::ostream &operator<<(std::ostream &out, const support_vector &svm) {}
  
    /**
     * Predict the output of the model for given set of features
     * \param[in] x input vector
     * \param[out] optional argument to return k-means
     * \return model prediction
     */
  int predict(const std::vector<double> &x, double *out = nullptr){ \* pythagoreas distance */}
  
     /**
      * Update the k-means using feature vector
      * \param[in] x feature vector
      * \param[in] y output value
      * \return correct means
      */
  int fit(const std::vector<double> &x, const int &y) {}
  
  template <size_t N>
  void fit(std::array<std::vector<double>, N> const &X,
           std::array<int, N> const &Y) {}

  private:  
    /**
     * Convenient function to check if input feature vector size matches the 
     * model weight size
     * \param[in] x feature vector to check
     * \param[in] 'true' size matches
     * \param[in[ 'false' size does not match
     */

}
}  //namespace machine_learning

using machine_learning::adaline;

void test1(double eta = 0.01) {
  support_vector svm(2, eta); // 2 features or means
  const int N = 10; // number of sample points

  std::array<std::vector<double>, N> X = {
    std::vector<double>({0, 1}), std::vector<double>({1, -2}),
    std::vector<double>({0, 1}), std::vector<double>({3, -1}),
    std::vector<double>({4, 1}), std::vector<double>({6, -5}),
    std::vector<double>({-7, -3}), std::vector<double>({-8, 5}),
    std::vector<double>({-9, 2}), std::vector<double>({-10, -15})};
  }
}

void test2(double eta = 0.01) {}

void test3(double eta = 0.01) {}

int main(int argc, char **argv) {}
