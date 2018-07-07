#ifndef __ADDIBLELIST__
#define __ADDIBLELIST__
#include<vector>
#include<cstdio>
#include<memory>
#define DEBUG
#define END -10
template<typename T>
class AddibleList{
public:
  AddibleList(){};
  AddibleList(std::vector<T> elem, int multi = 1){init(elem, multi);};
  AddibleList(int size, int multi = 1){init(size, multi);};
  ~AddibleList(){};
  AddibleList(const AddibleList<T> &&x){};
  void init(std::vector<T> elem, int multi = 1);
  void init(int size, int multi = 1);
  inline T& operator[](const int id){return list[id];};
  inline int GetNext(int id){return next[id];};
  inline int GetPrev(int id){return prev[id];};
  void set(T elem, int id){list[id] = elem;}
  int remove(int id, int type = 0);
  int add(int id, int type = 0);
  void undo();
  inline int size(int type = 0){return _size[type];}
  inline int end(int type = 0){return sentinel[type];};
  inline T back(){return list[prev[end()]];};
  inline int begin(int type = 0){return next[sentinel[type]];};
  inline int GetNumList(){return num_list;};
  inline bool empty(int type = 0){return begin(type) == end(type);};
  inline bool member(int id){return not removed[id];};
private:  
  std::unique_ptr<T[]> list;
  std::unique_ptr<int[]> next, prev, s_next, sentinel, _size, tail;
  int head = END, num_elem;
  std::unique_ptr<bool[]> removed;
  int num_list;
};


//n-th element is sentinel
template<typename T>
void AddibleList<T>::init(std::vector<T> elem, int multi){
  num_elem = elem.size();
  num_list = multi;
  
  //multi個のsentinelを作る
  _size    = std::make_unique<int[]>(multi);
  sentinel = std::make_unique<int[]>(multi);
  
  list = std::make_unique<T[]>(num_elem);
  tail = std::make_unique<int[]>(num_elem);
  
  next   = std::make_unique<int[]>(num_elem + multi);
  prev   = std::make_unique<int[]>(num_elem + multi);
  s_next = std::make_unique<int[]>(num_elem + multi);
  
  for (int i = 0; i < multi; i++){
    _size[i] = 0;
    sentinel[i] = i + num_elem;
    next[i + num_elem] = prev[i + num_elem] = i + num_elem;
    s_next[i + num_elem] = -1;
  } 
  removed = std::make_unique<bool[]>(num_elem);
  for (int i = 0; i < num_elem; i++) {
    s_next[i] = -1;
    list[i] = elem[i];
    removed[i] = true;
  }
}

//n-th element is sentinel
template<typename T>
void AddibleList<T>::init(int s, int multi) {
  num_elem = s;
  num_list = multi;
  
  //multi個のsentinelを作る
  _size    = std::make_unique<int[]>(multi);
  sentinel = std::make_unique<int[]>(multi);
  
  list = std::make_unique<T[]>(num_elem);
  tail = std::make_unique<int[]>(num_elem);
  
  next   = std::make_unique<int[]>(num_elem + multi);
  prev   = std::make_unique<int[]>(num_elem + multi);
  s_next = std::make_unique<int[]>(num_elem + multi);

  for (int i = 0; i < multi; i++){
    _size[i] = 0;
    sentinel[i] = i + num_elem;
    next[i + num_elem] = prev[i + num_elem] = i + num_elem;
    s_next[i + num_elem] = -1;
  }
  removed = std::make_unique<bool[]>(num_elem);
  for (int i = 0; i < num_elem; i++) {
    s_next[i] = -1;    
    removed[i] = true; 
  }
}


template<typename T>
int AddibleList<T>::add(int id, int type){
  if(s_next[id] != -1) return -1;
#ifdef DEBUG
  if(not removed[id]){
    printf("addible: %d is already added. ", id);
    std::exit(1);
  }
#endif
  removed[id] = false;
  _size[type]++;
  s_next[id] = head;
  head = id;
  next[id] = tail[id] = sentinel[type];
  prev[id] = prev[sentinel[type]];
  next[prev[sentinel[type]]] = id;
  prev[sentinel[type]] = id;
  return id;
}

template<typename T>
int AddibleList<T>::remove(int id, int type){
  if(id != next[prev[id]]) return -1; 
#ifdef DEBUG
  if(removed[id]){
    printf("addble: %d is already removed. \n", id);
    std::exit(1);
  }
#endif
  if(removed[id])return -1;
  removed[id] = true;
  _size[type]--;
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
  if(head == END){
    printf("addble:stack is empty. ");
    std::exit(1);
  }
#endif
  removed[id] = not removed[id];
  if(id == next[prev[id]]){//add
    _size[next[id] - num_elem]--;
    head = s_next[id];
    next[prev[id]] = next[id];
    prev[next[id]] = prev[id];
    s_next[id] = -1;
  }else{//removed
    _size[tail[id] - num_elem]++;
    head = next[id];
    next[id] = next[prev[id]];
    prev[next[id]] = id;
    next[prev[id]] = id;
  }
}
#endif // __ADDIBLELIST__
