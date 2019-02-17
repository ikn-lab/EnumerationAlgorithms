#include<iostream>
#include<vector>

#include"unionFind.hpp"
using namespace std;

void UnionFind::init(int _n){
  n = _n;
  rank.resize(n);
  parent.resize(n);
  for (int i = 0; i < n; i++) {
    rank[i] = 0;
    parent[i] = i;
  }
}

int UnionFind::find(int x){
  if(x == parent[x])return x;
  else return parent[x] = find(parent[x]);
}

void UnionFind::unite(int x, int y){
  x = find(x);
  y = find(y);
  if(x == y)return;
  if(rank[x] < rank[y]){
    parent[x] = y;
  }else{
    parent[y] = x;
    if(rank[x] == rank[y])rank[x]++;
  }
}

int UnionFind::size(){
  int res = 0;
  for (int i = 0; i < n; i++) {
    if(parent[i] == i)res++;
  }
  return res;
}

