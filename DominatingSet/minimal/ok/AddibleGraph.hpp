#ifndef __ADDIBLEGRAPH__
#define __ADDIBLEGRAPH__
#include<vector>

#include"AddibleList.hpp"
#include"Element.hpp"

using pii = std::pair<int, int>;

class AddibleGraph{
public:
  AddibleGraph(){};
  AddibleGraph(std::vector<std::vector<edge> > _G){init(_G);};
  void init(std::vector<std::vector<edge> > _G);
  int RemoveEdge(int id, int x = -1);
  int AddEdge(int id, int x = -1);
  int RemoveVertex(int id);
  int AddVertex(int id);
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
  int rev(int id, int v);
  void print();
private:
  int n, m, current_edge_size = 0, head = -1;
  std::vector<AddibleList<edge> > G;
  AddibleList<int> vlist;
  AddibleList<edge> elist;
  std::vector<pii> pos;//min(from, to):first, max(from, to):second
  std::vector<int> next;
};
#endif // __GRAPH__
