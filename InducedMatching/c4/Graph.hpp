#ifndef __GRAPH__
#define __GRAPH__
#include<vector>

#include"List.hpp"
#include"Element.hpp"
#include"basicDataStructure.hpp"

using pii = std::pair<int, int>;

class Graph{
public:
  Graph(){};
  Graph(std::vector<std::vector<edge> > _G){init(_G);};
  void init(std::vector<std::vector<edge> > _G);
  inline int size(){return n;}
  inline int edgeSize(){return current_edge_size;}
  inline List<edge>& operator[](const int id){return G[id];}
  int RemoveEdge(int id, int x = -1);
  int RemoveVertex(int id);
  void undo();
  void MakeVlist();
  inline bool member(int id){return vlist.member(id);};
  inline bool empty(){return vlist.empty();};
  inline int begin(){return GetNext(n + deg + 1);}
  inline int end(){return n + deg + 1;}
  inline int GetNext(int id){
    int res = vlist.GetNext(id);
    while(n <= res and res < n + deg + 1) res = vlist.GetNext(res);
    return res;};
  inline int GetPrev(int id){
    int res = vlist.GetPrev(id);
    while(n <= res and res < n + deg + 1) res = vlist.GetPrev(res);
    return res;};
  inline int GetDeg(int id){return (id < n)?G[id].size():-1;};
  inline edge GetEdge(int id){return elist[id];};
  inline int MaximumDeg(){return begin();};
  void print();
  // int begin(){return G[n]}
  std::vector<int> dist;
protected:
  int n, m, current_edge_size = 0, head, deg;
  std::vector<List<edge> > G;
  List<int> vlist;
  List<edge> elist;
  std::vector<pii> pos; //min(from, to): first, max(from, to):second
  std::vector<int> next;
};

#endif // __GRAPH__
