#ifndef __FRACTION__
#define __FRACTION__
#include<algorithm>

class Fraction{
public:
  Fraction(){}
  Fraction(int _x, int _y):x(_x/std::__gcd(_x, _y)),y(_y/std::__gcd(_x, _y)){};
  Fraction operator+(Fraction f);
  Fraction operator+(int f);
  Fraction operator-(Fraction f);
  Fraction operator-(int f);
  Fraction operator*(Fraction f);
  Fraction operator*(int f);
  bool operator<(int f);
  bool operator>(int f);
  inline int GetNume(){return x;};
  inline int GetDeno(){return y;};
  void print(){printf("density:%.4lf\n", (double)x/y);}
private:
  int x = 0, y = 1;// x/y
};

#endif // __FRACTION__
