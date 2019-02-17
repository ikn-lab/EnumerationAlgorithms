#ifndef __BASICDATASTRUCTRUE__
#define __BASICDATASTRUCTRUE__
#include<vector>
#include<iostream>
#include<memory>

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
