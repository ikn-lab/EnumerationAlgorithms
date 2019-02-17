#ifndef NEXT_PERMUTATION
#define NEXT_PERMUTATION
#include<vector>
#include"basicDataStructure.hpp"
class next_permutation{
public:
  next_permutation(){};
  next_permutation(int n_);
  void Enumerate(FILE *rev);
  inline int minIndex();
private:
  FixedStack<int> st;
  std::vector<int> ordering, next;
  int n;
};
#endif
