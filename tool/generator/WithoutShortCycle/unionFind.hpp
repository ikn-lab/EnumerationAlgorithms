#ifndef __UNIONFIND__
#define __UNIONFIND__
#include<vector>

class UnionFind{
public:
  UnionFind();
  UnionFind(int _n){init(_n);}
  void init(int _n);
  int find(int x);
  void unite(int x, int y);
  int size();
  bool same(int x, int y){ return find(x) == find(y);}
private:
  int n;
  std::vector<int> rank, parent;
};

#endif // __UNIONFIND__
