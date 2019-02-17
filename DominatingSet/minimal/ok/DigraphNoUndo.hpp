#ifndef __DIGRAPHNOUNDO__
#define __DIGRAPHNOUNDO__
#include<vector>

#include"ListNoUndo.hpp"
#include"Element.hpp"

using pii = std::pair<int, int>;

class DigraphNoUndo{
public:
  DigraphNoUndo(){};
  DigraphNoUndo(std::vector<std::vector<edge> > _G){init(_G);};
  void init(std::vector<std::vector<edge> > _G);
  inline int size(){return vlist.size();}
  inline int edgeSize(){return current_edge_size;}
  inline ListNoUndo<edge>& operator[](const int id){return G[id];}
  int RemoveEdge(int id);
  int AddEdge(int id);
  int RemoveVertex(int id);//バグってます。
  inline int begin(){return vlist.GetNext(n);}
  inline int end(){return n;}
  inline int GetNext(int id){return vlist.GetNext(id);};
  inline int GetPrev(int id){return vlist.GetPrev(id);};
  inline int GetInDeg(int id){return RevG[id].size();};
  inline int GetOutDeg(int id){return G[id].size();};
  inline edge GetEdge(int id){return elist[id];};
  inline int GetPos(int id){return pos[id].first;}
  inline bool member(int id){return elist.member(id);};
  void print();
protected:
  int n, m, current_edge_size = 0;
  std::vector<ListNoUndo<edge> > G, RevG;
  ListNoUndo<int> vlist;
  ListNoUndo<edge> elist;
  std::vector<pii> pos;//G:first, RevG:second
  std::vector<int> next;
};

#endif // __DIGRAPHNOUNDO__
