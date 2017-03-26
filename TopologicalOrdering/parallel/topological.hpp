#ifndef TOPOLOGICAL_HPP
#define TOPOLOGICAL_HPP
#include<queue>
#include<vector>
#include"graph.hpp"
#define MAX_V 1e9
using namespace std;


bool hasInputEdge(Graph &dag, int node);
vector<int> topoSort(Graph dag);

#endif
