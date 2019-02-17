#!/usr/bin/env python3
# -*- coding: utf-8 -*-
import networkx as nx
import sys
from numpy.random import *

args = sys.argv
seed(114)
a = int(args[1])
# T = nx.random_powerlaw_tree(50, 2, 14, 10)
for i in range(1, 11):
    T = nx.random_powerlaw_tree(a, tries=4000)
    n, m = len(list(T.nodes)), len(list(T.edges))
    name = "PowerLawTree" + str(n) + "_" + str('{0:02d}'.format(i)) + ".in"
    file = open(name, 'w')
    print(n, m)
    file.write(str(n) + " " + str(m) + "\n")
    for e in list(T.edges):
        print(e[0], " ", end="")
        print(e[1])
        file.write(str(e[0]) + " " + str(e[1]) + "\n")
