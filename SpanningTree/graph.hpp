#ifndef __GRAPH__
#define __GRAPH__
#include<vector>

class UnionFind{
public:
  UnionFind();
  UnionFind(int _n){init(_n);}
  void init(int _n){
    n = _n;
    rank.resize(n);
    parent.resize(n);
    for (int i = 0; i < n; i++) {
      rank[i] = 0;
      parent[i] = i;
    }
  }
  int find(int x){
    if(x == parent[x])return x;
    else return parent[x] = find(parent[x]);
  }
  
  void unite(int x, int y){
    x = find(x);
    y = find(y);
    if(x == y)return;
    if(rank[x] < rank[y]){
      parent[x] = y;
    }else{
      parent[y] = x;
      if(rank[x] == rank[y])rank[x]++;
    }
  }
  bool same(int x, int y){
    return find(x) == find(y);
  }
  int size(){
    int res = 0;
    for (int i = 0; i < n; i++) {
      if(parent[i] == i)res++;
    }
    return res;
  }
private:
  int n;
  std::vector<int> rank, parent;
};

class Graph{
public:
  Graph(){};
  Graph(int n){uf.init(n), g.resize(n);}
  void AddEdge(int u, int v){
    g[u].push_back(u), g[v].push_back(v);
  }
private:
  UnionFind uf;
  std::vector<std::vector<int> > g;
}

#endif // __GRAPH__
