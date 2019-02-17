#include<vector>
#include<queue>
#include<unordered_set>
#include"naive.hpp"
#include <boost/multiprecision/cpp_int.hpp>

typedef boost::multiprecision::cpp_int bigint;
using pii = std::pair<int, int>;
using lli = long long int;

bool checkIM(std::vector<edge> &m, Graph &G, std::vector<int> &solution, int size){
  std::vector<int> start_point(G.size(), -1);
  for (int i = 0; i < size; i++) {
    int pos = solution[i];
    edge e = m[pos];
    if(start_point[e.from] >= 0 or
       start_point[e.to  ] >= 0) return false;
    start_point[e.from] = e.to;
    start_point[e.to  ] = e.from;
    pos++;
  }
  for (int i = 0; i < start_point.size(); i++) {
    if(start_point[i] < 0)continue;
    for (int j = 0; j < G[i].size(); j++) {
      int u = G[i][j].to;
      if(start_point[u] >= 0 and i != start_point[u]){
        return false; 
      }
    }
  }
  return true;
}

bigint EnumIMatch(std::vector<edge> &m,
                  std::vector<int> &ans,
                  Graph &G,
                  std::vector<int> &solution,
                  std::vector<int> &count,
                  int size,
                  int depth){
  int res = 0;
  for (lli i = 0; i < (1LL<<m.size()); i++) {
    // std::cout << i << std::endl;
    int size = 0;
    for (lli j = 0; j < G.size(); j++) {
      if((i&(1LL<<j)))solution[size++] = j;
    }
    if(checkIM(m, G, solution, size)) ans[size]++, res++;;
  }
  return res;
}
