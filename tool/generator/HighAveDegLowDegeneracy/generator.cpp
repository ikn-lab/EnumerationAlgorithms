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
typedef std::pair<int, pii> piii;

std::mt19937 mt(114);

void randomGraph(std::ofstream &output_file, int n, int degeneracy){
  int cnt = 0;
  UnionFind uf(n);
  bool connected = false;
  std::vector<std::vector<int> > G(n);
  while(not connected){
    G.resize(n);
    connected = true;
    for (int i = 0; i < n; i++) {
      std::set<int> to;
      while(to.size() < std::min(degeneracy, n - i - 1))to.insert(mt()%(n - i - 1) + i + 1);
      for (auto j: to){
        G[i].push_back(j);
        uf.unite(i, j);
        cnt++;
      }
    }
    for (int i = 0; i < n; i++) connected &= uf.same(0, i);
  }
  output_file << n << " " << cnt << std::endl;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < G[i].size(); j++) {
      output_file << i << " " << G[i][j] << std::endl;
    }
  }
}

int main(int argc, char *argv[]){
  int degeneracy;
  int n;
  if(argc == 3){
    n = atoi(argv[1]), degeneracy = atoi(argv[2]); 
  }else{
    std::cerr << "Enter the number of vertices and degeneracy." << std::endl;
    exit(1);
  }
  std::string name;
  std::cout << "Generate k-degenerate random graphs." << std::endl;
  for (int i = 1; i <= 7; i++) {
    char tmp[5];
    sprintf(tmp, "%02d", i);
    std::string id = tmp;
    name = "HighAveDegLowDegenerate" + std::to_string(n) + "_" + std::to_string(degeneracy).substr(0, 5) + "_" + id + ".in";
    std::cout << name << std::endl;
    // std::cout << "generate random case" << std::endl;
    std::ofstream output_file(name.c_str());
    randomGraph(output_file, n, degeneracy);
    output_file.close();
  }
  return 0;
}
