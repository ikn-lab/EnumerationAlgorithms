#ifndef __ENUM__
#define __ENUM__
#include<vector>

#include"Graph.hpp"
#include"AddibleList.hpp"
#include"Element.hpp"
using bigint = long long int;

class EBGIterator{
public:
  EBGIterator(std::vector<std::vector<edge> > _G, int _k);
  ~EBGIterator();
  bool next(bool isBackTrack = false);
  void playOut(){while(next());};
  void printSolution();
  AddibleList<edge> solution;
private:
  Graph G;
  bigint *result;
  int **D;
  //G:Graph, L:Loop, D:Distance, I:Inner, E:Edge
  int *stack_G, *stack_D, *stack_P, *A, *deg;
  edge *stack_E;
  int head_D = -1, head_G = -1,head_E = -1, head_P = -1;
  int loop = 0, k;
  AddibleList<edge> Cin, Cout;
  edge GetCand();
  void printStacks();
  void restore(edge e, bool isInner);
  void nextCand(edge e, bool isInner);
  void updateCand(edge e, bool isInner);
  void updateDistance(edge e);
};


#endif // __ENUM__
