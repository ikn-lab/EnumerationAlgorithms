#!/usr/bin/env python
# -*- coding: utf-8 -*-
#!/usr/bin/env python
# -*- coding: utf-8 -*-
# いちいち一つずつ実行するのがめんどいからまとめてできるようにした．
# python exe.py 実行したいファイルがあるディレクトリ名 とするとグラフの密度を固定して，頂点サイズが異なるランダムデータと小さい閉路のないグラフの2種類のデータに対して実行する．
import time, os, sys, signal
from os.path import join,getsize
import datetime
import subprocess
import sys
from sh import tail
from sh import wc
from sh import echo
from sh import head
from sh import paste

def split(names):
    names = names.replace("\n", " ")
    names = names.split(" ")
    names = names[0:len(names) - 1]
    return names

def main():
    dir_name = [sys.argv[1]]
    margin   = 80
    if dir_name[0] == "all" and len(dir_name) == 1:
        dir_name = subprocess.check_output("ls")
        dir_name = split(dir_name)
    dir_names = [s for s in dir_name if ".py" not in s]
    print(dir_names)
    for i in dir_names:
        os.chdir(i)
        subprocess.call("pwd",shell=True)
        types = subprocess.check_output("ls")
        types = split(types)
        types = [s for s in types if ".csv" not in s]
        hoge = open("DominatingSets"+ i + ".csv", "w")
        for j in types:
            print(j)
            os.chdir(j)
            files = subprocess.check_output("ls")
            # print(files)
            files = split(files)
            files = [s for s in files if ".out" in s]
            log = open("outSum.csv", "w")
            summary = ""
            # high/10_2/01.outみたいなファイル
            for k in files:
                subprocess.call("cp -f org/org_" + k + " " + k, shell=True)
            os.chdir("..")
        os.chdir("..")
if __name__ == '__main__':
    main()
