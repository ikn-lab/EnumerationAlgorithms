#include<iostream>
#include"graph.hpp"
#include"enum_naive.hpp"

int NaiveEnumeration(Graph &dag,
                     FILE *naive,
                     vector<int> v,
                     bool *used){
  if((int)v.size() == dag.size()){
    // for (int i = 0; i < v.size(); i++) {
    //   fprintf(naive, "%d ", v[i]);
    // }
    // fprintf(naive, "\n");
    return 1;
  }
  
  //initialize "used" array
  if(used == NULL){
    used = new bool[dag.size()];
    for (int i = 0; i < dag.size(); i++) {
      used[i] = false;
    }
  }
  
  int counter = 0;
  for (int i = 0; i < dag.size(); i++) {
    if(used[i] == true)continue;
    bool flag = true;
    for (int j = 0; j < (int)v.size(); j++) {
      if(dag[i][v[j]] == 1 && dag[v[j]][i] == -1){
        flag = false;
        break;
      }
    }
    if(flag == true){
      used[i] = true;
      v.push_back(i);
      counter += NaiveEnumeration(dag, naive, v, used);
      if(v.size() > 1)v.pop_back();
      else v.clear();
      used[i] = false;
    }
  }
  if(v.size() == 0){
    fprintf(naive, "%d\n", counter);
    std::cout << counter << std::endl;
  } 
  return counter;
}
