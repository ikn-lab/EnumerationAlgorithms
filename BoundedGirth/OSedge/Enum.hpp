#ifndef __ENUM__
#define __ENUM__
#include<vector>
using bigint = long long int;
using pii = std::pair<int, int>;

class EBG{
public:
  EBG(std::vector<std::vector<int> > H, int girth);
  void Enumerate();
  void print();
private:
  std::vector<std::vector<int> > G;
  std::vector<bigint> ans;
  std::vector<std::vector<int> > solution;
  std::vector<pii> edges;
  std::vector<bool> used;
  int m, g;
  int Girth(pii e);
  void dfs(int size = 0, int depth = 0);
};

#endif // __ENUM__
