import numpy as np
import matplotlib.pylab as plt
from mpl_toolkits.mplot3d import Axes3D
import sys

files = sys.argv[1:]
dt1 = np.dtype('int32')
dt2 = np.dtype(float)
f_vals = []
x_vals = []

for directory in files:
    degree = np.fromfile(directory + "cosmic_degree.bin",dtype=dt1)
    print len(degree)
    #betweeness = betweeness / np.amax(betweeness)
    
    masses = np.fromfile(directory + "cosmic_masses.bin",dtype=dt2)
    print len(masses)
    
    #ax = plt.gca()
    #ax.set_xscale('log')
    #ax.set_yscale('log')
    #plt.scatter(masses,degree, marker='.', color='black')
    #plt.show()
    

    #bins=np.linspace(1,600,600)
    #hist,_,_ = plt.hist(degree,histtype='step', bins=bins)

    f_vals.append(degree)
    x_vals.append(masses)
    #plt.clf()
    
    #ax = plt.gca()
    #ax.set_xscale('log')
    #ax.set_yscale('log')
    
    #plt.plot(bins[1:], hist, color='black')
    #plt.plot(polyspace, poly, color='red')

plt.clf()
ax = plt.gca()
ax.set_yscale('log')
#ax.set_xscale('log')
plt.xlabel(r'$k$', fontsize=16)
plt.ylabel(r'Mass $(M_\odot)$', fontsize=16)
markers = ['.', '*', 's']
colors = ['blue', 'red', 'green']
i = 0
for x,y in zip(x_vals,f_vals):
    plt.scatter(y,x, marker=markers[i%len(markers)],color=colors[i % len(colors)], alpha=0.2)
    i = i + 1
plt.ylim(5.*10**10, 5*10**14)
plt.show()
