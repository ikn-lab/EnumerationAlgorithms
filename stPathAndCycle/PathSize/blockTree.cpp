#include<iostream>
using namespace std;

BlockTree::BlockTree(int n){
  bt.init(n);
  g.init(n);
  ord.resize(n);
  low.resize(n);
  v_to_bt.resize(n, -1);
}
