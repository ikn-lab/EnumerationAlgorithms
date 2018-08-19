#ifndef __GRAPH__
#define __GRAPH__

#include<vector>
#include<stack>
#include<tuple>
#include<set>
using bigint = long long int;

class Graph{
public:
  Graph(int n, int _k){
    g.resize(n), used.resize(n, false), k = _k;
    solution_size = 0;
    m.resize(n, std::vector<int>(n, 1e9));
    for (int i = 0; i < n; i++) m[i][i] = 0;
    ms = m;
  }
  Graph(){};
  void AddEdge(int u, int v);
  void NextCand(int v);
  int size(){return g.size();};
  int CurrentSolutionSize(){return solution_size;};
  void erase(int v){used[v] = true;};
  void restore(int v);
  std::vector<int>& operator[](const int v){return g[v];};
  std::set<int> cand, s;
  void print();
  std::vector<bool> used;
private:
  int k, solution_size;
  void update1(int v);
  void update2(int v);
  void updateCand(int v);
  int findSecondMininum(int from, int to);
  std::vector<std::vector<int> > g, m, ms;
  std::stack<std::tuple<int, int, int> > st1, st2;
  std::stack<int> stv;
  // std::vector<bool> used;
};

#endif // __GRAPH__
