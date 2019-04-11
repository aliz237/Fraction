#include <iostream>
#include <vector>
#include <assert.h>

using namespace std;

struct Bad_frac{
  std::string err_name;
  Bad_frac(const char* n) : err_name{n} {}
  Bad_frac(std::string n) : err_name{n} {}

};

void error(const char* err_name){ throw Bad_frac(err_name);}

class Fraction{
  int a,b;

  int gcd(int a, int b){
    // replace this with the fastest
    // possible algorithm for gcd
    a = abs(a);
    // b is always > 0

    while (a != b){
      if (a > b)
	a -= b;
      else
	b -= a;
    }
    return a;
  }
  
  void simplify (int& a, int& b){
    int d = gcd(a,b);
    a /= d;
    b /= d;
  }
  
public:

  Fraction (int a=0, int b=1){
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

  Fraction& operator - (){
    this->a *= -1;
    return *this;
  }
  
  Fraction& operator += (const Fraction& rhs){
    Fraction temp(a * rhs.b + rhs.a * b, b * rhs.b);
    *this = temp;
    return *this;
  }

  Fraction& operator *= (const Fraction& rhs){
    Fraction temp(a * rhs.a, b * rhs.b);
    return *this = temp;
  }

  Fraction& operator /= (const Fraction& rhs){
    return (*this) *= rhs.reciprocal();
  }
  
  Fraction& operator -= (const Fraction& rhs){
    Fraction temp{rhs};
    return (*this) += (- temp);
  }

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
  
  Fraction reciprocal () const {
    if (!a) error("Can't compute the reciprocal of 0\n");
    return Fraction(b,a);
  }
  
  ostream& print(ostream& o) const {
    if (a % b)
      o << a << "/" << b;
    else
      o << a/b;
    return o;
  }

};

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
  
ostream& operator << (ostream& o, const Fraction& f){
  return f.print(o);
}

int main(){

  // simple test to approximate geometric sum 2/3 + (2/3)^2 + (2/3)^3 + ...
  // Can't choose large N, it quickly overflows
  constexpr int N = 10;
  vector<Fraction> v(N);
  Fraction r(2,3);
  Fraction sum;

  // fill up the vector with a decreasing sequence of fractions (2/3)^n
  v[0] = r;
  for (unsigned i=1; i<v.size(); ++i){
    v[i] = v[i-1] * r;
    cout << v[i] << " ";
    sum += v[i];  
  }

  cout <<"\nsum: " << sum << " should be close to:" << (2.0/3) / (1- 2.0/3) << "\n";

  assert(v[1] > v[2]);
  assert(v[2] < v[1]);
  assert(-v[1] < v[2]);
  assert(v[2].reciprocal() < v[3].reciprocal());

  // this should be 1/r = 1/v[0] = 3/2
  assert(v[2] / v[3] == v[0].reciprocal());
  
  assert(v[2] != v[3]);
  
  //2/3 - 8/27 = (18-8)/27 = 10/27
  assert(v[0]-v[2] == Fraction(10,27));

  // -2/3 - 8/27 = (-18-8)/27 = -26/27
  // unary - multiplies its operand by -1
  assert(-v[0]-v[2] == Fraction(26,-27));

  assert(Fraction(-2,-3) == Fraction(2,3));
  assert(Fraction(-2,3) == Fraction(2,-3));
  assert(Fraction(2,-3) < Fraction(-1,2));

  cout << "-60/3=" << Fraction(-20) << ", -2/-3=" << Fraction(-2,-3);
  cout << " ,4/-3=" << Fraction(4,-3);
  cout <<"\nAll tests passed\n";

  // some bad cases
  try{

    Fraction a(1,2), b; //b=0

    //Fraction c(1,0);
    // a / b;
     b.reciprocal();

  }
  
  catch(Bad_frac f){
    cerr << f.err_name;
  }
  
  return 0;
}
