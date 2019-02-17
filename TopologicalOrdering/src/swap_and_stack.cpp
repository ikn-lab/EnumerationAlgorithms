#include<stack>
#include"graph.hpp"
#include"topological.hpp"
#include"swap_and_stack.hpp"
using namespace std;

void SwapAndStack::
init(Graph &G_){
  G  = G_;
  tp = topoSort(G);
}

int SwapAndStack::
minIndex(vector<int> &v){
  int res = -1;
  for (int i = 0; i < v.size() - 1; i++) {
    if(!(v[i] > v[i + 1] && !G.isEdge(tp[ v[i] ], tp[ v[i + 1] ])))continue;
    res = i;
    break;
  }
  return res;
}


void SwapAndStack::
Search(FILE *output_file){
  //neighbor_counter
  int j = -1;
  int back = 0, counter = 1;
  vector<int> v(G.size()), s(G.size()), next(G.size());
  for (int i = 0; i < G.size(); i++) {
    v[i] = s[i] = next[i] = i;
  }
  next[0] = 1;
  next[1] = 0;
  stack<int> st;
  while(!(v == s && j == G.size() - 1)){
    swap(next[back], next[back + 1]);
    while(++j < G.size() - 1){
      if(G.isEdge(tp[ v[j] ], tp[ v[j + 1] ]) == false){
        swap(next[j], next[j + 1]);
        back = minIndex(next);
        //reverse traverse
        if(back != j){
          swap(next[j], next[j + 1]);
        }else{
          st.push(j);
          swap(v[back], v[back + 1]);
          j = -1;
        }
      }
    }
    //forward traverse
    if(v != s){
      //printPerm(v, rev);
      counter++;
      j = st.top();
      back = j;
      swap(v[st.top()], v[st.top() + 1]);
      st.pop();
    }
  }
  fprintf(output_file, "%d\n", counter);
  return;
}
