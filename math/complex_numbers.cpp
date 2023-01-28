/*
 * @file .cpp
 * 
 * @brief An implementation of Complex Number as Objects
 * @details A basic implementation of Complex Number field as a class with 
 * operators overloaded to accomodate field operations
 */

#include <cassert>
#include <cmath>
#include <complex>
#include <ctime>
#include <iostream>
#include <stdexcept>

/*
 * @brief Class Complex to represent complex numbers as field
 */
class Complex {
  double re;
  double im;

  public:
    /*
     * @brief Complex Constructor which initializes our complex number.
     * @details Complex Constructor which initializes number which takes three arguments
     * @param x 'true' absolute value of complex number; 'false' if real
     * @param y 'true' complex number; 'false' if imaginary
     * @param is_polar 'false' by default. 'true' if polar coordinates
     */
    explicit Complex(double x=0.f, double y=0.f, bool is_polar=false) {
      if(!is_polar) {
        re = x;
        im = y;
        return;
      }
      re = x*std::cos(y);
      im = x*std::sin(y);
    }
    Complex(const Complex &other) : re(other.real()), im(other.imag()) {};
    double real() const { return this->re; };
    double imag() const { return this->im; };
    double abs() const { return std::sqrt(this->re*this->re + this->im*this->im); }
    double arg() const { return std::atan2(this->im, this->re); }
    Complex operator+(const Complex &other) {
      Complex result(this->re + other.re, this->im + other.im)
      return result;
    }
    Complex operator-(const Complex &other) {
      Complex result(this->re - other.re, this->im - other.im);
      return result;
    }
    Complex operator*(const Complex &other) {
      Complex result(this->re*other.re - this->im * other.im,
                     this->re * other.im + this-> im * other.re);
      return result;
    }
    Complex operator~() const {
      Complex result(this->re, -(this->im));
      return result;
    }
    Complex operator/(const Complex &other) {
      Complex result = *this * ~other;
      double denominator = 
        other.real()*other.real() + other.imag()*other.imag();
      if (denominator != 0) {
        result = Complex(result.real() / denominator,
                         result.imag() / denominator);
        return result;
      } else { 
        throw std::invalid_argument("Undefined value");
      }
    }
    const Complex &operator=(const Complex &other) {
      this->re = other.real();
      this->im = other.imag();
      return *this;
    }
    bool operator==(const Complex &a, const Complex &b) {
      return a.real() == b.real() && a.imag() == b.imag();
    }
    std::ostream &operator<<(std::ostream &os, const Complex &num) {
      os << "(" << num.real();
      if (num.imag() < 0) {
        os << " - " << -num.imag();
      } else {
        os << " + " << num.imag();
      }
      os << "i)";
      return os;
    }
    double get_rand() { return (std::rand() % 100 -50) / 100.f; }
    
}
