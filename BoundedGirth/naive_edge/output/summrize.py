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
    margin   = 35
    if dir_name[0] == "all" and len(dir_name) == 1:
        dir_name = subprocess.check_output("ls")
        dir_name = split(dir_name)
    dir_names = [s for s in dir_name if ".py" not in s]
    print(dir_names)
    for i in dir_names:
        os.chdir(i)
        types = subprocess.check_output("ls")
        types = split(types)
        types = [s for s in types if ".csv" not in s]
        hoge = open("BoundedGirth"+ i + ".csv", "w")
        for j in types:
            os.chdir(j)
            files = subprocess.check_output("ls")
            # print(files)
            files = split(files)
            files = [s for s in files if ".out" in s]
            log = open("outSum.csv", "w")
            summary = ""
            # high/10_2/01.outみたいなファイル
            for k in files:
                summary += k + " "
                tmp = subprocess.check_output("wc -l " + k, shell=True)
                tmp = split(tmp)
                num_column = int(tmp[0])
                print(k + " " + str(num_column), margin - num_column)
                if margin - num_column < 0:
                    tmp = subprocess.check_output("head -" + str(margin) + " " + k , shell=True) 
                    f = open(k, "w")
                elif num_column < margin:
                    tmp  = subprocess.check_output("cat " + k, shell=True)
                    f = open(k, "w")
                    for x in range(0, margin + 1 - num_column):
                        tmp = tmp + "\n"
                print >> f, tmp
                f.close()
            print >> log, subprocess.check_output("paste -d\",\" " + summary, shell=True)
            log.close()
            # subprocess.check_output("cat " + k, shell=True)
            # txt = 
            # print(txt)
            # print >> log, subprocess.check_output("tail -n +4 " + input_files_name ,shell=True)
            # output = subprocess.check_output("ls")
            # print(output)
            print >> hoge, subprocess.check_output("paste -d\",\" " + summary, shell=True)
            os.chdir("..")
        print(i)
        hoge.close()
        os.chdir("..")
if __name__ == '__main__':
    main()
