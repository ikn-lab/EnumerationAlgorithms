////////////////////////////////////////
/*                                    */
/* Enumeration of independnet set     */
/* O(1) time per solution             */
/* constraint: \omega(G) is constant  */
/* kurita                             */
/*                                    */
////////////////////////////////////////

#include<iostream>
#include<vector>
#include<fstream>
#include<memory>
#include<queue>
#include<stack>
#include<chrono>
using namespace std;
//List.hpp#include<chrono>
#ifndef __LIST__
#define __LIST__

template<typename T>
class List{
public:
  List(){};
  List(std::vector<T> elem){init(elem);};
  List(int size){init(size);};
  ~List(){};
  List(List&& x){};
  void init(std::vector<T> elem);
  void init(int size);
  inline T& operator[](const int id){return list[id];};
  inline int GetNext(int id){return next[id];};
  inline int GetPrev(int id){return prev[id];};
  void set(T elem, int id){list[id] = elem;};
  int remove(int id);
  void undo();
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
  int tail, _size, head = -1;
};


//n-th element is sentinel
template<typename T>
void List<T>::init(std::vector<T> elem){
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
void List<T>::init(int size) {
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
int List<T>::remove(int id){
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
  next[id] = head;
  head = id;
  return prev[id];
}

template<typename T>
void List<T>::undo(){
#ifdef DEBUG
  if(head == -1){
    printf("stack is empty. ");
    std::exit(1);
  }
#endif
  removed[head] = false;
  _size++;
  int id = head;
  head = next[id];
  next[id] = next[prev[id]];
  prev[next[id]] = id;
  next[prev[id]] = id;
}

#endif // __LIST__

#ifndef __BASICDATASTRUCTRUE__
#define __BASICDATASTRUCTRUE__

template<typename T>
class FixedStack{
public:
  FixedStack(){};
  FixedStack(int n):cap(n){stack = std::make_unique<T[]>(n);}
  inline void resize(int n){cap = n, stack = std::make_unique<T[]>(n);}
  inline bool push(T item);
  inline T top();
  inline bool pop();
  inline bool empty(){return s == 0;};
  inline bool clear(){s = 0; return true;};
  inline int size(){return s;};
private:
  std::unique_ptr<T[]> stack;
  int s = 0, cap;
};

template<typename T>
class FixedQueue{
public:
  FixedQueue(){};
  FixedQueue(int n){que = std::make_unique<T[]>(n + 1), cap = n;}
  inline void resize(int n){que = std::make_unique<T[]>(n + 1), cap = n;}
  inline bool push(T item);
  inline T front();
  inline bool pop();
  inline bool empty(){return tail == head;};
  inline bool clear(){tail = head = 0; return true;};
  inline int size(){return (tail - head < 0)?tail + cap - head:tail - head;};
  inline int end(){return tail;}
  inline T operator[](const int p){return que[p];}
private:
  std::unique_ptr<T[]> que;
  int tail = 0, head = 0, cap;
};



template<typename T>
bool FixedStack<T>::push(T item){
#ifdef DEBUG
  if(cap == s){
    std::cerr << "FixedStack size is over " << cap << std::endl;
    return false;
  }
#endif
  stack[s++] = item;
  return true;
}

template<typename T>
T FixedStack<T>::top(){
#ifdef DEBUG
  if(s == 0){
    std::cerr << "FixedStack is empty" << std::endl;
    exit(1);
  }
#endif
  return stack[s - 1];
};

template<typename T>
bool FixedStack<T>::pop(){
#ifdef DEBUG
  if(cap == 0){
    std::cerr << "FixedStack size is zero" << std::endl;
    return false;
  }
#endif
  --s;
  return true;
}

template<typename T>
bool FixedQueue<T>::push(T item){
#ifdef DEBUG
  if(cap == size()){
    std::cerr << "FixedQueue size is over " << cap << std::endl;
    return false;
  }
#endif
  que[tail++] = item;
  if(tail >= cap) tail = 0;
  return true;
}

template<typename T>
T FixedQueue<T>::front(){
#ifdef DEBUG
  if(empty()){
    std::cerr << "FixedQueue is empty" << std::endl;
    exit(1);
  }
#endif
  return que[head];
};

template<typename T>
bool FixedQueue<T>::pop(){
#ifdef DEBUG
  if(empty()){
    std::cerr << "FixedQueue size is zero" << std::endl;
    return false;
  }
#endif
  if(++head >= cap) head = 0;
  return true;
}

#endif // __BASICDATASTRUCTRUE__

using bigint = long long int;

class EIS{
public:
  EIS(std::vector<std::vector<int> > H);
  ~EIS(){};
  inline int size(){return G.size();}
  void Enumerate();
  void print();
private:
  void RecEnum(int v = 0);
  std::vector<std::vector<int> > G;
  List<int> cand;
  FixedStack<int> solution;
  std::vector<bigint> ans;
  std::vector<int> degList;
  int n;
    
};
// #define DEBUG

using bigint = long long int;

int main(){
  int n, m, cnt = 0;
  std::cin >> n >> m;
  std::vector<std::vector<int> > G(n, std::vector<int>(n, 1));
  for (int i = 0; i < n; i++) G[i][i] = 0;

  for (int i = 0; i < m; i++) {
    int u, v, w;
    std::cin >> u >> v >> w;
    u--, v--;
    G[u][v] = G[v][u] = 0;
  }
  EIS eis(G);
  // std::cout << "degeneracy:" << eds.GetDegeneracy() << std::endl;
  // std::cout << "n:" << eds.size() << std::endl;
  
  auto start = std::chrono::system_clock::now();
  eis.Enumerate();
  auto end = std::chrono::system_clock::now();
  auto diff = end - start;
  std::cout << "elapsed time = "
            << std::chrono::duration_cast<std::chrono::milliseconds>(diff).count()
            << " msec."
            << std::endl;  
  eis.print();
  // std::cout << "time:"
  //           << std::chrono::duration_cast<std::chrono::milliseconds>(eds.time).count()
  //           << std::endl;
  return 0;
}



#define INF 1e9
using bigint = long long int;

EIS::EIS(std::vector<std::vector<int> > H){
  n = H.size();
  ans.resize(n, 0);
  G.resize(H.size());
  solution.resize(n);
  for (int i = 0; i < n; i++) G[i].resize(n);
  for (int i = 0; i < n; i++) 
    for (int j = 0; j < n; j++)
      G[i][j] = H[i][j];
  std::vector<int> c(n);
  for (int i = 0; i < n; i++) c[i] = i;
  cand.init(c);
}


void EIS::Enumerate(){
  RecEnum();
}


void EIS::RecEnum(int v) {
  if(cand.member(v)){
    int stack = 0;
    cand.remove(v);
    if(cand.size() > 0) RecEnum(v + 1);
    else ans[solution.size()]++;
    for (int i = cand.begin(); i != cand.end(); i = cand.GetNext(i)) {
      if(G[v][i] == 1) i = cand.remove(i), stack++;
    }
    solution.push(v);
    if(cand.size() > 0) RecEnum(v + 1);
    else ans[solution.size()]++;
    solution.pop();
    for (int i = 0; i < stack + 1; i++) cand.undo();
  }else{
    if(cand.size() > 0) RecEnum(v + 1);
    else ans[solution.size()]++;
  }
}


void EIS::print(){
  int sum = 0;
  for (int i = 0; i < ans.size(); i++) sum += ans[i];
  std::cout << "sum:" << sum << std::endl;
  for (int i = 0; i < n; i++) {
    std::cout << "[" << i << "]:" << ans[i] << std::endl;
    if(ans[i] == 0)break;
  }
}
