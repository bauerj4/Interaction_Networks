
import numpy as np
import matplotlib.pylab as plt
import sys

dt = np.dtype('i4')
vertex = np.fromfile("OUTPUTS/sw_vertices.bin",dtype=dt)

nodes = vertex[0]
vertex = vertex[1:]


angles = np.linspace(0., 2. * np.pi, nodes)
x_vals = np.cos(angles)
y_vals = np.sin(angles)


"""

Scale here if desired

"""




"""

Make the plots

"""

plt.figure(figsize=(8,8))

plt.scatter(x_vals,y_vals,color='red')
i=0
while (i < len(vertex)):
    plt.plot([x_vals[vertex[i]], x_vals[vertex[i+1]]], \
             [y_vals[vertex[i]], y_vals[vertex[i+1]]], color='black')
    i = i + 2

plt.show()
