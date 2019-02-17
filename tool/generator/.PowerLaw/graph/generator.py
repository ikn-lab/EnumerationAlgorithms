#!/usr/bin/env python3
# -*- coding: utf-8 -*-
import networkx as nx
import sys
from numpy.random import *

args = sys.argv
a, b = int(args[1]), int(int(args[1])/2)
seed(114)
for i in range(1, 11):
    G = nx.powerlaw_cluster_graph(a, b, rand())
    n, m = len(list(G.nodes)), len(list(G.edges))
    name = "PowerLawGraph" + str(n) + "_" + str(m/n)[0:3] + "_" + str('{0:02d}'.format(i)) + ".in"
    file = open(name, 'w')
    print(name)
    print(n, " ", end="")
    print(m)
    file.write(str(n) + " " + str(m) + "\n")
    for e in list(G.edges):
        print(e[0], " ", end="")
        print(e[1])
        file.write(str(e[0]) + " " + str(e[1]) + "\n")
