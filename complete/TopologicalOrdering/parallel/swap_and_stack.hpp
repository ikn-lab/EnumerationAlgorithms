#ifndef SWAP_AND_STACK_HPP
#define SWAP_AND_STACK_HPP

class SwapAndStack{
  Graph G;
  vector<int> tp;
public:
  SwapAndStack(){};
  SwapAndStack(Graph &g){
    init(g);
  };
  void init(Graph &g);
  void Search(FILE *rev);
  int minIndex(vector<int> &v);
};
             
#endif
