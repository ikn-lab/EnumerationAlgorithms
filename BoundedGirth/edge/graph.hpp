#ifndef __GRAPH__
#define __GRAPH__
#include<vector>

#include"List.hpp"
#include"Element.hpp"

using pii = std::pair<int, int>;

class Graph{
public:
  Graph(std::vector<std::vector<edge> > _G);
  int size(){return n;}
  int edgeSize(){return m;}
  List<edge>& operator[](const int id){return G[id];}
  int RemoveEdge(int id, int x = -1);
  int RemoveVertex(int id);
  void undo();
  int begin(){return vlist.GetNext(n);}
  int end(){return n;}
  int GetNext(int id){return vlist.GetNext(id);};
  int GetPrev(int id){return vlist.GetPrev(id);};
  int GetDeg(int id){return deg[id];};
  void print();
  // int begin(){return G[n]}
private:
  int n, m;
  std::vector<List<edge> > G;
  List<int> vlist;
  List<edge> elist;
  std::vector<pii> edge2vertex;//u: first, v:second
  int head;
  std::vector<int> next, deg;
};

#endif // __GRAPH__
