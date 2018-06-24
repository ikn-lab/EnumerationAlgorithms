#ifndef __ENUM__
#define __ENUM__
#include<tuple>
#include<stack>
#include<set>

#include"Graph.hpp"
#include"Element.hpp"
#include"List.hpp"
#include"AddibleList.hpp"

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
  bool isCB();
  bool isConnected();
  void GetDiferentNeighbor(int x, int y, std::set<int> &nx, std::set<int> &ny);
  void dfs(std::vector<bool> &visited, int v = 0);
  bool isSetConnected(int x, int y, std::set<int> &S, std::set<int> &T);
  void RecEnum();
  Graph G;
  int n, current_node = 0;
  std::vector<bigint> ans;
  std::set<int> del;
  AddibleList<int> solution;
};
#endif // __ENUM__


