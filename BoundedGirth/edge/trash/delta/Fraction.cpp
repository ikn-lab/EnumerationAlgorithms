#include<algorithm>
#include<iostream>

#include"Fraction.hpp"

Fraction Fraction::operator+(Fraction f){
  int a = (x*f.y) + (y*f.x);
  int b = y*f.y;
  return Fraction{a/std::__gcd(a,b), b/std::__gcd(a,b)};
}

Fraction Fraction::operator+(int f){
  int a = x + y*f;
  return Fraction{a/std::__gcd(a,y), y/std::__gcd(a,y)};
}

Fraction Fraction::operator-(Fraction f){
  int a = (x*f.y) - (y*f.x);
  int b = y*f.y;
  return Fraction{a/std::__gcd(a,b), b/std::__gcd(a,b)};
}

Fraction Fraction::operator-(int f){
  int a = x - y*f;
  return Fraction{a/std::__gcd(a,y), y/std::__gcd(a,y)};
}

Fraction Fraction::operator*(Fraction f){
  int a = x*f.x;
  int b = y*f.y;
  return Fraction{a/std::__gcd(a,b), b/std::__gcd(a,b)};
}

Fraction Fraction::operator*(int f){
  int a = x*f;
  return Fraction{a/std::__gcd(a, y), y/std::__gcd(a, y)};
}

bool Fraction::operator<(int f){
  return x < f*y;
}
bool Fraction::operator>(int f){
  return x > f*y;
}

