#include<vector>
typedef long long int lli;

typedef class Graph{
public:
  Graph(int _n):n(_n){g.resize(_n), neighbor.resize(_n, 0);}
  int size(){return g.size();};
  std::vector<int> & operator[](const int p){return g[p];}
  int N(int v){return neighbor[v];};
  void IncrementNeighbor(int v){neighbor[v]++;};
  void decrementNeighbor(int v){neighbor[v]--;};
  void AssignmentNeighbor(int v,int x){neighbor[v] = x;};
  void print(){
    std::cout << "print" << std::endl;
    for (int i = 0; i < n; i++) {
      std::cout << neighbor[i] << std::endl;
    }
  }
private:
  int n;
  std::vector<int> neighbor;
  std::vector<std::vector<int> > g;
}Graph;

lli MIS(Graph &g, int v = 0);
