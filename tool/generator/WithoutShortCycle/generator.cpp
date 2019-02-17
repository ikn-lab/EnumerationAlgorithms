#include<random>
#include<vector>
#include<string>
#include<set>
#include<iostream>
#include<algorithm>
#include<queue>
#include<fstream>
#include<cstring>
#include<ctime>

#include"unionFind.hpp"
typedef std::pair<int, int> pii;
std::mt19937 mt(114);

bool isFourCycle(std::vector<std::vector<int> > &G, pii e){
  int n = G.size();
  std::vector<int> X, Y;
  for (int i = 0; i < n; i++){
    if(G[e.first ][i] == 1 and i != e.first and i != e.second) X.push_back(i);
    if(G[e.second][i] == 1 and i != e.first and i != e.second) Y.push_back(i);
  }
  for (int i = 0; i < X.size(); i++) {
    for (int j = 0; j < Y.size(); j++) {
      if(X[i] == Y[j])continue;
      if(G[X[i]][Y[j]] == 1) return true;
    }
  }
  return false;
}

void noFourCycleGraph(std::ofstream &output_file, int n, double density){
  std::vector<pii> edge;
  int cnt = 0;
  bool connected = false;
  while(not connected){
    std::vector<std::vector<int> > G(n, std::vector<int>(n, 0));
    for (int i = 0; i < n; i++) G[i][i] = 1;
    edge.clear();
    connected = true;
    UnionFind uf(n);
    while((double)edge.size()/n < density){
      if(cnt > 10000)break;
      cnt++;
      int x = mt()%n, y = mt()%n;
      if(x == y) continue;
      pii add = pii(std::min(x, y), std::max(x, y));
      if(G[add.first][add.second] == 0) {
        G[add.first][add.second] = 1;
        G[add.second][add.first] = 1;
        if(not isFourCycle(G, pii(x, y))){
          edge.push_back(add);
          cnt = 0;
          uf.unite(add.first, add.second);
        }else{
          G[add.first][add.second] = 0;
          G[add.second][add.first] = 0;
        }
      }
    }
    for (int i = 0; i < n; i++) connected &= uf.same(0, i);
  }
  output_file << n << " " << edge.size() << std::endl;
  for (auto e:edge) {
    output_file << e.first << " " << e.second << std::endl;
  }
}

int main(int argc, char *argv[]){
  double density;
  int n;
  if(argc == 3){
    n = atoi(argv[1]), density = atof(argv[2]); 
  }else{
    std::cerr << "enter the number of vertices and density." << std::endl;
    exit(1);
  }
  std::string name;
  for (int i = 1; i <= 1; i++) {
    char tmp[5];
    sprintf(tmp, "%02d", i);
    std::string id = tmp;
    name = "noCycleWithLengthFour" + std::to_string(n) + "_" + std::to_string(density).substr(0, 3) + "_" + id + ".in";
    std::cout << name << std::endl;
    std::ofstream output_file(name.c_str());
    noFourCycleGraph(output_file, n, density);
    output_file.close();
  }
  return 0;
}
