#include<iostream>
#include<cstdio>

#include"EdgeList.hpp"


EdgeList::EdgeList(){
  elist.push_back(edge{-1, -1, -1, 0, -1, 1, -1});
  elist.push_back(edge{-1, -1, -1, 1, -1, -1, 0});
}

void EdgeList::push_back(edge e){
  elist[elist[1].prev].next = elist[1].prev = elist.size();
  elist.push_back(e);
  elist.back().next = 1;
  elist.back().prev = elist.size() - 2;
}

void EdgeList::push_back(int id){
  add.push(id);
  elist[id].prev = elist[1].prev;
  elist[elist[1].prev].next = elist[1].prev = id;
  elist[id].next = 1;
}

void EdgeList::UndoAdd(){
  if(add.empty()){
    std::cerr << "add is empty(edge)" << std::endl;
    exit(1);
  }
  int id = add.top();
  add.pop();
  elist[elist[id].prev].next = elist[id].next;
  elist[elist[id].next].prev = elist[id].prev;
}


void EdgeList::print(){
  std::cout << std::endl;
  std::cout << "print elist" << std::endl;
  for (int i = elist[0].next; i < (int)elist.size() - 1; i=elist[i].next) {
    std::cout << "from:" << i << " to:" << elist[i].to << std::endl;
  }
  std::cout << std::endl;
}

void EdgeList::RemoveEdge(int id){
  st.push(id);
  elist[elist[id].prev].next = elist[id].next;
  elist[elist[id].next].prev = elist[id].prev;
}

void EdgeList::RestoreEdge(){
  if(st.empty()){
    std::cerr << "stack is empty(edge)" << std::endl;
    exit(1);
  }
  int id = st.top();
  st.pop();
  elist[elist[id].prev].next = id;
  elist[elist[id].next].prev = id;
}
