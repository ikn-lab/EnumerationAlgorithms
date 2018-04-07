#include<iostream>
#include<vector>
#include<memory>

#include"Element.hpp"
#include"AddibleList.hpp"
// #include"Graph.hpp"

void print(AddibleList<int> &al, int type = 0){
  std::cout << "start print" << std::endl;
  std::cout << "size:" << al.size(type) << std::endl;
  for (int i = al.begin(type); i != al.end(type); i = al.GetNext(i)) {
    // std::cout << "i:" << i << std::endl;
    std::cout << al[i] << " ";
  }
  std::cout << std::endl;
}

int main(){
  std::vector<int> tmp;
  std::unique_ptr<edge[]> ptr, p;
  // std::unique_ptr<edge[]> ptr = std::make_unique<edge[]>(10);
  p = std::make_unique<edge[]>(10);
  for (int i = 0; i < 10; i++){
    tmp.push_back(i);
    p[i] = edge(i, i + 1, 0);
  } 
  AddibleList<int> al(tmp, 4);
  al.add(3, 0);
  al.add(5, 1);
  // al.remove(5, 1);
  print(al);
  print(al, 1);
  return 0;
}
