#ifndef NEXT_PERMUTATION
#define NEXT_PERMUTATION
#include<vector>
#include"basicDataStructure.hpp"
#include"List.hpp"

class next_permutation{
public:
  next_permutation(){};
  next_permutation(int n_);
  bool next();
  inline int minIndex();
private:
  FixedStack<std::tuple<int, int, int> > st;
  List<int> elem;
  std::vector<int> perm;
  int n, i, d, is_left;
};
#endif
