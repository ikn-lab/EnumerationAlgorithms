#include<iostream>
#include<vector>
#include<fstream>
#include<queue>
using namespace std;
typedef vector<vector<int> > Graph;
typedef long long int lli;
typedef pair<int, int> pii;
typedef pair<int, pii> piii;

int bfs(Graph &g, int v){
  queue<piii> que;
  que.push(piii(0 ,pii(v, -1)));
  vector<int> used(g.size(), -1);
  while(not que.empty()){
    v = que.front().second.first;
    int d = que.front().first;
    int prev = que.front().second.second;
    que.pop();
    used[v] = d;
    for (int i = 0; i < g[v].size(); i++) {
      if(prev == g[v][i])continue;
      if(used[g[v][i]] != -1 and d + used[g[v][i]] + 1 == 4)
        return 4;
      used[g[v][i]] = d + 1;
      que.push(piii(d + 1, pii(g[v][i], v)));
    }
  }
  return -1;
}

bool isFourCycle(Graph &g){
  int n = g.size();
  for (int i = 0; i < n; i++) {
    if(bfs(g, i) == 4)return true;
  }
  return false;
}

int main(int argc, char *argv[]){
  string s;
  ifstream ist(argv[1], ios::in);
  int n;
  getline(ist, s);
  sscanf(s.data(), "%d", &n);
  Graph g(n);
  while(getline(ist, s)){
    int to, from;
    std::sscanf(s.data(), "%d %d", &to, &from);
    g[to].push_back(from);
    g[from].push_back(to);
  }
  if(isFourCycle(g)){
    std::cout << "G has 4-cycle" << std::endl;
  }else{
    std::cout << "G does not have 4-cycle" << std::endl;
  }
    

  return 0;
}
