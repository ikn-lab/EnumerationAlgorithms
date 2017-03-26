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
    directory = sys.argv[1]
    today = datetime.datetime.today()
    os.chdir(str(directory))
    print "hoge"
    commands.getoutput("make -B")
    commands.getoutput("mv output .output" + str('{0:02}'.format(today.month)) + str(today.day) + ":" + str(today.minute))
    commands.getoutput("mkdir output")
    os.chdir("../gen")
    for i in xrange(2, 17):
        for j in ["random", "no_short_cycle"]:
            density = i*0.5
            str_density = '{0:.02f}'.format(density)
            print str_density
            print 
            os.chdir("..")
            file_name = commands.getoutput("ls gen| grep " + j + str(density)  + ".*07.in").split(".in\n")
            print j + str(density)
            file_name[-1] = file_name[-1].rstrip(".in")
            print file_name
            for f in file_name:
                input_data = "gen/" + f
                input_data = input_data.replace(".in", "")
                cmd = "time ./" + directory + "/EIM " + input_data + ".in"
                output_file = "./" + directory + "/output/" + f  + ".out"
                print "execute", output_file
                log = open(output_file, "w")
                start = time.time()
                print >> log, commands.getoutput(cmd), "\ntime:", time.time() - start
                print time.time() - start
            os.chdir("gen")

if __name__ == '__main__':
    main()
