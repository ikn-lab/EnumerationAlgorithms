#ifndef __EDGELIST__
#define __EDGELIST__

#include<vector>
#include<stack>

class edge{
public:
  edge():to(-1), rev(-1), next(1), prev(-1){};
  edge(int f, int t, int r, int po, int c = 1, int n = -1, int pr = -1){
    from = f;
    to   = t;
    rev  = r;
    next = n;
    pos  = po;
    prev = pr;
    cost = c;
  }
  int from, to, rev, pos, cost = 1, next, prev;
  void print(){
    printf("from = %d, to = %d, rev = %d, pos = %d\n", from, to, rev, pos);
  }
  bool operator!=(edge& e){
    return (from != e.from or to   != e.to);
  }
};

class EdgeList{
public:
  EdgeList();
  void push_back(edge e);
  void push_back(int id);
  void RemoveEdge(int id);
  void RestoreEdge();
  void UndoAdd();
  void print();
  bool empty(){return elist[0].next == 1;}
  inline int size(){return elist.size();}
  inline int end(){return 1;}
  inline edge& operator[](const int id){return elist[id];}
private:
  std::vector<edge> elist;
  std::stack<int> st, add;
};

#endif // __EDGELIST__

