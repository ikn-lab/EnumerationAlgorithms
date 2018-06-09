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
  inline int size(){return s;};
private:
  std::vector<T> vt;
  int s = 0;
};

template<typename T>
class FixedQueue{
public:
  FixedQueue(){};
  FixedQueue(int n){vt.resize(n);}
  inline void resize(int n){vt.resize(n);}
  inline bool push(T item);
  inline T front();
  inline bool pop();
  inline bool empty(){return s == 0;};
  inline bool clear(){s = start = 0;};
  inline int size(){return s;};
private:
  std::vector<T> vt;
  int s = 0, start = 0;
};



template<typename T>
bool FixedStack<T>::push(T item){
#ifdef DEBUG
  if(vt.size() == s){
    std::cerr << "FixedStack size is over " << vt.size() << std::endl;
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
    std::cerr << "FixedStack is empty" << std::endl;
    exit(1);
  }
#endif
  return vt[s - 1];
};

template<typename T>
bool FixedStack<T>::pop(){
#ifdef DEBUG
  if(vt.size() == 0){
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
  if(vt.size() == s){
    std::cerr << "FixedQueue size is over " << vt.size() << std::endl;
    return false;
  }
#endif
  if(start + s >= vt.size())vt[start + s++ - vt.size()] = item;
  else vt[start + s++] = item;
  return true;
}

template<typename T>
T FixedQueue<T>::front(){
#ifdef DEBUG
  if(s == 0){
    std::cerr << "FixedQueue is empty" << std::endl;
    exit(1);
  }
#endif
  return vt[start];
};

template<typename T>
bool FixedQueue<T>::pop(){
#ifdef DEBUG
  if(vt.size() == 0){
    std::cerr << "FixedQueue size is zero" << std::endl;
    return false;
  }
#endif
  --s;
  if(++start >= vt.size()) start -= vt.size();
  return true;
}

#endif // __BASICDATASTRUCTRUE__
