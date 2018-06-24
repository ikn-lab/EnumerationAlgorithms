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

std::mt19937 mt((int)time(0));

bool isFourCycle(std::vector<std::vector<int> > &G){
  int n = G.size();
  for (int i = 0; i < n; i++) {
    for (int j = i + 1; j < n; j++) {
      std::set<int> X, Y;
      for (int k = 0; k < G[i].size(); k++) X.insert(G[i][k]);
      for (int k = 0; k < G[j].size(); k++) Y.insert(G[j][k]);
      int cnt = 0;
      for (int v: X) cnt += Y.count(v);
      if(cnt >= 2)return true;
    }
  }
  return false;
}
void noFourCycleGraph(std::ofstream &output_file, int n, double density){
  std::cout << n << std::endl;
  std::set<pii> edge;
  std::vector<std::vector<int> > G(n);
  output_file << n << std::endl;
  int cnt = 0;
  while((double)edge.size()/n < density){
    if(cnt > 5000)break;
    cnt++;
    pii add = pii(mt()%n, mt()%n);
    pii rev = pii(add.second, add.first);
    if(add.first == add.second)continue;
    if(edge.find(add) == edge.end() and
       edge.find(rev) == edge.end()){
      G[add.first].push_back(add.second);
      G[rev.first].push_back(rev.second);
      if(isFourCycle(G) == false){
        edge.insert(add);
        cnt = 0;
      }else{
        G[add.first].pop_back();
        G[rev.first].pop_back();
      }
    }
  }
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
  for (int i = 1; i <= 7; i++) {
    char tmp[5];
    sprintf(tmp, "%02d", i);
    std::string id = tmp;
    name = "noCycleWithLengthFour" + std::to_string(density).substr(0, 5) + "_" + id + ".in";
    std::cout << name << std::endl;
    std::ofstream output_file(name.c_str());
    noFourCycleGraph(output_file, n, density);
    output_file.close();
  }
  return 0;
}
