#ifndef NEXT_PERMUTATION
#define NEXT_PERMUTATION
#include<vector>
// #include<stack>
#include"basicDataStructure.hpp"

class next_permutation{
public:
  next_permutation(){};
  next_permutation(int n_);
  ~next_permutation(){delete perm;};
  bool next();
  void printPerm();
private:
  FixedStack<std::tuple<int, int> > st;
  int elem;
  int* perm;
  int n, i, d, tmp;
};
#endif
