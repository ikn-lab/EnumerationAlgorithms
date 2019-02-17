#ifndef __ENUM__
#define __ENUM__
#include<vector>

#include"Graph.hpp"
#include"AddibleList.hpp"
#include"Element.hpp"
#include"Fraction.hpp"
using bigint = long long int;

class EBGIterator{
public:
  EBGIterator(std::vector<std::vector<edge> > _G, int _k);
  ~EBGIterator();
  bool next(bool isBackTrack = false);
  bool skip();
  void playOut(){while(next());};
  void printSolution();
  // inline int solutionSizeV(){return sol_size;};
  inline int solutionSizeV(){return G.size();};
  inline int solutionSizeE(){return solution.size();};
  inline int upperBound(){return G.edgeSize() + solution.size();};
  AddibleList<edge> solution;
  edge* dentist_solution;
  int dense_solution_size = 0;
  Fraction density;
private:
  Graph G;
  bigint *result;
  int **D;
  //G:Graph, L:Loop, D:Distance, I:Inner, E:Edge
  int *stack_G, *stack_D, *stack_P, *A, *deg;
  edge *stack_E;
  int head_D = -1, head_G = -1, head = -1;
  int n, m, loop = 0, k, sol_size = 0;
  AddibleList<edge> Cin, Cout;
  edge GetCand();
  void restore(edge e, bool isInner);
  void nextCand(edge e, bool isInner);
  void updateCand(edge e, bool isInner);
  void updateDistance(edge e);
  bool traverse();
};

#endif // __ENUM__
