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
  void nextCand(edge e, bool isInner);
  void updateCand(edge e, bool isInner);
  void updateDistance(edge e);
  void restore(edge e, bool isInner);
  bool GetCand(edge &e);
  bool next(bool isBackTrack = false);
  void playOut(){while(next());};
  AddibleList<edge> solution;
private:
  Graph G;
  std::vector<bigint> result;
  std::vector<std::vector<int> > D;
  //G:Graph, L:Loop, D:Distance, I:Inner, E:Edge
  int *stack_G, *stack_D, *stack_P, *A, *deg;
  bool *stack_I;
  edge *stack_E;
  int head_D = -1, head_G = -1, head_I = -1, head_E = -1, head_P = -1;
  int loop = 0, k;
  AddibleList<edge> Cin, Cout;
};


#endif // __ENUM__
