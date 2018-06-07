#ifndef REVERSE_SEARCH_PARALLEL_HPP
#define REVERSE_SEARCH_PARALLEL_HPP
#include<mutex>
#include<future>
#include<vector>
template<typename T>
class ReverseSearchParallel{
private:
  std::mutex mtx;
  void dfs(const T S, std::promise<int> res);
protected:
  std::vector<T> S;
  int delta;
  T init_val;
public:
  ReverseSearchParallel(){ delta = 0; };
  void Search(FILE *output_file);
  virtual ~ReverseSearchParallel(){};
  virtual void print(T v) = 0;
  virtual T LocalSearch(T v) = 0;
  virtual T Adj(T v, int j) = 0;

};

#include"reverse_search_praivate_parallel.hpp"

#endif


