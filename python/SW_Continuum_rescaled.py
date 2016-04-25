import numpy as np
import matplotlib.pylab as plt
import sys

dt = np.dtype(float)
files = sys.argv[1:]

i=0

markers = ['o', '.', 's', '*']
colors = ['blue', 'red', 'green', 'purple']

for element in files:
    domain = np.fromfile(element + "domain.bin", dtype=dt)
    rng = np.fromfile(element + "range.bin", dtype=dt)
    
    plt.scatter(domain,rng,marker=markers[i % len(markers)], color=colors[i % len(colors)])

    i = i + 1

plt.xlabel(r"Number of Shortcuts", fontsize=18)
plt.ylabel(r"$\Delta \theta \, (\pi Z \ell / N)$",fontsize=18)

ax = plt.gca()
ax.set_xscale('log')
plt.show()
