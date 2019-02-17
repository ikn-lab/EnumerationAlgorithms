#ifndef __LIST__
#define __LIST__
#include<vector>
// #define DEBUG

template<typename T>
class List{
public:
  List(){};
  List(std::vector<T> elem){init(elem);};
  List(int size){init(size);};
  ~List();
  void init(std::vector<T> elem);
  void init(int size);
  inline T& operator[](const int id){return list[id];};
  inline int GetNext(int id){return next[id];};
  inline int GetPrev(int id){return prev[id];};
  void set(T elem, int id){list[id] = elem;};
  int remove(int id);
  void undo();
  inline int size(){return s;}
  inline int end(){return tail;};
  inline int begin(){return next[tail];};
private:
  T* list;
  int *next, *prev;
  int tail, s, head = -1;
  bool *removed;
};

//n-th element is sentinel
template<typename T>
void List<T>::init(std::vector<T> elem){
  s    = tail = elem.size();
  list = new T[tail];
  next = new int[tail + 1];
  prev = new int[tail + 1];
#ifdef DEBUG
  removed = new bool[tail];
#endif
  for (int i = 0; i < tail; i++) {
    list[i] = elem[i];
    next[i] = i + 1;
    prev[i] = i - 1;
#ifdef DEBUG    
    removed[i] = false;
#endif
  }
  next[tail] = 0;
  prev[0] = tail;
}

//n-th element is sentinel
template<typename T>
void List<T>::init(int size) {
  s    = tail = size;
  list = new T[tail];
  next = new int[tail + 1];
  prev = new int[tail + 1];
#ifdef DEBUG
  removed = new bool[tail];
#endif
  for (int i = 0; i <= tail; i++) {
    next[i] = i + 1;
    prev[i] = i - 1;
#ifdef DEBUG
    removed[i] = false;
#endif    
  }
  next[tail] = 0;
  prev[0] = tail;
}


template<typename T>
List<T>::~List(){
  delete next;
  delete prev;
#ifdef DEBUG
  delete removed;
#endif
}

template<typename T>
int List<T>::remove(int id){
#ifdef DEBUG
  if(removed[id]){
    printf("%d is already removed.\n", id);
    std::exit(1);
  }
  removed[id] = true;
#endif
  s--;
  // std::cout << "next[" << 0 << "]:" << next[0] << std::endl;
  prev[next[id]] = prev[id];
  next[prev[id]] = next[id];
  next[id] = head;
  head = id;
  // std::cout << "next[" << 0 << "]:" << next[0] << std::endl;
  // std::cout << "next[" << id - 1 << "]:" << next[id - 1] << std::endl;
  // std::cout << "next[" << id << "]:" << next[id] << std::endl;
  // std::cout << "next[" << id + 1 << "]:" << next[id + 1] << std::endl;
  return prev[id];
}

template<typename T>
void List<T>::undo(){
#ifdef DEBUG
  if(head == -1){
    printf("stack is empty. ");
    std::exit(1);
  }
  removed[head] = false;
#endif
  s++;
  int id = head;
  head = next[id];
  next[id] = next[prev[id]];
  prev[next[id]] = id;
  next[prev[id]] = id;
}

#endif // __LIST__
