import pulp
import sys
import math

from collections import defaultdict
from dimacs import *

def graph_path(name):
    return "graph/" + name

def vertex_cover(G):
    print("Solving Vertex Cover:")
    model = pulp.LpProblem( "vertex_cover", pulp.LpMinimize)

    vars = []
    for v in range(len(G)):
        x = pulp.LpVariable(str(v), cat = "Binary")
        vars.append(x)
    
    model += sum(vars)

    for e in edgeList(G):
        model += vars[e[0]] + vars[e[1]] >= 1

    # solving
    model.solve()
    print("Status: ", pulp.LpStatus[model.status])
    size = sum(int(var.varValue) for var in model.variables() if var.varValue > 0)
    print("Size: ", size)
    for var in model.variables():
        if (var.varValue > 0):
            print(var.name, end=' ')
    print("\n")

def make_weights(G):
    weights = defaultdict(lambda: 0)
    for e in edgeList(G):
        weights[e[0]] = weights[e[0]] + 1
        weights[e[1]] = weights[e[1]] + 1
    return weights

def weighted_vertex_cover(G):
    print("Solving Weighted Vertex Cover:")
    model = pulp.LpProblem( "weighted_vertex_cover", pulp.LpMinimize)

    weights = make_weights(G)

    vars = []
    for v in range(len(G)):
        x = pulp.LpVariable(str(v), cat = "Binary")
        vars.append(x)

    model += sum(var * weights[int(var.name)] for var in vars)

    for e in edgeList(G):
        model += vars[e[0]] + vars[e[1]] >= 1

    # solving
    model.solve()
    print("Status: ", pulp.LpStatus[model.status])
    total_weight = sum(weights[int(var.name)] for var in model.variables() if var.varValue > 0)
    print("Total weight: ", total_weight)
    for var in model.variables():
        if (var.varValue > 0):
            print(var.name, ":", weights[int(var.varValue)], end=', ')
    print("\n")

def vertex_cover_relaxation(G):
    print("Solving Vertex Cover with relaxation:")
    model = pulp.LpProblem( "vertex_cover_relaxation", pulp.LpMinimize)

    vars = []
    for v in range(len(G)):
        x = pulp.LpVariable(str(v), lowBound=0, upBound=1, cat = "Continuous")
        vars.append(x)
    
    model += sum(vars)

    for e in edgeList(G):
        model += vars[e[0]] + vars[e[1]] >= 1

    # solving
    model.solve()
    print("Status: ", pulp.LpStatus[model.status])
    size = sum(1 for var in model.variables() if var.varValue >= 0.5)
    print("Size: ", size)
    for var in model.variables():
        if (var.varValue > 0):
            print(var.name, end=' ')
    print("\n")

# def graph_coloring(G, k):
#     print("Solving Graph Coloring:")
#     model = pulp.LpProblem("graph_coloring")

#     vars = dict()

#     for v in range(len(G)):
#         for color in range(k):
#             name = str(v) + ", " + str(k)
#             x = pulp.LpVariable(name, lowBound=0, upBound=1, cat = "Continuous")
#             vars[name] = x
        
#     for v in range(len(G))
#         name = str(v) + ", " + str(k)
#         model += sum(vars[]) = 1

def main():
    G = loadGraph(graph_path(sys.argv[1]))
    vertex_cover(G)
    weighted_vertex_cover(G)
    vertex_cover_relaxation(G)

if __name__ == "__main__":
    main()
