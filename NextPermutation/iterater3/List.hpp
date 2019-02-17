#ifndef __LIST__
#define __LIST__
#include<vector>
// #define DEBUG

template<typename T>
class List{
public:
  List(){};
  List(std::vector<T> list_){init(list_);};
  List(int size){init(size);};
  ~List();
  void init(std::vector<T> list_);
  void init(int size);
  inline T& operator[](const int id){return list[id].item;};
  inline int GetNext(int id){return list[id].next;};
  inline int GetPrev(int id){return list[id].prev;};
  void set(T item, int id){list[id].item = item;};
  int remove(int id);
  void undo();
  inline int size(){return s;}
  inline int end(){return tail;};
  inline int begin(){return list[tail].next;};
private:
  class elem{
  public:
    T item;
    int next, prev;
  };
  elem* list;
  int tail, s, head = -1;
  bool *removed;
};

//n-th element is sentinel
template<typename T>
void List<T>::init(std::vector<T> list_){
  s    = tail = list_.size();
  list = new elem[tail + 1];
#ifdef DEBUG
  removed = new bool[tail];
#endif
  for (int i = 0; i <= tail; i++) {
    list[i].item = list_[i];
    list[i].next = i + 1;
    list[i].prev = i - 1;
#ifdef DEBUG    
    removed[i] = false;
#endif
  }
  list[tail].next = 0;
  list[0].prev = tail;
}

//n-th element is sentinel
template<typename T>
void List<T>::init(int size) {
  s    = tail = size;
  list = new elem[tail + 1];
#ifdef DEBUG
  removed = new bool[tail];
#endif
  for (int i = 0; i <= tail; i++) {
    list[i].next = i + 1;
    list[i].prev = i - 1;
#ifdef DEBUG    
    removed[i] = false;
#endif
  }
  list[tail].next = 0;
  list[0].prev = tail;
}


template<typename T>
List<T>::~List(){
  delete list;
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
  list[list[id].next].prev = list[id].prev;
  list[list[id].prev].next = list[id].next;
  list[id].next = head;
  head = id;
  // std::cout << "next[" << 0 << "]:" << next[0] << std::endl;
  // std::cout << "next[" << id - 1 << "]:" << next[id - 1] << std::endl;
  // std::cout << "next[" << id << "]:" << next[id] << std::endl;
  // std::cout << "next[" << id + 1 << "]:" << next[id + 1] << std::endl;
  return list[id].prev;
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
  head = list[id].next;
  list[id].next = list[list[id].prev].next;
  list[list[id].next].prev = id;
  list[list[id].prev].next = id;
}

#endif // __LIST__
