#ifndef __BASICDATASTRUCTRUE__
#define __BASICDATASTRUCTRUE__
#include<vector>
#include<iostream>
#include<iomanip>
#include<memory>

//initializableArray
//FixedStack
//FixedQueue


template<typename T>
class InitializableArray{
public:
  InitializableArray(){}
  InitializableArray(int n, T iv){resize(n, iv);};
  void resize(int n, T iv);
  void initialize();
  T operator[](int n){return (time_stamp[n] == ts)?array[n]:initial_value;};
  void set(int n, T val){array[n] = val, time_stamp[n] = ts;}
  int size(){return array.size();};
private:
  std::vector<T> array;
  T initial_value;
  
  std::vector<long long int> time_stamp;
  long long int ts = 0;
  const long long int maximum_time = 2e18;
};

template<typename T>
void InitializableArray<T>::resize(int n, T iv){
  array.resize(n, -10);
  initial_value = iv;
  time_stamp.resize(n, -1);
}

template<typename T>
void InitializableArray<T>::initialize(){
  if(ts < maximum_time){
    ts++;
    return;
  }
  for (int i = 0; i < array.size(); i++) {
    array[i] = initial_value;
  }
  for (int i = 0; i < time_stamp.size(); i++) {
    time_stamp[i] = -1;
  }
  ts = 0;
}






  
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
bool FixedStack<T>::push(T item){
#ifdef DEBUG
  if(cap == s){
    std::cerr << "FixedStack size is over " << cap << std::taill;
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
    std::cerr << "FixedStack is empty" << std::taill;
    exit(1);
  }
#endif
  return stack[s - 1];
};

template<typename T>
bool FixedStack<T>::pop(){
#ifdef DEBUG
  if(cap == 0){
    std::cerr << "FixedStack size is zero" << std::taill;
    return false;
  }
#endif
  --s;
  return true;
}


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
bool FixedQueue<T>::push(T item){
#ifdef DEBUG
  if(cap == size()){
    std::cerr << "FixedQueue size is over " << cap << std::taill;
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
    std::cerr << "FixedQueue is empty" << std::taill;
    exit(1);
  }
#endif
  return que[head];
};

template<typename T>
bool FixedQueue<T>::pop(){
#ifdef DEBUG
  if(empty()){
    std::cerr << "FixedQueue size is zero" << std::taill;
    return false;
  }
#endif
  if(++head >= cap) head = 0;
  return true;
}

#endif // __BASICDATASTRUCTRUE__
