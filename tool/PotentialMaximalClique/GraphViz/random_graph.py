#!/usr/bin/env python3
# -*- coding: utf-8 -*-
import networkx as nx
import matplotlib.pyplot as plt
import random
import queue

def CheckFullConponenet(G, S):
    H = G.copy()
    for i in S: H.remove_node(i)
    connected_component = []
    visited = [False for i in range(G.number_of_nodes())]
    que = queue.Queue()    
    for i in range(G.number_of_nodes()):
        if (i in S) or visited[i] == True: continue
        connected_component.append(set())
        connected_component[-1].add(i)
        visited[i] = True
        que.put(i)
        while not(que.empty()):
            v = que.get()
            for j in H.neighbors(v):
                if visited[j] == True: continue
                visited[j] = True
                connected_component[-1].add(j)
                que.put(j)
                
    for C in connected_component:
        N = set()
        for v in C:
            for k in G.neighbors(v):
                N.add(k)
        if S <= N:return True
    return False

def CheckConnect(G, S, s, t):
    # print("start CheckConnect")
    H = G.copy()
    starts, terminals = [], []
    for i in G.neighbors(s):
        if not(i in S): starts.append(i)
    for i in G.neighbors(t):
        if not(i in S): terminals.append(i)
    if len(starts) == 0 or len(terminals) == 0: return False
    
    visited = [False for i in range(G.number_of_nodes())]
    que = queue.Queue()
    for i in starts:
        visited[i] = True
        que.put(i)
        
    while not(que.empty()):
        v = que.get()
        if v in terminals:
            return True
        for i in H.neighbors(v):
            if visited[i] == True:
                continue
            visited[i] = True
            que.put(i)
    return False

def CheckPMC(G, S):
    # print(",".join(map(str,S)))
    if len(S) <= 1:return False
    if CheckFullConponenet(G, S): return False
    for i in S:
        for j in S:
            if i <= j: continue
            if not(i in G.neighbors(j)) and not CheckConnect(G, S, i, j): return False
    return True

def dfs(G, n, S):
    if n == 0:
        if CheckPMC(G, S):
            ncolor = []
            for i in range(G.number_of_nodes()):
                if i in S: ncolor.append('g')
                else: ncolor.append('w')
            plt.figure(figsize=(16,9))
            pos = nx.spring_layout(G,k=0.3)
            nx.draw_networkx(G,pos,node_color=ncolor)
            nx.draw_networkx_labels(G, pos, fontsize=14, font_family="DejaVu Sans", font_weight="bold")
            plt.axis("off")
            plt.savefig("random.png")
            plt.show()
            plt.close() #一旦閉じる！！！

        return
    S.add(n - 1)
    dfs(G, n - 1, S)
    S.remove(n - 1)
    dfs(G, n - 1, S)

G = nx.fast_gnp_random_graph(14, 0.3)
S = set()
dfs(G, G.number_of_nodes(), S)


