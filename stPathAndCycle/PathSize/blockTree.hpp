#ifndef __BLOCKTREE__
#define __BLOCKTREE__

#include"graph.hpp"

class BlockTree{
public:
  BlockTree(int n);
  void AddEdge(int from, int v);
  void RemoveVertex(int id);
  void RestoreVertex(int cnt = 1);
private:
  Graph g, bt;
  std::vector<int> v_to_bt, ord, low;
  int v_ord = 0, bt_size = 0;
  void dfs(int v = 0, int previous = -1);
}
#endif // __BLOCKTREE__
