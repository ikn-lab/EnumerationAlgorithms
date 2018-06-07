#ifndef REVERSE_SEARCH_HPP
#define REVERSE_SEARCH_HPP

template<typename Input, typename Output>
class ReverseSearch{
protected:
  Input input_data;
  std::vector<Output> InitialState;
  int delta, neighbor_counter = 0, tree_id = 0;
  Output* current_sol = NULL, * tmp = NULL;
public:
  ReverseSearch(Input _input_data):input_data(_input_data){};
  ~ReverseSearch(){};
  virtual Output* Parent(Output *v) = 0;
  virtual Output* Child(Output *v, int k) = 0;
  Output* next();
  void playout();
  ReverseSearch<Input, Output> CopyIterater();
};
#include"reverse_search_praivate.hpp"
#endif
