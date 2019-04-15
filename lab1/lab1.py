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

def vertexes(G):
    N = set()
    E = edgeList(G)
    for e in E:
        N.add(e[0])
        N.add(e[1])
    return tuple(N)

def remove_vertex(G, v):
    G = copy.deepcopy(G)
    for u in G[v].copy():
        G[u].remove(v)    # usun krawędź z u do v
        G[v].remove(u)    # usun krawędź z v do u
    return G

def remove_edge(G, e):
    G = copy.deepcopy(G)
    G[e[0]].remove(e[1])
    G[e[1]].remove(e[0])
    return G
       
def recursive(G, k, removed = tuple()):
    E = edgeList(G)
    if k == 0 or not E:
        if not E:
            return removed
        else:
            return None

    e = E[0]

    sol = recursive(remove_vertex(G, e[0]), k-1, removed + (e[0], ))
    if sol:
        return sol
    sol = recursive(remove_vertex(G, e[1]), k-1, removed + (e[1], ))
    if sol:
        return sol
    return None

def check_everything():
    # onlyfiles = [f for f in listdir(mypath) if isfile(join(mypath, f))]
    name = "m30"
    G = loadGraph( filepath(path, name) )
    for k in range(1, len(G)):
        sol = recursive(G, k)
        if sol:
            print(sol)
            saveSolution(filepath(path, name) + ".sol", sol)
            break

check_everything()
# G = loadGraph( "graph/e5" )
# print(recursive(G, 2))
