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
  inline int size(){return vlist.size() - org_deg - 1 - isolated;}
  inline int edgeSize(){return current_edge_size;}
  inline List<edge>& operator[](const int id){return G[id];}
  int RemoveEdge(int id, int x = -1);
  int RemoveVertex(int id);
  void undo();
  void MakeVlist();
  inline bool member(int id){return vlist.member(id);};
  inline bool empty(){return vlist.empty();};
  inline int begin(){return GetNext(n + deg + 1);}
  inline int end(){return n + org_deg + 1;}
  inline int GetNext(int id){
    // printf("n: %d, id: %d, deg: %d\n", n, id, deg);
    // printVlist();
    return (n <= vlist.GetNext(id) and vlist.GetNext(id) < n +
            org_deg + 1)?
      GetNext(vlist.GetNext(id)):vlist.GetNext(id);};
  inline int GetPrev(int id){
    return (n <= vlist.GetPrev(id) and vlist.GetPrev(id) < n + org_deg + 1)?
      GetPrev(vlist.GetPrev(id)):vlist.GetPrev(id);};
  inline int GetDeg(int id){return G[id].size();};
  inline edge GetEdge(int id){return elist[id];};
  inline int MaximumDeg(){return begin();};
  inline int MinimumDeg(){return GetPrev(n);};
  void print();
  // int begin(){return G[n]}
  std::vector<int> dist;
  int n, m, current_edge_size = 0, head, org_deg, deg, isolated;
  void printVlist(){
    std::cout << "print vlist" << std::endl;
    for (int i = vlist.begin(); i != vlist.end(); i = vlist.GetNext(i)) {
      std::cout << vlist[i] << " ";
    }
    std::cout << std::endl;
  }
  
protected:
  std::vector<List<edge> > G;
  List<int> vlist;
  List<edge> elist;
  std::vector<pii> pos; //min(from, to): first, max(from, to):second
  std::vector<int> next;
};

#endif // __GRAPH__
