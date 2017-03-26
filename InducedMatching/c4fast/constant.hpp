#ifndef CONSTANT_HPP
#define CONSTANT_HPP
#include<vector>

#include"graph.hpp"
// #include <boost/multiprecision/cpp_int.hpp>

// typedef boost::multiprecision::cpp_int bigint;
typedef long long int bigint;
typedef std::pair<int, int> pii;

std::vector<bigint> EIMMain(Graph &g);
bigint RecIM(Graph &g, int size = 0, int marge = 1);
bigint CallOneChildren(Graph &g, int v, int size, int marge);

#endif
