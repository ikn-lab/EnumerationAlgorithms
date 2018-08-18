#!/usr/bin/env python3
# -*- coding: utf-8 -*-
import networkx as nx

G = nx.powerlaw_cluster_graph(25, 7, 0.114);
n, m = len(list(G.nodes)), len(list(G.edges))
print(n, " ", end="")
print(m)
for e in list(G.edges):
    print(e[0], " ", end="")
    print(e[1])
