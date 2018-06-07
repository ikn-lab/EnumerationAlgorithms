#ifndef __GRAPH__
#define __GRAPH__

#include<vector>
#include<stack>
#include<tuple>
#include<set>
#include<map>
using bigint = long long int;
using pii = std::pair<int, int>;
using piiii = std::pair<pii, pii>;
  
class Graph{
public:
  Graph(int n, int _k){g.resize(n), used.resize(n), k = _k;}
  Graph(){};
  void AddEdge(int u, int v);
  int size(){return g.size();};
  std::vector<int>& operator[](const int v){return g[v];};
  std::vector<std::vector<bool> > used;
  std::map<int, piiii> edge_id;
  int k, m;
private:
  std::vector<std::vector<int> > g;
};

#endif // __GRAPH__



