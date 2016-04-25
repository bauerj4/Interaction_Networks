import numpy as np
import matplotlib.pylab as plt
import sys




dt = np.dtype('d')

vertex = np.fromfile("OUTPUTS/cosmic_vertices.bin",dtype=dt)
print vertex
count = len(vertex)

x = []
y = []
z = []

i=0
while (i < count):
    x.append(vertex[i])
    y.append(vertex[i+1])
    z.append(vertex[i+2])
    i = i + 3


edges = np.fromfile("OUTPUTS/cosmic_edges.bin",dtype=dt)
count = len(edges)/3

print edges

x1 = []
y1 = []
z1 = []
x2 = []
y2 = []
z2 = []


i=0
while (i < count):
    x1.append(edges[i])
    y1.append(edges[i+1])
    z1.append(edges[i+2])
    x2.append(edges[i+3])
    y2.append(edges[i+4])
    z2.append(edges[i+5])

    i = i + 6

plt.scatter(x,y,marker='.', color='black')
for i in range(0, len(x1)):
    plt.plot([x1[i], x2[i]], [y1[i], y2[i]], color='red', alpha=0.1)
plt.show()
