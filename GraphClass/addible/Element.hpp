#ifndef __ELEMENT__
#define __ELEMENT__

class edge{
public:
  edge():from(-1), to(-1), id(-1), cost(-1){};
  edge(int f, int t, int i, int c = 1):
    from(f), to(t), id(i), cost(c){}
  int from, to, id, cost = 1;
};

#endif // __ELEMENT__







