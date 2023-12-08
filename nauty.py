from pynauty import *
import math

#vertex count needs to account for the number of coprimes. Only running on one coprime right now

seq = [-1, -1, 1, 1, -1]
seq2 = [1, -1, -1, 1, -1]



size = len(seq)
n = len(seq) * len(seq)

coprimes = [2]

#for num in range(0, size):
    #if math.gcd(num, n) == 1:
        #coprimes.append(num)

print(coprimes)

print("Generating graphs")

g = Graph(n)
g2 = Graph(n)

connect = [set() for _ in range(n)]

for i in range(0, size):
    for j in coprimes:
        vert = ((i * j) % size)
        if i != vert:
            connect[i].add(vert)
        for k in range(1, size):
            vertex = i + k * size
            vertex = ((vertex + k) % size) + size * k
            newvert = ((vert + k) % size) + size * k

            if vertex != newvert:
                connect[vertex].add(newvert)

for item in connect[0]:
    print(item)

                
for i in range(0, n):
    g.connect_vertex(i, list(connect[i]))

g2 = g.copy()



negones = []

for i in range(0, n):
    if seq[i % size] == -1:
        negones.append(i)
    
    

g.set_vertex_coloring([set(negones)])

negones = []

for i in range(0, n):
    if seq2[i % size] == -1:
        negones.append(i)

g2.set_vertex_coloring([set(negones)])


#print(g)
#print(g2)
#print(canon_label(g))
#print(canon_label(g2))
print(autgrp(g))

print("testing isomorphism")
 
print(isomorphic(g, g2))