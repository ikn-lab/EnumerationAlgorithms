#ifndef NAIVE_HPP
#define NAIVE_HPP
#include<vector>
#include<queue>
#include<unordered_set>
#include<iostream>
#include <boost/multiprecision/cpp_int.hpp>

typedef boost::multiprecision::cpp_int bigint;
typedef struct edge{
  int from, to, id;
}edge;

typedef std::vector<std::vector<edge> > Graph;
typedef std::pair<int, int> pii;
bigint EnumIMatch(std::vector<edge> &m,
                  std::vector<int> &addlist,
                  std::vector<int> &ans,
                  Graph &g,
                  size_t p = 0,
                  int IMsize = 0);

#endif
