#include<iostream>

#include"Enum.hpp"
#include"Graph.hpp"

void EMDS::init(std::vector<vector<edge> > &H){
  int n = H.size();
  G.init(H);
}

void EMDS::Enumerate(){
  if(G.size() == 0){
    
  }
}
