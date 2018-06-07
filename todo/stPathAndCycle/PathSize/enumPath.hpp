#ifndef __ENUMPATH__
#define __ENUMPATH__
#include<vector>

#include"graph.hpp"
typedef long long int bigint;

std::vector<bigint> EPMain(Graph &g);
void LightUpdate(Graph &g);
void RightUpdate(Graph &g);

#endif // __ENUMPATH__
