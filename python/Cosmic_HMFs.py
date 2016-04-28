from mpl_toolkits.mplot3d import Axes3D
import matplotlib.pylab as plt
import numpy as np
import sys


"""

Halo mass functions from Rockstar output

Usage:

python <program_name> <rockstar_outputs>

"""

files = sys.argv[1:]
f_vals = []
x_vals = []

for element in files:
    h = 0.679
    
    f = open(element)
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
            

    bins=np.linspace(10,14,50)
    dm = bins[1] - bins[0]
    hist, _, _ = plt.hist(np.log10(m),bins=bins)
    x_vals.append(bins[1:] - dm)
    f_vals.append(hist)
    plt.clf()

for x,y in zip(x_vals, f_vals):
    plt.plot(x,y,linewidth=2)

plt.xlabel(r'$\log_{10} [M / M_\odot]$',fontsize=16)
plt.ylabel(r'$dN / d\log_{10} [M / M_\odot]$',fontsize=16)

ax = plt.gca()
ax.set_yscale('log')
plt.show()
