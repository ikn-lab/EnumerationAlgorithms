$\newcommand{\size}[1]{|#1|}$
#s-t PathとCycleの列挙アルゴリズム
以下の論文の内容を実装した．

* 論文: Optimal Listing of Cycles and st-Paths in Undirected Graphs
* 著者: Etienne Etienne Birmele, Rui Ferreira, Roberto Grossi, Andrea Marino, Romeo Rizzi, Gustavo Sacomoto, Nadia Pisanti
* 会議/雑誌: SIAM
* 計算量: $O(\size{\pi})$と$O(\size{C})$．($\pi$を列挙するパス，$C$を列挙するサイクルとする．)

簡単な解説: 分割法で列挙する．まず，s-t pathが高速に列挙できるとサイクルの列挙ができることがわかる．なぜなら，グラフの全域木を考えて，全域木に含まれる辺をtree edge，それ以外の辺をback edgeとよぶと，あるback edge eの両端点をsとtとするs-t pathを列挙することで，eを含むサイクルが列挙できるからである．

s-t pathの列挙するために，block treeというデータ構造(グラフ構造?)を考える．これは，あるグラフ$G$から次のような操作で作る木$T$である．$T$は$G$の2-連結成分(関節点を含まない連結成分)と関節点を頂点とし，2-連結成分が関節点が含まれていればその間には辺をもつ木である．
この木上で，s-t pathを持つように管理しながら元のグラフ上で，s-t pathを列挙していく．