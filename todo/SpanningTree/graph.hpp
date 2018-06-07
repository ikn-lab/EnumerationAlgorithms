#ifndef __GRAPH__
#define __GRAPH__
#include<vector>
#include<stack>

typedef std::pair<int, int> pii;
struct Node{
  int ord, low;
};

class edge{
public:
  edge():to(-1), rev(-1), next(1), prev(-1){};
  edge(int t, int r, int n, int p){
    to   = t;
    rev  = r;
    next = n;
    prev = p;
  }
  int to, rev, next, prev;
};

  
class EdgeList{
public:
  EdgeList(){
    s = 2;
    elist.push_back(edge(-1, -1, 1, -1));
    elist.push_back(edge(-1, -1, 1e9, 0));
  }
  void push_back(edge e){s++, elist.push_back(e);};
  void RemoveEdge(int id);
  void RestoreEdge();
  void print();
  inline int size(){return s - 2;}
  inline int end(){return 1;}
  inline edge& operator[](const int id){return elist[id];}
private:
  int s;
  std::vector<edge> elist;
  std::stack<int> st;
};


class Graph{
public:
  Graph(){};
  Graph(int n_):n(n_), g_tail(n_ - 1){
    g.resize(2*n);
    node.resize(2*n, Node{-1, (int)1e9});
    m = 0;
  }
  void AddEdge(int u, int v);
  int Contract(int u, int v);
  void Uncontract();
  int EnumBridgeAndContract();
  int GetNode(){return g_tail;};
  int BridgeSize(){return bridge_size;};
  bool empty(){return n == 1;};
  int size(){return n;}
  EdgeList& operator[](int i){return g[i];};
  std::vector<pii> bridge;
  int v_ord = 0, g_tail, bridge_size = 0, history_size = 0;
private:
  int Dfs(int v, int previous);//whether contracted or not
  int n, m;
  std::vector<EdgeList> g;
  std::vector<Node> node;
  std::vector<pii> history;
  
};

#endif // __GRAPH__
