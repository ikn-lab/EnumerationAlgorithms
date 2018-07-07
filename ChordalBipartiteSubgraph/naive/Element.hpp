#ifndef __ELEMENT__
#define __ELEMENT__

class edge{
public:
  edge():from(-1), to(-1), id(-1), cost(-1){};
  ~edge(){};
  edge(int f, int t, int i, int c = 1):
    from(f), to(t), id(i), cost(c){}
  int from, to, id, cost = 1;
  bool operator<(const edge e){return to > e.to;};
};

#endif // __ELEMENT__

