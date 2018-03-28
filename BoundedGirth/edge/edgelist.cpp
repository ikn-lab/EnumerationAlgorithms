#include<iostream>
#include<cstdio>

#include"EdgeList.hpp"


EdgeList::EdgeList(){
  elist.push_back(edge{-1, -1, -1, 0, -1, 1, -1});
  elist.push_back(edge{-1, -1, -1, 1, -1, -1, 0});
}

void EdgeList::push_back(edge e){
  std::cout << "push_back edge" << std::endl;
  print();
  elist[elist[1].prev].next = elist[1].prev = elist.size();
  elist.push_back(e);
  elist.back().next = 1;
  elist.back().prev = elist.size() - 2;
  print();
}

void EdgeList::push_back(int id){
  std::cout << "push_back int" << std::endl;
  if(used[id] == true or id == 0 or id == 1){
    std::cout << "error: push_back id" << std::endl;
    exit(1);
  }
  used[id] = true;
  print();
  add.push(id);
  elist[id].prev = elist[1].prev;
  elist[elist[1].prev].next = elist[1].prev = id;
  elist[id].next = 1;
  print();
}

void EdgeList::RemoveEdge(int id){
  std::cout << "remove edge" << std::endl;  
  print();
  if(used[id] == false or id == 0 or id == 1){
    printf("error: remove edge %d %d->%d\n", id , elist[id].from, elist[id].to);
    exit(1);
  }
  int loop = 0;
  for (int i = elist[1].prev; i != 0; i=elist[i].prev, loop++) {
    std::cout << elist[i].from << "->" << elist[i].to << " next:" << elist[i].next << " prev:" << elist[i].prev << std::endl;
    if(loop > 100)exit(1);
  }
  std::cout << std::endl;
  std::cout << std::endl;
  used[id] = false;
  st.push(id);
  
  elist[elist[id].prev].next = elist[id].next;
  elist[elist[id].next].prev = elist[id].prev;
  print();
}

void EdgeList::RestoreEdge(){
  std::cout << "restore edge" << std::endl;  
  print();
  if(st.empty()){
    std::cerr << "stack is empty(edge)" << std::endl;
    exit(1);
  }
  int id = st.top();
  st.pop();
  elist[elist[id].next].prev = id;
  elist[elist[id].prev].next = id;
  used[id] = true;
  print();
}

void EdgeList::UndoAdd(){
  std::cout << "undo" << std::endl;  
  print();
  if(add.empty()){
    std::cerr << "add is empty(edge)" << std::endl;
    exit(1);
  }
  int id = add.top();
  add.pop();
  elist[elist[id].next].prev = elist[id].prev;
  elist[elist[id].prev].next = elist[id].next;
  used[id] = false;
  print();
}


void EdgeList::print(){
  // std::cout << "print elist" << std::endl;
  for (int i = elist[0].next; i != 1; i=elist[i].next) {
    std::cout << elist[i].from << "->" << elist[i].to << " ";
  }
  std::cout << std::endl;
  std::cout << std::endl;
}

void EdgeList::AllUsed(){
  used.resize(elist.size(), true);
}

void EdgeList::NotUsed(){
  used.resize(elist.size(), false);
  used[0] = used[1] = true;
}

