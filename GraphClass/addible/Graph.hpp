#ifndef __GRAPH__
#define __GRAPH__
#include<vector>

#include"AddibleList.hpp"
#include"Element.hpp"

using pii = std::pair<int, int>;

class Graph{
public:
  Graph(){};
  Graph(std::vector<std::vector<edge> > _G){init(_G);};
  void init(std::vector<std::vector<edge> > _G);
  void RemoveEdge(int id, int x = -1);
  void AddEdge(int id);
  void RemoveVertex(int id);
  void AddVertex(int id);
  void undo();
  inline int size(){return n;}
  inline int edgeSize(){return current_edge_size;}
  inline AddibleList<edge>& operator[](const int id){return G[id];}
  inline int begin(){return vlist.GetNext(n);}
  inline int end(){return n;}
  inline int GetNext(int id){return vlist.GetNext(id);};
  inline int GetPrev(int id){return vlist.GetPrev(id);};
  inline int GetDeg(int id){return G[id].size();};
  inline edge GetEdge(int id){return elist[id];};
  void print();
  // int begin(){return G[n]}
private:
  int n, m, current_edge_size = 0, head = -1;
  std::vector<AddibleList<edge> > G;
  AddibleList<int> vlist;
  AddibleList<edge> elist;
  std::vector<pii> pos;//min(from, to):first, max(from, to):second
  std::vector<int> next;
};
#endif // __GRAPH__
