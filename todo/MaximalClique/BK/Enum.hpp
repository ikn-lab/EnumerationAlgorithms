#ifndef __ENUM__
#define __ENUM__

class EC{
public:
  EC(std::vector<std::vector<edge> > _G){init(_G);};
  EC(){};
  void Enumerate();
  void init();
  void print();
private:
  void RecEnum();

  Graph G;
  AddibleList<int> cand;
  
}


#endif // __ENUM__
