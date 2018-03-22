#ifndef __GRAPH__
#define __GRAPH__

#include<vector>
#include<stack>
#include<tuple>
#include<set>

#include"edgelist.hpp"
using bigint = long long int;
using element = std::pair<int, edge>;
class Graph{
public:
  Graph(int n, int _k){
    G.resize(n), deg.resize(n, 0), tmp.resize(n, 0);
    edge_id.resize(n), k = _k, m = 0;
    solution_size = 0;
    D.resize(n, std::vector<int>(n, 1e9));
    for (int i = 0; i < n; i++) {
      edge_id[i].push_back(0);
      edge_id[i].push_back(0);
      D[i][i] = 0; 
    }
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
  EdgeList Cin, Cout;
private:
  void updateDistance(edge e);
  void updateCand(edge e);
  void addCandidateSet(edge e, EdgeList &cand);
  void removeCandidateSet(int id, int mode);
  int k, solution_size, m;
  std::vector<EdgeList> G;
  std::vector<std::vector<int> > D, edge_id;
  std::vector<int> deg, tmp;
  std::stack<std::tuple<int, int, int> > dist;
  //0:in2del, 1:out2del, 2:out2in, 3:newedge
  std::stack<element> stack;
  // std::vector<bool> used;
};

#endif // __GRAPH__
