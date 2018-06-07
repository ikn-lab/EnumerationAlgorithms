#ifndef CONSTANT_HPP
#define CONSTANT_HPP
#include"graph.hpp"
#include <boost/multiprecision/cpp_int.hpp>

typedef boost::multiprecision::cpp_int bigint;

bigint EnumIMatch(Graph &g, std::vector<bigint> &ans, int size = 0, int marge = 1);

#endif
