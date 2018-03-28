#ifndef __ELEMENT__
#define __ELEMENT__

class edge{
public:
  edge():u(-1), v(-1), id(1), cost(-1){};
  edge(int _u, int _v, int i, int c = 1):
    u(_u), v(_v), id(i), cost(c){}
  int u, v, id, cost = 1;
};

#endif // __ELEMENT__

