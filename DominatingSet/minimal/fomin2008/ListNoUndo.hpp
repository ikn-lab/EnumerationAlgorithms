#ifndef __LISTNOUNDO__
#define __LISTNOUNDO__
#include<vector>
#include<memory>
// #define DEBUG

template<typename T>
class ListNoUndo{
public:
  ListNoUndo(){};
  ListNoUndo(std::vector<T> elem){init(elem);};
  ListNoUndo(int size){init(size);};
  ~ListNoUndo(){};
  ListNoUndo(ListNoUndo&& x){};
  void init(std::vector<T> elem);
  void init(int size);
  inline T& operator[](const int id){return list[id];};
  inline int GetNext(int id){return next[id];};
  inline int GetPrev(int id){return prev[id];};
  void set(T elem, int id){list[id] = elem;};
  int remove(int id);
  int add(int id);
  inline int size(){return _size;}
  inline int maxSize(){return tail;}
  inline int end(){return tail;};
  inline int begin(){return next[tail];};
  inline T back(){return list[prev[end()]];};
  inline bool member(int id){return not removed[id];};
private:
  std::unique_ptr<T[]> list;
  std::unique_ptr<int[]> next, prev;
  std::unique_ptr<bool[]> removed;
  int tail, _size;
};


//n-th element is sentinel
template<typename T>
void ListNoUndo<T>::init(std::vector<T> elem){
  _size   = tail = elem.size();
  list    = std::make_unique<T[]>(tail);
  next    = std::make_unique<int[]>(tail + 1);
  prev    = std::make_unique<int[]>(tail + 1);
  removed = std::make_unique<bool[]>(tail);
  for (int i = 0; i < tail; i++) {
    list[i] = elem[i];
    next[i] = i + 1;
    prev[i] = i - 1;
    removed[i] = false;
  }
  next[tail] = 0;
  prev[tail] = tail - 1;
  prev[0] = tail;
}

//n-th element is sentinel
template<typename T>
void ListNoUndo<T>::init(int size) {
  _size   = tail = size;
  list    = std::make_unique<T[]>(tail);
  next    = std::make_unique<int[]>(tail + 1);
  prev    = std::make_unique<int[]>(tail + 1);
  removed = std::make_unique<bool[]>(tail);
  for (int i = 0; i <= tail; i++) {
    next[i] = i + 1;
    prev[i] = i - 1;
    removed[i] = false;
  }
  next[tail] = 0;
  prev[0] = tail;
}


template<typename T>
int ListNoUndo<T>::remove(int id){
#ifdef DEBUG
  if(removed[id]){
    printf("%d is already removed.\n", id);
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

template<typename T>
int ListNoUndo<T>::add(int id){
  removed[id] = false;
  _size++;
  next[prev[tail]] = id;
  next[id]   = tail;
  prev[id]   = prev[tail];
  prev[tail] = id;
  return prev[id];
}

#endif // __LISTNOUNDO__
