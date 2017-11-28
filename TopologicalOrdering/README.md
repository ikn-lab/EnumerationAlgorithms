$\newcommand{\size}[1]{|#1|}$

#トポロジカルソート順の列挙アルゴリズム

以下の論文を実装した．

* 論文: reverse search for enumeration
* 著者: David Avis, Komei Fukuda
* 会議/雑誌: DAM

簡単な解説: 列挙アルゴリズムの構築法についての論文．解空間上に全域木を定義して，その木上をDFSすることで，列挙を行うという技法．

論文中ではこの技法を使って，連結な誘導部分グラフの列挙やトポロジカルソートの列挙を行なっていたので，今回はトポロジカルソートの実装をしてみた．論文中の実装では，計算時間は$O(\size{V})$である．ただし，定数時間列挙アルゴリズムも実装した．