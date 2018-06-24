#include<random>
#include<vector>
#include<string>
#include<set>
#include<iostream>
#include<algorithm>
#include<queue>
#include<fstream>
#include<cstring>
#include<ctime>
typedef std::pair<int, int> pii;
typedef std::pair<int, pii> piii;

std::mt19937 mt((int)time(0));

void randomGraph(std::ofstream &output_file, int n, double density = -1){
  std::set<pii> edge;
  if(density == -1)density = sqrt(n)*n/2;
  int cnt = 0;
  while((double)edge.size()/n < density){
    if(cnt > 5000){
      break;
    }
    pii add = pii(mt()%n, mt()%n);
    if(add.first == add.second){
      cnt++;
      continue;
    }
    pii rev = pii(add.second, add.first);
    if(edge.find(add) != edge.end() or
       edge.find(rev) != edge.end()){
      cnt++;
      continue;
    }
    edge.insert(add);
    cnt = 0;
  }
  output_file << n << " " << edge.size() << std::endl;
  for (auto add: edge) {
    output_file << add.first << " " << add.second << std::endl;
  }
}

int main(int argc, char *argv[]){
  double density;
  int n;
  if(argc == 3){
    n = atoi(argv[1]), density = atof(argv[2]); 
  }else{
    std::cerr << "Enter the number of vertices and density." << std::endl;
    exit(1);
  }
  std::string name;
  std::cout << "Generate random graphs." << std::endl;
  for (int i = 1; i <= 7; i++) {
    char tmp[5];
    sprintf(tmp, "%02d", i);
    std::string id = tmp;
    name = "random" + std::to_string(density).substr(0, 5) + "_" + id + ".in";
    std::cout << name << std::endl;
    // std::cout << "generate random case" << std::endl;
    std::ofstream output_file(name.c_str());
    randomGraph(output_file, n, density);
    output_file.close();
  }
  return 0;
}
