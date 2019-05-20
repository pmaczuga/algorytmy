import sys
import collections
from dimacs import *
from itertools import *
import copy
from os import listdir
from os.path import isfile, join

path = "graph"

def filepath(path, name):
    return path + "/" + name

def brute_force(G, k):
    V = len(G)

    for C in combinations( range(V), k ):
        if isVC(edgeList(G), C):
            return C
    return None

def remove_vertex(G, v):
    N = []
    for u in G[v].copy():
        N += [(u,v)]        # dopisz usuwaną krawędź do N
        G[u].remove(v)      # usun krawędź z u do v
        G[v].remove(u)      # usun krawędź z v do u
    return N

def restore_vertex(G, N):
    for (u,v) in N:
        G[u].add(v)
        G[v].add(u)
       
def recursive(G, k, removed = tuple()):
    E = edgeList(G)
    if k == 0 or not E:
        if not E:
            return removed
        else:
            return None

    e = E[0]

    to_restore = remove_vertex(G, e[0])
    sol = recursive(G, k-1, removed + (e[0], ))
    if sol:
        return sol
    restore_vertex(G, to_restore)
    to_restore = remove_vertex(G, e[1])
    sol = recursive(G, k-1, removed + (e[1], ))
    if sol:
        return sol
    restore_vertex(G, to_restore)
    return None

def compress_graph(G, k):
    degrees = collections.defaultdict(lambda: (0, None))
    removed = []
    for edge in edgeList(G):
        degrees[edge[0]] = (degrees[edge[0]][0] + 1, edge[1])
        degrees[edge[1]] = (degrees[edge[1]][0] + 1, edge[0])
    for vertex, (degree, last_neighbour) in degrees.items():
        if degree == 1 and last_neighbour not in removed:
            removed += [last_neighbour]
            remove_vertex(G, last_neighbour)
            k -= 1
        elif degree > k and vertex not in removed:
            removed += [vertex]
            remove_vertex(G, vertex)
            k -= 1
    if len(edgeList(G)) > k**2:
        return ()
    return (G, k, tuple(removed))

def vertex_cover():
    name = sys.argv[1]
    real_G = loadGraph( filepath(path, name) )
    for k in range(1, len(real_G)):
        G = copy.deepcopy(real_G)
        compressed = compress_graph(G, k)
        if compressed:
            G = compressed[0]
            new_k = compressed[1]
            removed = compressed[2]
            sol = recursive(G, new_k)
            if sol != None:
                sol = removed + sol
                print("Precise: " + sol.__str__())
                saveSolution(filepath(path, name) + ".sol", sol)
                break

def approximate(G):
    sol = []
    E = edgeList(G)
    while E:
        e = E[0]
        sol += [e[0]]
        sol += [e[1]]
        remove_vertex(G, e[0])
        remove_vertex(G, e[1])
        E = edgeList(G)
    return sol
    
def approximate_vertex_cover():
    name = sys.argv[1]
    G = loadGraph( filepath(path, name) )
    sol = approximate(G)
    print("Approximate: " + sol.__str__())
    saveSolution(filepath(path, name) + ".sol", sol)

vertex_cover()
# approximate_vertex_cover()
