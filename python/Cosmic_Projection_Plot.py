import numpy as np
import matplotlib.pylab as plt
from mpl_toolkits.mplot3d import Axes3D
import sys

scaling_const = float(sys.argv[1])

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


dt = np.dtype(float)
betweeness = np.fromfile("OUTPUTS/cosmic_betweeness.bin",dtype=dt)
dt = np.dtype("int32")
degree = np.fromfile("OUTPUTS/cosmic_degree.bin",dtype=dt)

#degree = np.array(degree, dtype=np.dtype(float))
degree = np.log10(degree)
degree = degree / np.amax(degree)

print degree

"""
ax = plt.gca()
ax.set_yscale('log')
plt.hist(betweeness, histtype='step',bins=np.linspace(0,np.amax(betweeness),100))
plt.show()
"""

#betweeness = scaling_const * np.sqrt(betweeness)
betweeness = (betweeness/np.amax(betweeness))**2
print betweeness

fig = plt.figure(figsize=(14,10))
ax = fig.add_subplot(111, projection='3d')
plt.xlabel(r'$x$ kpc')
plt.ylabel(r'$y$ kpc')
#ax.set_axis_bgcolor('black')
sizes = scaling_const * degree
ax.scatter(x,y,z,marker='.',  color=plt.cm.jet(degree), s=scaling_const)#s=betweeness)
for i in range(0, len(x1)):
    ax.plot([x1[i], x2[i]], [y1[i], y2[i]], [z1[i], z2[i]], color='black', alpha=0.0)
plt.show()
