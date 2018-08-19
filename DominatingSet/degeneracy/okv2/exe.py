#!/usr/bin/env python
# -*- coding: utf-8 -*-
# いちいち一つずつ実行するのがめんどいからまとめてできるようにした．
# python exe.py 実行したいファイルがあるディレクトリ名 とするとグラフの密度を固定して，頂点サイズが異なるランダムデータと小さい閉路のないグラフの2種類のデータに対して実行する．
import time, os, sys, signal
from os.path import join,getsize
import datetime
import commands
import sys

def main():
    # girth = sys.argv[1]
    num_v = sys.argv[1]
    today = datetime.datetime.today()
    # os.chdir(str(directory))
    commands.getoutput("make")
    # commands.getoutput("mv output .output" + str('{0:02}'.format(today.month)) + str(today.day) + ":" + str(today.minute))
    commands.getoutput("mkdir output")
    dir_names = commands.getoutput("ls ../../../tool/generator/")
    dir_names = dir_names.replace("\n", " ")
    dir_names = dir_names.split(" ")
    print(dir_names)
    for i in dir_names:
        if i == "PowerLaw":
            input_files_graph = commands.getoutput("ls ../../../tool/generator/" + i + "/" + num_v + "/graph/")
            input_files_tree  = commands.getoutput("ls ../../../tool/generator/" + i + "/" + num_v + "/tree/")
            input_files = input_files_graph + "\n" + input_files_tree
        else: 
            input_files = commands.getoutput("ls ../../../tool/generator/" + i + "/" + num_v )
        print(commands.getoutput("ls ../../../tool/generator/" + i + "/" + num_v ))
        # print(input_files)
        input_files = input_files.replace("\n", " ")
        input_files = input_files.split(" ")
        input_files = [s for s in input_files if '.in' in s]
        # print(input_files)
        for j in input_files:
            output_file = "./output/" + j[0:len(j) - 3] + ".out"
            print("execute " + output_file)
            log = open(output_file, "w")
            start = time.time()
            cmd = "./EDS ../../../tool/generator/" + i + "/" + num_v + "/" + j
            print >> log, commands.getoutput(cmd)# , "\ntime:", time.time() - start
            print time.time() - start
            print

if __name__ == '__main__':
    main()
