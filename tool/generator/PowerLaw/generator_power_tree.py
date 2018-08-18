#!/usr/bin/env python3
# -*- coding: utf-8 -*-
import networkx as nx

# T = nx.random_powerlaw_tree(50, 2, 14, 10)
T = nx.random_powerlaw_tree(30, tries=1000)
n, m = len(list(T.nodes)), len(list(T.edges))
print(n, m)
for e in list(T.edges):
    print(e[0], " ", end="")
    print(e[1])
