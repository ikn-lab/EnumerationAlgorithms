#ifndef __ADDIBLELISTNOUNDO__
#define __ADDIBLELISTNOUNDO__
#include<vector>
#include<cstdio>
#include<memory>
// #define DEBUG
template<typename T>
class AddibleListNoUndo{
public:
  AddibleListNoUndo(){};
  AddibleListNoUndo(std::vector<T> elem){init(elem);};
  AddibleListNoUndo(int size){init(size);};
  ~AddibleListNoUndo(){};
  AddibleListNoUndo(const AddibleListNoUndo<T> &&x){};
  void init(std::vector<T> elem);
  void init(int size);
  inline T& operator[](const int id){return list[id];};
  inline int GetNext(int id){return next[id];};
  inline int GetPrev(int id){return prev[id];};
  void set(T elem, int id){list[id] = elem;}
  int remove(int id);
  int add(int id);
  inline int size(){return _size;}
  inline int end(){return tail;};
  inline T back(){return list[prev[end()]];};
  inline int begin(){return next[tail];};
  inline bool empty(){return begin() == end();};
  inline bool member(int id){return not removed[id];};
private:
  std::unique_ptr<T[]> list;
  std::unique_ptr<int[]> next, prev;
  std::unique_ptr<bool[]> removed;
  int _size, tail;
};


//n-th element is sentinel
template<typename T>
void AddibleListNoUndo<T>::init(std::vector<T> elem){
  _size   = 0;
  tail    = elem.size();
  list    = std::make_unique<T[]>(tail);
  next    = std::make_unique<int[]>(tail + 1);
  prev    = std::make_unique<int[]>(tail + 1);
  removed = std::make_unique<bool[]>(tail);
  for (int i = 0; i < tail; i++) {
    list[i] = elem[i];
    removed[i] = true;
  }
  next[tail] = prev[tail] = tail;
}


//n-th element is sentinel
template<typename T>
void AddibleListNoUndo<T>::init(int s) {
  _size   = 0;
  tail    = s;
  list    = std::make_unique<T[]>(tail);
  next    = std::make_unique<int[]>(tail + 1);
  prev    = std::make_unique<int[]>(tail + 1);
  removed = std::make_unique<bool[]>(tail);
  for (int i = 0; i < tail; i++) {
    removed[i] = true;
  }
  next[tail] = prev[tail] = tail;
}


template<typename T>
int AddibleListNoUndo<T>::add(int id){
#ifdef DEBUG
  if(not removed[id]){
    printf("addible: %d is already added. ", id);
    std::exit(1);
  }
#endif
  if(not removed[id])return id;
  removed[id] = false;
  _size++;
  next[id] = tail;
  prev[id] = prev[tail];
  next[prev[tail]] = id;
  prev[tail]       = id;
  return id;
}

template<typename T>
int AddibleListNoUndo<T>::remove(int id){
#ifdef DEBUG
  if(removed[id]){
    printf("addble: %d is already removed. \n", id);
    std::exit(1);
  }
#endif
  if(removed[id])return prev[id];
  removed[id] = true;
  _size--;
  prev[next[id]] = prev[id];
  next[prev[id]] = next[id];
  return prev[id];
}
#endif // __ADDIBLELISTNOUNDO__



