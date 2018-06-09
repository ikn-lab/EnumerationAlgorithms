#ifndef REVERSE_SEARCH_PRAIVATE_PARALLEL_HPP
#define REVERSE_SEARCH_PRAIVATE_PARALLEL_HPP
#include<thread>
#include<queue>
#include<future>
#include<vector>
#include<unistd.h>

template<typename T>
void ReverseSearchParallel<T>::
dfs(const T S, std::promise<int> res){
  int counter = 1;
  //neighbor_counter
  int j;
  T v, next;
  v = S;
  j = -1;
  while(!(v == S && j == delta)){
    while(j < delta){
      j++;
      next = Adj(v, j);
      if(next != S){
        //reverse traverse
        if(LocalSearch(next) == v){
          v = next;
          j = -1;
        }
      }
    }
    //forward traverse
    if(v != S){
      //mtx.lock();
      counter++;
      //mtx.unlock();
      T u = v;
      v = LocalSearch(v);
      j = 0;
      while(Adj(v, j) != u)j++;
      //std::cout << j << std::endl;
    }
  }
  res.set_value(counter);
}

template<typename T>
void ReverseSearchParallel<T>::
Search(FILE *output_file){
  //int vnum = boost::thread::hardware_concurrency();  // 論理コア数
  int pnum = sysconf(_SC_NPROCESSORS_ONLN);
  //int pnum = boost::thread::physical_concurrency();  // 物理コア数
  std::vector<std::thread> threads;

  std::vector<std::promise<int> > vp;
  std::vector<std::future<int> > vf;
  int counter = 1;
  //neighbor_counter
  int j;
  T v, next;
  queue<T> que;
  for (int i = 0; i < S.size(); i++) {
    que.push(S[i]);
  }
  j = -1;
    v = que.front();
    que.pop();
    //while(!(v == S[i] && j == delta)){
    while(j < delta){
      j++;
      next = Adj(v, j);
      if(next != init_val){
        //push next v
        if(LocalSearch(next) == v){
          vp.push_back(std::promise<int>());
          vf.push_back(vp.back().get_future());
          threads.push_back(std::thread(&ReverseSearchParallel<T>::dfs, this, next, std::move(vp.back())));
          //counter++;
        }
      }
    }

  int tmp;  
  for(int i = 0; i < vf.size(); i++){
    tmp = vf[i].get();
    std::cout << "tmp:" << tmp << std::endl;
    ///counter += vf[i].get();
  }
  
  for(auto& t:threads){
    t.join();
  }

  fprintf(output_file, "%d\n", counter);
  std::cout << counter << std::endl;
  return;
}


// template<typename T>
// void ReverseSearch<T>::
// Search(FILE *output_file){
//   int counter = 1;
//   //neighbor_counter
//   int j;
//   T v, next;
//   for (int i = 0; i < S.size(); i++) {
//     v = S[i];
//     j = -1;
//     while(!(v == S[i] && j == delta)){
//       while(j < delta){
//         j++;
//         next = Adj(v, j);
//         if(next != init_val){
//           //reverse traverse
//           if(LocalSearch(next) == v){
//             v = next;
//             j = -1;
//           }
//         }
//       }

//       //forward traverse
//       if(v != S[i]){
//         counter++;
//         T u = v;
//         v = LocalSearch(v);
//         j = 0;
//         while(Adj(v, j) != u)j++;
//         //std::cout << j << std::endl;
//       }
//     }
//   }
//   fprintf(output_file, "%d\n", counter);
//   std::cout << counter << std::endl;
//   return;
// }

#endif
