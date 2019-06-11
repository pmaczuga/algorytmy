import pulp

from dimacs import *

# stwórz model problemu o nazwie test, minimalizacja funkcji celu
model = pulp.LpProblem( "test", pulp.LpMinimize)   # LpMaximize dla maksymalizowania funkcji celu

# stwórz trzy zmienne, x, y, z
x = pulp.LpVariable( "x" , lowBound = 0, upBound = 5, cat = "Continuous" ) # zmienna ciągła z przedzialu [0,5]
y = pulp.LpVariable( "y" , lowBound = 0, upBound = 3, cat = "Integer" )    # zmienna całkowita ze zbioru {0,1,2,3}
z = pulp.LpVariable( "z" , cat = "Binary" )                                # zmienna binarna, wartosci ze zbioru {0,1}

# dodaj funkcję celu do modelu
model += 5-x+2*y-z    

# dodaj ograniczenia (konieczne do spełnienia nierówności liniowe)
model += x >= y
model += y >= z

# print(model)

model.solve()                    # rozwiąż używając CBC
print(pulp.LpStatus[model.status])     # wypisz status rozwiązania

# wypisz zmienne
for var in model.variables():
    print(var.name, "=", var.varValue)

# wypisz wartość funkcji celu
print(pulp.value(model.objective))

# wypisz status rozwiazania
print(pulp.LpStatus[model.status])