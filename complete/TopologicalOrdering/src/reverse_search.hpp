#ifndef REVERSE_SEARCH_HPP
#define REVERSE_SEARCH_HPP
#include"graph.hpp"

template<typename T>
class ReverseSearch{
protected:
  vector<T> S;
  int delta;
  T init_val;
public:
  ReverseSearch(){ delta = 0; };
  void Search(FILE *output_file);

  virtual ~ReverseSearch(){};
  virtual T LocalSearch(T v) = 0;
  virtual T Adj(T v, int j) = 0;

};

#include"reverse_search_praivate.hpp"

#endif
