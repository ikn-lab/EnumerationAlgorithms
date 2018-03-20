#ifndef __GRAPH__
#define __GRAPH__

#include<vector>
#include<stack>
#include<tuple>
#include<set>

#include"edgelist.hpp"
using bigint = long long int;

class Graph{
public:
  Graph(int n, int _k){
    G.resize(n), deg.resize(n, 0), tmp.resize(n, 0), k = _k;
    solution_size = 0;
    D.resize(n, std::vector<int>(n, 1e9));
    for (int i = 0; i < n; i++) D[i][i] = 0;
  }
  Graph(){};
  void AddEdge(int from, int to, int cost = 1);
  void NextCand(edge e);
  void restore(edge e);
  int size(){return G.size();};
  inline EdgeList& operator[](int id){return G[id];}
  bool candEmpty(){return (Cin.empty() and Cout.empty());}
  edge GetCand();
  int CurrentSolutionSize(){return solution_size;};
  void print();
  std::vector<edge> Cin, Cout;
private:
  void updateDistance(edge e);
  void updateCand(edge e);
  int k, solution_size;
  std::vector<EdgeList> G;
  std::vector<std::vector<int> > D;
  std::vector<int> deg, tmp;
  std::stack<std::tuple<int, int, int> > dist;
  std::stack<edge> out2in, in2del, out2del;
  // std::vector<bool> used;
};

#endif // __GRAPH__
