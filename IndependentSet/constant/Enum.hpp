#ifndef __ENUM__
#define __ENUM__
#include<memory>
#include<queue>
#include<stack>
#include<chrono>

#include"List.hpp"
#include"basicDataStructure.hpp"
using bigint = long long int;

class EIS{
public:
  EIS(std::vector<std::vector<int> > H);
  ~EIS(){};
  inline int size(){return G.size();}
  void Enumerate();
  void print();
private:
  void RecEnum();
  std::vector<std::vector<int> > G;
  List<int> cand;
  FixedStack<int> solution;
  std::vector<bigint> ans, deg;
  int sum_deg, n; 
};
#endif // __ENUM__
