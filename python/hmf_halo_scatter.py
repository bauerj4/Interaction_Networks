from mpl_toolkits.mplot3d import Axes3D
import matplotlib.pylab as plt
import numpy as np
import sys

h = 0.679

f = open(sys.argv[1])
x = []
y = []
z = []
m = []

for line in f:
    if (line[0] == '#'):
        pass
    else:
        line = line.split()
        m.append(float(line[2]) * h)
        x.append(float(line[8]) *  h)
        y.append(float(line[9]) *  h)
        z.append(float(line[10]) * h)


fig = plt.figure(figsize=(16,7))

bins = np.linspace(10,13,40)
dx = bins[1] - bins[0]
masses, _, = np.histogram(np.log10(m),bins=bins)

plt.clf()

#print len(bins)
#print len(masses)

#fig = plt.figure(figsize=(16,10))

ax = fig.add_subplot(121)
ax.set_yscale('log')
#ax.set_xscale('log')
plt.xlabel(r'$\log_{10} [M / M_\odot]$',fontsize=16)
plt.ylabel(r'$dN / d\log_{10} [M / M_\odot]$',fontsize=16)
plt.plot(bins[1:] + dx, masses,linewidth=2)

ax = fig.add_subplot(122, projection='3d')
plt.xlabel('$x$ Mpc')
plt.ylabel('$y$ Mpc')
#plt.zlabel('$z$ kpc')

ax.scatter(x,y,z, marker='.',s=1)

plt.show()


