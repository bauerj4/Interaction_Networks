import numpy as np
import matplotlib.pylab as plt
from mpl_toolkits.mplot3d import Axes3D
import sys


"""

Calculates mass vs betweeness.  Betweeness
for cosmic web is broken now.  

Usage:
python <program_name>

"""

#dt = np.dtype('d')
dt = np.dtype(float)

betweeness = np.fromfile("OUTPUTS/cosmic_betweeness.bin",dtype=dt)
betweeness = betweeness / np.amax(betweeness)

masses = np.fromfile("OUTPUTS/cosmic_masses.bin",dtype=dt)

ax = plt.gca()
ax.set_xscale('log')
plt.scatter(masses,betweeness, marker='.', color='black')
plt.show()

