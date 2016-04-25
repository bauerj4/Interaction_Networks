import numpy as np
import matplotlib.pylab as plt
import sys

NWRITERS = int(sys.argv[1])
NODES = int(sys.argv[2])
dt = np.dtype('i4')#np.dtype('>i4')


matrixlist = []
rowrngs = []
colrngs = []
for n in range(0, NWRITERS):
    thisblock = np.fromfile("OUTPUTS/adjacency." + str(n), dtype=dt)
    minrow = thisblock[0]
    maxrow = thisblock[1]
    mincol = thisblock[2]
    maxcol = thisblock[3]
    rowrngs.append([minrow, maxrow])
    colrngs.append([mincol, maxcol])
    thisblock = thisblock[4:]
    print thisblock
    print len(thisblock)
    print (maxrow - minrow + 1)*(maxcol - mincol + 1)
    thisblock = np.reshape(thisblock, (maxrow - minrow + 1, maxcol - mincol + 1))
    matrixlist.append(thisblock)


"""

Now, patch things back together.

"""

matrix = np.zeros(NODES*NODES)
matrix = np.reshape(matrix,(NODES,NODES))

for i in range(0, NODES):
    for j in range(0, NODES):
        # Find what block this belongs to.
        
        isInColRng = np.zeros(NWRITERS)
        isInRowRng = np.zeros(NWRITERS)

        k = 0
        for rng in rowrngs:
            if (i >= rng[0] and i <= rng[1]):
                isInRowRng[k] = True
            else:
                isInRowRng[k] = False
            k = k + 1

        k = 0
        for rng in colrngs:
            if (j >= rng[0] and j <= rng[1]):
                isInColRng[k] = True
            else:
                isInColRng[k] = False
            k = k + 1
        for k in range(0, len(isInColRng)):
            if (isInColRng[k] and isInRowRng[k]):
                matrix[i][j] = matrixlist[k][i - rowrngs[k][0]][j - colrngs[k][0]]

plt.imshow(np.log(matrix), interpolation='none')
plt.show()

# Now arrange nodes on a circle


plt.figure(figsize=(8,8))

node_pos = np.linspace(0., 2. * np.pi, NODES)
x = np.cos(node_pos)
y = np.sin(node_pos)

j = 0
for row in matrix:
    for i in range(0, len(row)):
        if (i != j and matrix[i][j] != 0 ):
            plt.plot([x[i], x[j]], [y[i], y[j]], color='k')
    j = j + 1
plt.scatter(x,y, color='red')


plt.show()


x1 = np.dot(matrix, matrix[0])
x2 = np.dot(matrix, x1)
x3 = np.dot(matrix, x2)
x4 = np.dot(matrix, x3)

print x4
