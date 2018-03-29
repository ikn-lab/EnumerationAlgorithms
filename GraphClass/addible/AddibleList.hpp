#ifndef __ADDIBLELIST__
#define __ADDIBLELIST__
#include<vector>
#define DEBUG

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
  int GetNext(int id){return next[id];};
  int GetPrev(int id){return prev[id];};
  void set(T elem, int id){list[id] = elem;}
  void remove(int id);
  void add(int id);
  void undo();
  int size(){return s;}
  int end(){return tail;};
  int begin(){return next[tail];};
private:
  T *list;
  int *next, *prev, *s_next;
  int tail, head = -1, s;
  bool *removed;
};


//n-th element is sentinel
template<typename T>
void AddibleList<T>::init(std::vector<T> elem){
  s      = tail = elem.size();
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
  s    = tail = size;
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
void AddibleList<T>::add(int id){
#ifdef DEBUG
  if(removed[id] == false){
    printf("%d is already added. ", id);
    std::exit(1);
  }
  removed[id] = false;
#endif
  s++;
  s_next[id] = head;
  head = id;
  next[id] = tail;
  prev[id] = prev[tail];
  prev[tail] = next[prev[tail]] = id;
}

template<typename T>
void AddibleList<T>::remove(int id){
#ifdef DEBUG
  if(removed[id]){
    printf("%d is alredy removed.\n", id);
    std::exit(1);
  }
  removed[id] = true;
#endif
  s--;
  prev[next[id]] = prev[id];
  next[prev[id]] = next[id];
  next[id] = head;
  head = id;
}

template<typename T>
void AddibleList<T>::undo(){
#ifdef DEBUG
  if(head == -1){
    printf("stack is empty. ");
    std::exit(1);
  }
  removed[head] = false;
#endif
  int id = head;
  if(id == prev[next[id]]){//add
    s--;
    next[prev[id]] = next[id];
    prev[next[id]] = prev[id];
    head = s_next[id];
  }else{//removed
    s++;
    head = next[id];
    next[id] = next[prev[id]];
    next[prev[id]] = prev[next[id]] = id;
  }
}

#endif // __ADDIBLELIST__
