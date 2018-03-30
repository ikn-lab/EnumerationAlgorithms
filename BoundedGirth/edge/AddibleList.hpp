#ifndef __ADDIBLELIST__
#define __ADDIBLELIST__
#include<vector>

template<typename T>
class AddibleList{
public:
  AddibleList(){};
  AddibleList(std::vector<T> elem){init(elem);};
  AddibleList(int size){init(size);};
  ~AddibleList();
  void init(std::vector<T> elem);
  void init(int size);
  T& operator[](const int id){return list[id];};
  inline int GetNext(int id){return next[id];};
  inline int GetPrev(int id){return prev[id];};
  void set(T elem, int id){list[id] = elem;}
  int remove(int id);
  int add(int id);
  void undo();
  int size(){return s;}
  int end(){return tail;};
  int begin(){return next[tail];};
  inline bool empty(){return begin() == end();};
private:
  T *list;
  int *next, *prev, *s_next;
  int tail, head = -1, s;
  bool *removed;
};


//n-th element is sentinel
template<typename T>
void AddibleList<T>::init(std::vector<T> elem){
  s      = 0;
  tail   = elem.size();
  list   = new T[tail];
  next   = new int[tail + 1];
  prev   = new int[tail + 1];
  s_next = new int[tail + 1];
#ifdef DEBUG
  removed = new bool[tail];
#endif
  for (int i = 0; i < tail; i++) {
    list[i] = elem[i];
#ifdef DEBUG    
    removed[i] = true;
#endif    
  }
  next[tail] = prev[tail] = tail;
}

//n-th element is sentinel
template<typename T>
void AddibleList<T>::init(int size) {
  s      = 0;
  tail   = size;
  list = new T[tail];
  next = new int[tail + 1];
  prev = new int[tail + 1];
#ifdef DEBUG
  removed = new bool[tail];
  std::fill(removed, removed + tail, true);
#endif    
  next[tail] = prev[tail] = tail;
}


template<typename T>
AddibleList<T>::~AddibleList(){
  delete next;
  delete prev;
#ifdef DEBUG
  delete removed;
#endif
}

template<typename T>
int AddibleList<T>::add(int id){
#ifdef DEBUG
  if(removed[id] == false){
    printf("addible: %d is already added. ", id);
    std::exit(1);
  }
  removed[id] = false;
#endif
  s++;
  s_next[id] = head;
  head = id;
  next[id] = tail;
  prev[id] = prev[tail];
  next[prev[tail]] = id;
  prev[tail] = id;
  return id;
}

template<typename T>
int AddibleList<T>::remove(int id){
#ifdef DEBUG
  if(removed[id]){
    printf("addble: %d is already removed. \n", id);
    std::exit(1);
  }
  removed[id] = true;
#endif
  s--;
  prev[next[id]] = prev[id];
  next[prev[id]] = next[id];
  next[id] = head;
  head = id;
  return prev[id];
}

template<typename T>
void AddibleList<T>::undo(){
  int id = head;
#ifdef DEBUG
  if(head == -1){
    printf("stack is empty. ");
    std::exit(1);
  }
  removed[id] = not removed[id];
#endif
  if(id == next[prev[id]]){//add
    s--;
    head = s_next[id];
    next[prev[id]] = next[id];
    prev[next[id]] = prev[id];
  }else{//removed
    s++;
    head = next[id];
    next[id] = next[prev[id]];
    prev[next[id]] = id;
    next[prev[id]] = id;
  }
}

#endif // __ADDIBLELIST__

