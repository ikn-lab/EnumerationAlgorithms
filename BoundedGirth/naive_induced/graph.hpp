#ifndef __GRAPH__
#define __GRAPH__

#include<vector>
#include<stack>
#include<tuple>
#include<set>
using bigint = long long int;

class Graph{
public:
  Graph(int n, int _k){g.resize(n), used.resize(n, false);}
  Graph(){};
  void AddEdge(int u, int v);
  int size(){return g.size();};
  std::vector<int>& operator[](const int v){return g[v];};
  std::vector<bool> used;
private:
  int k;
  std::vector<std::vector<int> > g;
};

#endif // __GRAPH__



