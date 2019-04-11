#include <iostream>
#include <vector>
#include <assert.h>
#include "frac.h"
using std::cout;


int main(){

  // simple test to approximate geometric sum 2/3 + (2/3)^2 + (2/3)^3 + ...
  // Can't choose large N, it quickly overflows
  constexpr int N = 10;
  std::vector<Fraction> v(N);
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
    std::cerr << f.err_name;
  }
  
  return 0;
}
