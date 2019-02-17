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


void randomGraph(std::ofstream &output_file, int n, double density = -1){
  if(density == -1)density = sqrt(n)*n/2;
  int cnt = 0;
  std::vector<pii> edge;
  bool connected = false;
  while(not connected){
    connected = true;
    UnionFind uf(n);
    std::vector<std::vector<int> > G(n, std::vector<int>(n, 0));
    for (int i = 0; i < n; i++) G[i][i] = 1;
    edge.clear();
    while(2*edge.size() < density*n){    
      if(cnt > 5000) break;
      int x = mt()%n, y = mt()%n;
      pii add = pii(std::min(x, y), std::max(x, y));
      if(G[add.first][add.second] == 1){
        cnt++;
        continue;
      }
      G[add.first][add.second] = 1;
      G[add.second][add.first] = 1;
      edge.push_back(add);
      uf.unite(add.first, add.second);
      cnt = 0;
    }
    for (int i = 0; i < n; i++) connected &= uf.same(0, i);
  }
  output_file << n << " " << edge.size() << std::endl;
  for (auto add: edge) {
    output_file << add.first << " " << add.second << std::endl;
  }
}

int main(int argc, char *argv[]){
  double density;
  int n;
  if(argc == 3){
    n = atoi(argv[1]), density = atof(argv[2]); 
  }else{
    std::cerr << "Enter the number of vertices and density." << std::endl;
    exit(1);
  }
  std::string name;
  std::cout << "Generate random graphs." << std::endl;
  for (int i = 1; i <= 1; i++) {
    char tmp[5];
    sprintf(tmp, "%02d", i);
    std::string id = tmp;
    name = "randomGraph_" + std::to_string(n).substr(0, 3) + "_" + std::to_string(density).substr(0, 3) + "_" + id + ".in";
    std::cout << name << std::endl;
    // std::cout << "generate random case" << std::endl;
    std::ofstream output_file(name.c_str());
    randomGraph(output_file, n, density);
    output_file.close();
  }
  return 0;
}
