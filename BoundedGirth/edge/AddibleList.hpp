#ifndef __ADDIBLELIST__
#define __ADDIBLELIST__
#include<vector>
#include<cstdio>
#include<memory>
// #define DEBUG
template<typename T>
class AddibleList{
public:
  AddibleList(){};
  AddibleList(std::vector<T> elem, int multi = 1){init(elem, multi);};
  AddibleList(int size, int multi = 1){init(size, multi);};
  ~AddibleList();
  void init(std::vector<T> elem, int multi = 1);
  void init(int size, int multi = 1);
  inline T& operator[](const int id){return list[id];};
  inline int GetNext(int id){return next[id];};
  inline int GetPrev(int id){return prev[id];};
  void set(T elem, int id){list[id] = elem;}
  int remove(int id, int type = 0);
  int add(int id, int type = 0);
  void undo(int type = 0);
  inline int size(int type = 0){return s[type];}
  inline int end(int type = 0){return tail[type];};
  inline int begin(int type = 0){return next[tail[type]];};
  inline int GetNumList(){return num_list;};
  inline bool empty(int type = 0){return begin(type) == end(type);};
private:
  std::unique_ptr<T[]> list;
  std::unique_ptr<int[]> next, prev, s_next, head, tail, s;
  std::unique_ptr<bool[]> removed;
  int num_list;
};


//n-th element is sentinel
template<typename T>
void AddibleList<T>::init(std::vector<T> elem, int multi){
  num_list = multi;
  s    = std::make_unique<int[]>(multi);
  tail = std::make_unique<int[]>(multi);
  head = std::make_unique<int[]>(multi);
  list = std::make_unique<T[]>(elem.size());

  //multi個のsentinelを作る
  next   = std::make_unique<int[]>(elem.size() + multi);
  prev   = std::make_unique<int[]>(elem.size() + multi);
  s_next = std::make_unique<int[]>(elem.size() + multi);
  
  for (int i = 0; i < multi; i++){
    s[i] = 0, head[i] = -1;
    tail[i] = i + elem.size();
    next[i + elem.size()] = prev[i + elem.size()] = i + elem.size();
  } 
#ifdef DEBUG
  removed = std::make_unique<bool[]>(elem.size());
#endif
  for (int i = 0; i < elem.size(); i++) {
    list[i] = elem[i];
#ifdef DEBUG    
    removed[i] = true;
#endif    
  }
}

//n-th element is sentinel
template<typename T>
void AddibleList<T>::init(int size, int multi) {
  s    = std::make_unique<int[]>(multi);
  tail = std::make_unique<int[]>(multi);
  head = std::make_unique<int[]>(multi);
  list = std::make_unique<T[]>(size);

  //multi個のsentinelを作る
  next   = std::make_unique<int[]>(size + multi);
  prev   = std::make_unique<int[]>(size + multi);
  s_next = std::make_unique<int[]>(size + multi);

  for (int i = 0; i < multi; i++){
    s[i] = 0, head[i] = -1;
    tail[i] = i + size;
    next[i + size] = prev[i + size] = i + size;
  } 
#ifdef DEBUG
  removed = std::make_unique<bool[]>(size);
  for (int i = 0; i < size; i++) removed[i] = true;
#endif    
}


template<typename T>
AddibleList<T>::~AddibleList(){
//   delete next;
//   delete prev;
//   delete s_next;
//   delete head;
//   delete tail;
//   printf("%p\n", head);
//   printf("%p\n", tail);
//   printf("%p\n", s);
//   delete s;
// #ifdef DEBUG
//   delete removed;
// #endif
}

template<typename T>
int AddibleList<T>::add(int id, int type){
#ifdef DEBUG
  if(not removed[id]){
    printf("addible: %d is already added. ", id);
    std::exit(1);
  }
  removed[id] = false;
#endif
  s[type]++;
  s_next[id] = head[type];
  head[type] = id;
  next[id] = tail[type];
  prev[id] = prev[tail[type]];
  next[prev[tail[type]]] = id;
  prev[tail[type]] = id;
  return id;
}

template<typename T>
int AddibleList<T>::remove(int id, int type){
#ifdef DEBUG
  if(removed[id]){
    printf("addble: %d is already removed. \n", id);
    std::exit(1);
  }
  removed[id] = true;
#endif
  s[type]--;
  prev[next[id]] = prev[id];
  next[prev[id]] = next[id];
  next[id] = head[type];
  head[type] = id;
  return prev[id];
}

template<typename T>
void AddibleList<T>::undo(int type){
  int id = head[type];
#ifdef DEBUG
  if(head[type] == -1){
    printf("addble:stack is empty. ");
    std::exit(1);
  }
  removed[id] = not removed[id];
#endif
  if(id == next[prev[id]]){//add
    s[type]--;
    head[type] = s_next[id];
    next[prev[id]] = next[id];
    prev[next[id]] = prev[id];
  }else{//removed
    s[type]++;
    head[type] = next[id];
    next[id] = next[prev[id]];
    prev[next[id]] = id;
    next[prev[id]] = id;
  }
}

#endif // __ADDIBLELIST__
