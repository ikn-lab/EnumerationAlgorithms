$\newcommand{\set}[1]{\{ #1 \}}$
# HighAveDegLowDegeneracy generatorの仕様

## コンパイル
g++ generator.cpp unionFinde.cpp -o generator

## 使い方

- ./generator 頂点数 縮退数
- 出力: HighAveDegLowDegeneracy頂点数_縮退数_ID.in
- 
## 生成方法
それぞれの頂点$i$に対し，c++のmt()関数を用いて，$i + 1$から$n - 1$までの乱数$x$を生成し，組$\set{i, x}$が以前に生成した組と異なればグラフに辺として追加する．そうでない場合，組を生成し直す．$i$に対し，指定された縮退数と同じ本数の辺か，$n - i$本の辺を追加する．これを全ての頂点に行い，グラフを出力する．

## 出力の仕様
縮退数$k$の最密グラフ，つまり$kn - \frac{k(k + 1)}{2}$本の辺を持つグラフ．


## 出力フォーマット
頂点数$n$ 辺数$m$  
$v_1$ $u_1$  
$\vdots$  
$v_m$ $u_m$  

ここで，$u_i, v_i$は$0$以上$n - 1$以下である．