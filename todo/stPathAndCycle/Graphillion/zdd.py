#!/usr/bin/env python
# -*- coding: utf-8 -*-
from graphillion import GraphSet
import graphillion.tutorial as tl
import sys

args = sys.argv
f = open(args[1], 'r')
cnt = 0
universe = []
for row in f:
    if cnt == 0:
        n = int(row)
    else:
        u, v = map(int, row.split(" "))
        universe.append((u, v))
    cnt += 1

GraphSet.set_universe(universe)
paths = GraphSet.paths(1, n)
cycles = GraphSet.cycles()
print "the num of paths: " + str(len(paths))
# print paths
print "the num of cycles: " + str(len(cycles))
# print cycles
