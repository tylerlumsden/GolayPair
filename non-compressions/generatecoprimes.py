import math

coprimeslist = []
coprimes = []

for i in range(100):
    for j in range(2, i):
        if math.gcd(i, j) == 1:
            coprimes.append(j)
    coprimeslist.append(coprimes) 
    coprimes = []

f = open("coprimes.h", "w")

f.write("int coprimelength[100] = {")

for i in range(len(coprimeslist)):
    if i == len(coprimeslist) - 1:
        f.write(str(len(coprimeslist[i])))
        break

    f.write(str(len(coprimeslist[i])) + ",")

f.write("};\n\n\n")

f.write("int coprimelist[100][100] = {\n")

for i in range(len(coprimeslist)):

    f.write("{")



    for j in range(len(coprimeslist[i])):
        if j == len(coprimeslist[i]) - 1:
            f.write(str(coprimeslist[i][j]))
            break

        f.write(str(coprimeslist[i][j]) + ",")

    if i == len(coprimeslist) - 1:
        f.write("}\n\n};")
        break

    f.write("},\n")
    
    
    

