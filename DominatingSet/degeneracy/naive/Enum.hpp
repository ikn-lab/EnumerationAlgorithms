#ifndef __ENUM__
#define __ENUM__
#include<vector>
using bigint = long long int;

class EDS{
public:
  EDS(){}
  EDS(std::vector<std::vector<int> > H){init(H);}
  void init(std::vector<std::vector<int> > H);
  void Enumerate();
  int size(){return G.size();};
  void print();
private:
  // void dfs(int size, int depth = 0);
  std::vector<std::vector<int> > G;
  std::vector<int> dominated;
  std::vector<bigint> ans;
};

#endif // __ENUM__
