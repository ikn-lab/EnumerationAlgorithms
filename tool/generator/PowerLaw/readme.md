#PowerLaw generatorの仕様
グラフの生成にはpythonのライブラリを使用している．
networkxのpowerlaw_cluster_graphとrandom_powerlawtreeを使用している．

## 使い方

- ./generator_HK_power.py
- ./generator_power_tree.py
- 出力: 標準出力

## 生成方法
ライブラリをそのまま使っているだけ．

## 出力フォーマット
頂点数$n$ 辺数$m$  
$v_1$ $u_1$  
$\vdots$  
$v_m$ $u_m$  

ここで，$u_i, v_i$は$0$以上$n - 1$以下である．