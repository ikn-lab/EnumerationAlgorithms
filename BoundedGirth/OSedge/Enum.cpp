#include<vector>
#include<iostream>
#include<queue>

#include"Enum.hpp"
// #define DEBUG
using bigint = long long int;
using pii = std::pair<int, int>;
using piii = std::pair<pii, int>;

EBG::EBG(std::vector<std::vector<int> > H, int girth){
  G = H, g = girth;
  for (int i = 0; i < G.size(); i++) {
    for (int j = 0; j < G[i].size(); j++) {
      if(i < G[i][j])edges.push_back(pii(i, G[i][j]));
    }
  }
  m = edges.size();
  ans.resize(m + 1, 0);
  solution.resize(G.size());
  used.resize(m, false);
}

void EBG::Enumerate(){
  dfs();
}


int EBG::Girth(pii e){
  solution[e.first ].push_back(e.second);
  solution[e.second].push_back(e.first );
  int res = 1e9;
  for (int i = 0; i < solution.size(); i++) {
    if(solution[i].size() == 0)continue;
    std::queue<pii> que;
    std::vector<int> dist(solution.size(), 1e9);
    dist[i] = 0;
    que.push(pii(i, -1));
    while(not que.empty()){
      int v   = que.front().first;
      int par = que.front().second;
      que.pop();
      for (int j = 0; j < solution[v].size(); j++) {
        if(dist[solution[v][j]] != 1e9){
          if(par != solution[v][j])
            res = std::min(res, dist[v] + dist[solution[v][j]] + 1);
        }else{
          dist[solution[v][j]] = dist[v] + 1;
          que.push(pii(solution[v][j], v));
        }
      }
    }
  }
  if(res < g){
    solution[e.first ].pop_back();
    solution[e.second].pop_back();
  }
  return res;
}

void EBG::dfs(int size, int depth){
  std::vector<piii> cand;
  ans[size]++;
  for (int i = 0; i < edges.size(); i++) {
    if(solution[edges[i].first].size() + solution[edges[i].second].size() > 0
       and not used[i])
      cand.push_back(piii(edges[i], i));
  }
  if(size == 0) {
    for (int i = 0; i < edges.size(); i++) {
      cand.push_back(piii(edges[i], i));
    }
  }
  
  for (int i = 0; i < cand.size(); i++) {
    pii e = cand[i].first;
    used[cand[i].second] = true;
    if(Girth(e) >= g){
      dfs(size + 1, depth + 1); 
      solution[e.first ].pop_back();
      solution[e.second].pop_back();
    }
  }
  for (int i = 0; i < cand.size(); i++) used[cand[i].second] = false;
}

void EBG::print(){
  int sum = 0;
  for (int i = 0; i < ans.size(); i++) sum += ans[i];
  std::cout << sum << std::endl;
  for (int i = 0; i < ans.size(); i++) {
    std::cout << "i:" << i << " " << ans[i] << std::endl;
  }
}
