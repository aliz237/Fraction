#ifndef FRAC_H
#define FRAC_H

#include <string>

struct Bad_frac{
  std::string err_name;
  Bad_frac(const char* n) : err_name{n} {}
  Bad_frac(std::string n) : err_name{n} {}
};

inline void error(const char* err_name){ throw Bad_frac(err_name);}

class Fraction{
  int a,b;

  int gcd(int a, int b);
  void simplify (int& a, int& b);
  
public:

  Fraction (int a=0, int b=1);
  Fraction reciprocal () const;  
  std::ostream& print(std::ostream& o) const;
  Fraction& operator - ();
  Fraction& operator += (const Fraction& rhs);
  Fraction& operator *= (const Fraction& rhs);
  Fraction& operator /= (const Fraction& rhs);
  Fraction& operator -= (const Fraction& rhs);

  bool operator == (const Fraction& rhs) const {
    return (this->a * rhs.b) == (this->b * rhs.a);
  }
  bool operator != (const Fraction& rhs) const {
    return (this->a * rhs.b) != (this->b * rhs.a);
  }
  bool operator <  (const Fraction& rhs) const {
    return (this->a * rhs.b) < (this->b * rhs.a);
  }
  bool operator >  (const Fraction& rhs) const {
    return (this->a * rhs.b) > (this->b * rhs.a);
  }
};

Fraction operator + (const Fraction& x, const Fraction& y);
Fraction operator - (const Fraction& x, const Fraction& y);
Fraction operator * (const Fraction& x, const Fraction& y);
Fraction operator / (const Fraction& x, const Fraction& y);
std::ostream& operator << (std::ostream& o, const Fraction& f);

#endif
