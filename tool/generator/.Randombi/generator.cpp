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
typedef std::pair<int, int> pii;
typedef std::pair<int, pii> piii;

std::mt19937 mt(114);


bool connect(int n, std::set<pii> &edge){
  std::vector<int> parent(n), group(n);
  for (int i = 0; i < n; i++) parent[i] = group[i] = i;
  for (auto p: edge) {
    int x = p.first, y = p.second;
    while(parent[x] != x)x = parent[x];
    while(parent[y] != y)y = parent[y];
    if(x != y) parent[x] = y;
  }
  for (int i = 0; i < n; i++) {
    while(group[i] != group[group[i]])group[i] = group[group[i]];
  }
  int val = group[0];
  for (int i = 1; i < n; i++) {
    if(val != group[i])return false;
  }
  return true;
}

void randomBipartite(std::ofstream &output_file, int n, double density = -1){
  std::set<pii> edge;
  do{
    if(density == -1)density = sqrt(n)*n/2;
    int cnt = 0;
    int U = mt()%n;
    int W = n - U;
    while(2*edge.size() < density*n){
      if(cnt > 5000){
        break;
      }
      pii add = pii(mt()%U, mt()%W + U);
      if(add.first == add.second){
        cnt++;
        continue;
      }
      pii rev = pii(add.second, add.first);
      if(edge.find(add) != edge.end() or
         edge.find(rev) != edge.end()){
        cnt++;
        continue;
      }
      edge.insert(add);
      cnt = 0;
    }
  }while(connect(n, edge));
  output_file << n << " " << edge.size() << std::endl;
  for (auto add: edge) {
    output_file << add.first << " " << add.second << std::endl;
  }
}

int main(int argc, char *argv[]){
  double density;
  std::string mode;
  int n;
  if(argc == 3){
    n = atoi(argv[1]), density = atof(argv[2]); 
  }else{
    std::cerr << "enter the number of vertices and density." << std::endl;
    exit(1);
  }
  std::string name = "randomBipartite_";
  std::string s = name;
  for (int i = 1; i <= 7; i++) {
    char tmp[5];
    sprintf(tmp, "%02d", i);
    std::string id = tmp;
    name = s + std::to_string(n) + "_" + std::to_string(density).substr(0, 3) + "_" + id + ".in";
    std::cout << name << std::endl;
    std::ofstream output_file(name.c_str());
    randomBipartite(output_file, n, density);
    output_file.close();
  }
  return 0;
}
