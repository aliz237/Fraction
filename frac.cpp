#include "frac.h"
#include <ostream>


double Fraction :: gcd(double a, double b){
  // replace this with the fastest
  // possible algorithm for gcd
  a = a<0 ? -a : a;
  // b is always > 0
  while (a != b){
    if (a > b)
      a -= b;
    else
      b -= a;
  }
  return a;
}
  
void Fraction :: simplify (double& a, double& b){
  double d = gcd(a,b);
  a /= d;
  b /= d;
}

Fraction :: Fraction (double a, double b){
  if (!b) error("Construction failed! Denominator is 0.\n");

  // Always put the negative sign in the numerator
  // Makes comparison operators and printing simpler
  if (b < 0) { b *= -1; a*= -1;}

  this->a = a;
  this->b = !a ? 1 : b;
    
  /*
   * It makes sense to force the gcd(a,b)=1
   * o.w operations on fractions may easily overflow
   * If performance is important and numbers are samall
   * this line can be commented out.
   */
  if (a && (b != 1)) simplify(this->a,this->b);
}

Fraction& Fraction :: operator - (){
  this->a *= -1;
  return *this;
}
  
Fraction& Fraction :: operator += (const Fraction& rhs){
  Fraction temp(a * rhs.b + rhs.a * b, b * rhs.b);
  *this = temp;
  return *this;
}

Fraction& Fraction :: operator *= (const Fraction& rhs){
  Fraction temp(a * rhs.a, b * rhs.b);
  return *this = temp;
}

Fraction& Fraction :: operator /= (const Fraction& rhs){
  return (*this) *= rhs.reciprocal();
}
  
Fraction& Fraction :: operator -= (const Fraction& rhs){
  Fraction temp{rhs};
  return (*this) += (- temp);
}

Fraction Fraction :: reciprocal () const {
  if (!a) error("Can't compute the reciprocal of 0\n");
  return Fraction(b,a);
}
  
std::ostream& Fraction :: print(std::ostream& o) const {
  return o << a << "/" << b;
}

Fraction operator + (const Fraction& x, const Fraction& y){
  Fraction temp{x};
  temp += y;
  return temp;
}

Fraction operator - (const Fraction& x, const Fraction& y){
  Fraction temp{x};
  temp -= y;
  return temp;
}

Fraction operator * (const Fraction& x, const Fraction& y){
  Fraction temp{x};
  return temp *= y;
}

Fraction operator / (const Fraction& x, const Fraction& y){
  if (y == 0) error("Division by 0 in operator / \n");
  Fraction temp{x};
  return temp /= y;
}
  
std::ostream& operator << (std::ostream& o, const Fraction& f){
  return f.print(o);
}
