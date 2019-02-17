#ifndef SWAP_AND_STACK_HPP
#define SWAP_AND_STACK_HPP
#include<vector>

class SwapAndStack{
  Graph G;
  vector<int> tp;
public:
  SwapAndStack(){};
  SwapAndStack(Graph &G_){init(G_);};
  void init(Graph &G_);
  void Search(FILE *rev);
  int minIndex(vector<int> &v);
};
             
#endif





