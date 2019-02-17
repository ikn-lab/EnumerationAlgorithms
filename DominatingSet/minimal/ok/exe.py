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
    num_v     = sys.argv[1]
    parameter = sys.argv[2]
    path      = sys.argv[3]
    num_p     = 4
    today = datetime.datetime.today()
    dir_names = commands.getoutput("ls " + path)
    dir_names = dir_names.replace("\n", " ")
    dir_names = dir_names.split(" ")
    commands.getoutput("make")
    print(dir_names)

    if len(sys.argv) == num_p:
        commands.getoutput("mkdir output")
    elif len(sys.argv) == num_p + 1:
        commands.getoutput("mkdir output_pruning")

    for i in dir_names:
        if i != "H"
        if i == "PowerLaw":
            commands.getoutput("./" + path + "/" + i + "/graph/generator.py " + num_v + " " + parameter) 
            commands.getoutput("./" + path + "/" + i + "/tree/generator.py "  + num_v + " " + parameter) 
        else: 
            commands.getoutput("./" + path + "/" + i + "/generator "  + num_v + " " + parameter) 
        # print(input_files)
        input_files = commands.getoutput("ls | grep .in")
        input_files = input_files.replace("\n", " ")
        input_files = input_files.split(" ")
        input_files = [s for s in input_files if '.in' in s]
        print(input_files)
        for j in input_files:
            if len(sys.argv) == num_p:
                commands.getoutput("mkdir output/" + j[0:10] + "/")
                commands.getoutput("mkdir output/" + j[0:10] + "/" + num_v + "_" + parameter)
                commands.getoutput("mkdir output/" + j[0:10] + "/" + num_v + "_" + parameter + "/input_data")
                output_file = "./output/" + j[0:10] + "/" + num_v + "_" + parameter + "/" + j[len(j) - 5:len(j) - 3] + ".out"
            elif len(sys.argv) == num_p + 1:
                commands.getoutput("mkdir output_pruning/" + j[0:10] + "/")
                commands.getoutput("mkdir output_pruning/" + j[0:10] + "/" + num_v + "_" + parameter)
                commands.getoutput("mkdir output_pruning/" + j[0:10] + "/" + num_v + "_" + parameter + "/input_data")
                output_file = "./output_pruning/" + j[0:10] + "/" + num_v + "_" + parameter + "/" + j[len(j) - 5:len(j) - 3] + ".out"
            print(output_file)
            print("execute " + output_file)
            log = open(output_file, "w")
            start = time.time()
            cmd = "./EDS " + j
            print >> log, commands.getoutput(cmd)# , "\ntime:", time.time() - start
            print time.time() - start
            print
            if len(sys.argv) == num_p:
                commands.getoutput("mv " + j + " output/" + j[0:10] + "/" + num_v + "_" + parameter + "/input_data")
            elif len(sys.argv) == num_p + 1:
                commands.getoutput("mv " + j + " output_pruning/" + j[0:10] + "/" + num_v + "_" + parameter + "/input_data")

if __name__ == '__main__':
    main()
