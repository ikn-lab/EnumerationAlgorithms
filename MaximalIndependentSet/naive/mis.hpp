#ifndef MIS_HPP
#define MIS_HPP

#include<vector>
typedef long long int lli;

typedef class Graph{
public:
  Graph(int n){g.resize(n, std::vector<int>()), neighbor.resize(n, 0);}
  int size(){return g.size();};
  std::vector<int> & operator[](const int p){return g[p];}
  int N(int v){return neighbor[v];};
  void IncrementNeighbor(int v){neighbor[v]++;};
  void decrementNeighbor(int v){neighbor[v]--;};
  void AssignmentNeighbor(int v,int x){neighbor[v] = x;};
private:
  std::vector<std::vector<int> > g;
  std::vector<int> neighbor;
}Graph;

lli MIS(Graph &g, int v = 0);

#endif
