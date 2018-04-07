#ifndef __DIGRAPH__
#define __DIGRAPH__
#include<vector>

#include"AddibleList.hpp"
#include"Element.hpp"

using pii = std::pair<int, int>;

class Digraph{
public:
  Digraph(){};
  Digraph(std::vector<std::vector<edge> > _G){init(_G);};
  void init(std::vector<std::vector<edge> > _G);
  inline int size(){return n;}
  inline int edgeSize(){return current_edge_size;}
  inline AddibleList<edge>& operator[](const int id){return G[id];}
  int RemoveEdge(int id);
  int AddEdge(int id);
  int RemoveVertex(int id);
  int AddVertex(int id);
  void undo();
  inline int begin(){return vlist.GetNext(n);}
  inline int end(){return n;}
  inline int GetNext(int id){return vlist.GetNext(id);};
  inline int GetPrev(int id){return vlist.GetPrev(id);};
  inline int GetInDeg(int id){return RevG[id].size();};
  inline int GetOutDeg(int id){return G[id].size();};
  void print();
  // int begin(){return G[n]}
private:
  int n, m, current_edge_size = 0, head;
  std::vector<AddibleList<edge> > G;
  AddibleList<int> vlist;
  AddibleList<edge> elist;
  std::vector<pii> pos;
  std::vector<int> next;
};
#endif // __DIGRAPH__
