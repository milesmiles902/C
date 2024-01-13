/*
 * @file .cpp
 * @brief Solve the equation f(x)=0 using false position method
 *
 * @details First, multiple intervals are selected with the intervale gap provided.
 * Seperate recursive function called for every root
 * Roots are printed seperately.
 *
 * For interval [a,b] such that a<0, and b>0, then the (i+1)^th approximation by 
 * x_i+1 = a_i/b_i - b_i*f(a_i){f(b_i)-f(a_i)}
 *
 * For the next iteration, the interval is selected as:
 * [a,x] if x>0 or [x,b] if x<0. 
 */

#include <cmath>
#include <iostream>

namespace numerical_methods{
  namespace false_position{
    static float eq(float x){
      return (x*x-x);
    }
    static float regula_falsi(float x1, float x2, float y1, float y2){
      float diff = x1-x2;
      if(diff<0){
        diff = (-1)*diff;
      }
      if (diff < 0.0001){
        if (y1<0){
          y1 = -y1;
        }
        if (y2<0){
          y2=-y2;
        }
        if (y1<y2){
          return x1;
        } else{
          return x2;
        }
      }
      float x3 = 0, y3 = 0;
      x3 = x1 - (x1-x2)*(y1)/(y1-y2);
      y3 = eq(x3); 
      return regula_falsi(x2,x3,y2,y3);
    }

void printRoot(float root, const int16_t &count) {
    if (count == 1) {
        std::cout << "Your 1st root is : " << root << std::endl;
    } else if (count == 2) {
        std::cout << "Your 2nd root is : " << root << std::endl;
    } else if (count == 3) {
        std::cout << "Your 3rd root is : " << root << std::endl;
    } else {
        std::cout << "Your " << count << "th root is : " << root << std::endl;
    }
}
}  // namespace false_position
}  // namespace numerical_methods

/**
 * @brief Main function
 * @returns 0 on exit
 */
int main() {
    float a = 0, b = 0, i = 0, root = 0;
    int16_t count = 0;
    float range =
        100000;       // Range in which we have to find the root. (-range,range)
    float gap = 0.5;  // interval gap. lesser the gap more the accuracy
    a = numerical_methods::false_position::eq((-1) * range);
    i = ((-1) * range + gap);
    // while loop for selecting proper interval in provided range and with
    // provided interval gap.
    while (i <= range) {
        b = numerical_methods::false_position::eq(i);
        if (b == 0) {
            count++;
            numerical_methods::false_position::printRoot(i, count);
        }
        if (a * b < 0) {
            root = numerical_methods::false_position::regula_falsi(i - gap, i,
                                                                   a, b);
            count++;
            numerical_methods::false_position::printRoot(root, count);
        }
        a = b;
        i += gap;
    }
    return 0;
}

