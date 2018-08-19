$\newcommand{\set}[1]{\{ #1 \}}$
# WithoutShortCycle generatorの仕様

## コンパイル
g++ generator.cpp unionFind.cpp -o generator

## 使い方

- ./generator 頂点数 縮退数
- 出力: WithoutNoCycleWithLengthFour頂点数_密度_ID.in
- 
## 生成方法
random graph generator と同じようにrandom graphを生成し，生成したグラフが指定の密度を持ち，連結かつ長さ$4$のサイクルを持たないならば出力する．また，辺追加を$5000$回失敗した場合は，連結性と長さ$4$のサイクルを持たないことをチェックして出力する．

## 出力の仕様
長さ$4$のサイクルを持たない指定密度以下のグラフ．


## 出力フォーマット
頂点数$n$ 辺数$m$  
$v_1$ $u_1$  
$\vdots$  
$v_m$ $u_m$  

ここで，$u_i, v_i$は$0$以上$n - 1$以下である．

## メモ
cycleCheckerはテスト用プログラム．