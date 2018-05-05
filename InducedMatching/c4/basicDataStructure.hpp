#ifndef __BASICDATASTRUCTRUE__
#define __BASICDATASTRUCTRUE__
#include<vector>
#include<iostream>

template<typename T>
class FixedStack{
public:
  FixedStack(){};
  FixedStack(int n){vt.resize(n);}
  inline void resize(int n){vt.resize(n);}
  inline bool push(T item);
  inline T top();
  inline bool pop();
  inline bool empty(){return s == 0;};
  inline bool clear(){s = 0; return true;};
  inline int size(){return s;};
private:
  std::vector<T> vt;
  int s = 0;
};

template<typename T>
class FixedQueue{
public:
  FixedQueue(){};
  FixedQueue(int n){vt.resize(n + 1), cap = n;}
  inline void resize(int n){vt.resize(n + 1), cap = n;}
  inline bool push(T item);
  inline T front();
  inline bool pop();
  inline bool empty(){return tail == head;};
  inline bool clear(){tail = head = 0; return true;};
  inline int size(){return (tail - head < 0)?tail + vt.size() - head:tail - head;};
  inline int end(){return tail;}
  inline T operator[](const int p){return vt[p];}
private:
  std::vector<T> vt;
  int tail = 0, head = 0, cap;
};



template<typename T>
bool FixedStack<T>::push(T item){
#ifdef DEBUG
  if(vt.size() == s){
    std::cerr << "FixedStack size is over " << vt.size() << std::taill;
    return false;
  }
#endif
  vt[s++] = item;
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
  return vt[s - 1];
};

template<typename T>
bool FixedStack<T>::pop(){
#ifdef DEBUG
  if(vt.size() == 0){
    std::cerr << "FixedStack size is zero" << std::taill;
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
    std::cerr << "FixedQueue size is over " << vt.size() << std::taill;
    return false;
  }
#endif
  vt[tail++] = item;
  if(tail >= vt.size()) tail = 0;
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
  return vt[head];
};

template<typename T>
bool FixedQueue<T>::pop(){
#ifdef DEBUG
  if(empty() == 0){
    std::cerr << "FixedQueue size is zero" << std::taill;
    return false;
  }
#endif
  if(++head >= vt.size()) head = 0;
  return true;
}

#endif // __BASICDATASTRUCTRUE__
