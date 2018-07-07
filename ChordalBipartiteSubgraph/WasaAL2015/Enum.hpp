#ifndef __ENUM__
#define __ENUM__
#include<tuple>
#include<stack>

#include"Element.hpp"
#include"List.hpp"
#include"AddibleGraph.hpp"
#include"AddibleList.hpp"
#include"basicDataStructure.hpp"

using log = std::tuple<int, int, int, int>;
using bigint = long long int;

class ECIB{
public:
  ECIB(std::vector<std::vector<edge>> _G){init(_G);};
  ECIB(){};
  void Enumerate();
  void init(std::vector<std::vector<edge>> _G);
  void print();
private:
  void RecEnum();
  int updateTP(int u);
  int updateCand(int u);
  int GetParent(int v, int x, int y, int u);
  int updateParent(int v, int x, int y, int root);
  void restoreTP(int cnt);
  //For x, y \in N(v), this function answers u and w belong to same connected compornet or not in c(solution, u, w) in O(n) time. 
  bool GetConnect(int v, int x, int y, int u, int w);
  AddibleGraph G;
  int n, delta = 0;
  std::vector<std::vector<std::vector<std::vector<int>>>> tp;
  // std::vector<std::vector<std::vector<std::vector<AddibleList<int>>>>> contract;
  std::vector<bigint> ans;
  // AddibleList<int> solution;
  AddibleList<int> cand;
  FixedStack<log> stack;
};
#endif // __ENUM__

