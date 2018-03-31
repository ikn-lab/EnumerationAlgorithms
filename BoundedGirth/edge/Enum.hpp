#ifndef __ENUM__
#define __ENUM__
#include<vector>

#include"Graph.hpp"
#include"AddibleList.hpp"
#include"Element.hpp"
using bigint = long long int;

void NextCand(Graph &G, edge e, bool isInner);
void updateCand(Graph &G, edge e, bool isInner);
void updateDistance(Graph &G, edge e);
void restore(Graph &G, edge e, bool isInner);
edge GetCand();
std::vector<bigint> EBGMain(Graph &G, int _k);

#endif // __ENUM__
