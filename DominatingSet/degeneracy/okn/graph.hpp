#ifndef __GRAPH__
#define __GRAPH__
#include<vector>
using bigint = long long int;

class Graph{
public:
  Graph(int n);
  void DegenerateOrder();
  void sort();
  void AddEdge(int u, int v){g[u].push_back(v), g[v].push_back(u);}
  inline std::vector<int>& operator[](int id){return g[id];}
  inline int size(){return g.size();}
  void print();
  std::vector<bool> used;
  std::vector<int> dominated;
  int degeneracy = 0;
private:
  std::vector<std::vector<int> > g;
};

#endif // __GRAPH__
