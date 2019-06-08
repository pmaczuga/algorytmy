import pycosat
import random
import math
import numpy as np
from dimacs import *
import sys

def zad1():
    k = 3
    n = 10
    T = 100
    sign = [-1, 1]
    a_min = 1
    a_max = 10
    a_step = 0.1

    V = range(1, n+1)


    a = a_min
    while a < a_max:
        S = 0
        for t in range(T):
            cnf = []
            for i in range(math.floor(a * n)):
                clause = []
                for j in range(k):
                    x = random.choice(V)*random.choice(sign)
                    clause.append(x)
                cnf.append(clause)
            if not pycosat.solve(cnf) == u'UNSAT':
                S += 1
        print("{:.1f}; {}".format(a, S/T))
        a += 0.1

def index( i, j ):
    return (i+j)*(i+j+1)//2+i + 1

def check_coloring(G, k, sol):
    colors = dict()
    for v in range(len(G)):
        for color in range(k):
            if index(v, color) in sol:
                if v in colors:
                    return "Wrong coloring"
                colors[v] = color

    for e in edgeList(G):
        if colors[e[0]] == colors[e[1]]:
            return "Wrong coloring"

    return colors

def zad2a():
    G = loadGraph(sys.argv[1])
    k = int(sys.argv[2])
    cnf = []
    for v in range(len(G)):
        all_colors = []
        for color1 in range(k):
            for color2 in range(color1 + 1, k):
                if color1 != color2:
                    cnf.append([-index(v, color1), -index(v, color2)])
            all_colors.append(index(v, color1))
        cnf.append(all_colors)
    for e in edgeList(G):
        for color in range(k):
            cnf.append([-index(e[0], color), -index(e[1], color)])

    sol = pycosat.solve(cnf)
    if sol != u'UNSAT':
        print(check_coloring(G, k, sol))
    else:
        print(sol)

def main():
    # zad1()
    zad2a()

if __name__ == "__main__":
    main()
