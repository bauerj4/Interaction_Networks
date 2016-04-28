import numpy as np
import matplotlib.pylab as plt
from mpl_toolkits.mplot3d import Axes3D
import sys

"""

Degree distribution

Usage:
python <program_name> <file_list>

"""


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
    

    bins=np.linspace(1,600,600)
    hist,_,_ = plt.hist(degree,histtype='step', bins=bins)

    f_vals.append(hist)
    x_vals.append(bins[1:])
    #plt.clf()
    
    ax = plt.gca()
    ax.set_xscale('log')
    ax.set_yscale('log')
    
    #plt.plot(bins[1:], hist, color='black')
    #plt.plot(polyspace, poly, color='red')

plt.clf()
ax = plt.gca()
ax.set_yscale('log')
ax.set_xscale('log')
plt.xlabel(r'$k$', fontsize=16)
plt.ylabel(r'$d N / d \log_{10} k$', fontsize=16)
for x,y in zip(x_vals,f_vals):
    plt.plot(x,y,linewidth=2)
plt.show()
