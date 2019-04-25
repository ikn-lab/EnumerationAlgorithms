#ifndef __ENUM__
#define __ENUM__
#include<memory>
#include<queue>
#include<stack>
#include<chrono>

#include"List.hpp"
#include"basicDataStructure.hpp"
using bigint = long long int;
using SmallestLastOrdering = std::vector<std::vector<int> >;

class EIS{
public:
  EIS(std::vector<std::vector<int> > H);
  ~EIS(){};
  inline int size(){return G.size();}
  void Enumerate();
  void print();
private:
  void RecEnum();
  void ComputeSLO(int d);
  std::vector<std::vector<int> > G;
  SmallestLastOrdering SLO; 
  List<int> cand;
  FixedStack<int> solution;
  std::vector<bigint> ans, deg;
  int sum_deg, n; 
};
#endif // __ENUM__


