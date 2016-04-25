
import numpy as np
import matplotlib.pylab as plt
import sys

scaling_coeff = float(sys.argv[1])
scaling_power = float(sys.argv[2])

dt = np.dtype('i4')
vertex = np.fromfile("OUTPUTS/sw_vertices.bin",dtype=dt)

nodes = vertex[0]
vertex = vertex[1:]


angles = np.linspace(0., 2. * np.pi, nodes + 1)
x_vals = np.cos(angles)
y_vals = np.sin(angles)


"""

Scale here if desired

"""

dt = np.dtype(float)
betweeness = np.fromfile("OUTPUTS/sw_betweeness.bin",dtype=dt)
#plt.xlabel('Betweeness')
#plt.ylabel('Counts')
#plt.hist(betweeness,histtype='step')

#print betweeness
#betweeness = (betweeness - np.amin(betweeness)) / (np.amax(betweeness) - np.amin(betweeness))
#betweeness = scaling_coeff * (betweeness - np.amin(betweeness))**scaling_power
betweeness = betweeness / np.amax(betweeness)
print betweeness

"""

Make the plots

"""

plt.figure()
plt.xlabel('Betweeness')
plt.ylabel('Counts')
plt.hist(1./scaling_coeff * betweeness**(1/scaling_power),histtype='step')
plt.show()


plt.figure(figsize=(8,8))

plt.scatter(x_vals,y_vals,color=plt.cm.jet(betweeness),s=scaling_coeff)
i=0
while (i < len(vertex)):
    plt.plot([x_vals[vertex[i]], x_vals[vertex[i+1]]], \
             [y_vals[vertex[i]], y_vals[vertex[i+1]]], color='black')
    i = i + 2

ax = plt.gca()
ax.set_yticks([])
ax.set_xticks([])
plt.show()
