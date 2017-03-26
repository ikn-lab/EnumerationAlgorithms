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

bool bfs(int v, std::vector<std::vector<int> > &g){
  std::vector<int> used(g.size(), 1e9);
  std::vector<int> cnt(g.size(), 0);
  std::queue<piii> que;
  que.push(piii(0, pii(v, -1)));
  used[v] = 0;
  while(not que.empty()){
    v = que.front().second.first;
    int prev = que.front().second.second;
    int d = que.front().first;
    que.pop();
    
    if(d >= 2)break;
    for (int i = 0; i < g[v].size(); i++) {
      if(prev == g[v][i])continue;
      if(d == 1 and used[g[v][i]] >= 2 and used[g[v][i]] != 1e9)return true;
      used[g[v][i]] = std::min(used[g[v][i]], d + 1);
      que.push(piii(d + 1, pii(g[v][i], v)));
    }
  }
  return false;
}
bool isFourCycle(std::vector<std::vector<int> > &g){
  int n = g.size();
  for (int i = 0; i < n; i++) {
    if(bfs(i, g) == true)return true;
  }
  return false;
}
void noFourCycleGraph(std::ofstream &output_file, int n, double density){
  std::cout << n << std::endl;
  std::set<pii> edge;
  std::vector<std::vector<int> > g(n);
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
      g[add.first].push_back(add.second);
      g[rev.first].push_back(rev.second);
      if(isFourCycle(g) == false){
        edge.insert(add);
        //std::cerr << "edge size:" << edge.size() << std::endl;
        cnt = 0;
      }else{
        g[add.first].pop_back();
        g[rev.first].pop_back();
      }
    }
  }
  for (auto e:edge) {
    output_file << e.first << " " << e.second << std::endl;
  }
}

void randomGraph(std::ofstream &output_file, int n, double density = -1){
  std::set<pii> edge;
  output_file << n << std::endl;
  if(density == -1)density = sqrt(n)*n;
  int cnt = 0;
  while((double)edge.size()/n < density){
    if(cnt > 5000){
      break;
    }
    pii add = pii(mt()%n, mt()%n);
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
    output_file << add.first << " " << add.second << std::endl;
    cnt = 0;
  }
}

void maxNoShortCycleGraph(std::ofstream &output_file, int n){
  output_file << n << std::endl;
  for (int i = 0; i < n - 1; i++) {
    output_file << i << " " << i + 1 << std::endl;
  }
  int k = 7;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      if(i + k - 1 + (k - 2)*j < n){
        output_file << i << " " << i + k - 1 + (k - 2)*j << std::endl;
      }
    }
  }
}
void Clique(std::ofstream &output_file, int n){
  output_file << n << std::endl;
  for (int i = 0; i < n; i++) {
    for (int j = i + 1; j < n; j++) {
      output_file << i << " " << j << std::endl;
    }
  }
}
// void generate(std::ofstream &output_file, int mode, int n, double density){
//   if(mode == 0){
//     randomGraph(output_file, n, m);
//   }else if(mode == 1){
//     maxNoShortCycleGraph(output_file, 50);
//   }else if(mode == 2){
//     Clique(output_file, 60);
//   }else if(mode == 3){
//     Clique(output_file, 60);
//   }else if(mode == 4){
//     Clique(output_file, 60);
//   }
// }

int main(int argc, char *argv[]){
  double density;
  std::string mode;
  if(argc == 3){
    mode = argv[1], density = atof(argv[2]); 
  }else{
    std::cerr << "enter the number of vertices and density." << std::endl;
  }
  std::string name;
  for (int i = 1; i <= 7; i++) {
    char tmp[2];
    sprintf(tmp, "%02d", i);
    std::string id = tmp;
    //std::cout << std::to_string(density).substr(0, 4) << std::endl;
    name  = mode + std::to_string(density).substr(0, 5) + "_" + id + ".in";
    //std::cout << name << std::endl;

    // std::cout << "generate random case" << std::endl;
    std::ofstream output_file(name.c_str());
    if(mode == "random")randomGraph(output_file, 10*i, density);
    else if(mode == "no_short_cycle")noFourCycleGraph(output_file, 10*i, density);
    else std::cerr << "error file name is wrong." << std::endl;
  }
  return 0;
}
