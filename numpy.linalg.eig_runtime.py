from numpy import linalg

path = input("Path to test file: ")
f = open(path, "r")
line = f.readline().split()
tests = int(line[0])
n = int(line[1])

for i in range(tests):
    mat = []
    for j in range(n):
        vec = [int(x) for x in f.readline().split()]
        mat.append(vec)
    w, v = linalg.eig(mat)
