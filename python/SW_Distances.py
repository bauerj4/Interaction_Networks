import numpy as np
import matplotlib.pylab as plt
import sys

paths = sys.argv[1:]

plt.figure(figsize=(16,7))

for path in paths:
    dt = np.dtype("i4")
    distances = np.fromfile(str(path) + "/sw_distances.bin", dtype=dt)
    
    count = distances[0];
    distances = distances[1:]
    distances_matrix = np.reshape(distances, (count,count))
    avg_distances = np.zeros(count)
    
    #plt.figure(figsize=(16,7))
    for i in range(0, count):
        avg_distances[i] = np.mean(distances_matrix[i])
    
    plt.subplot(121)
    ax = plt.gca()
    #ax.set_yscale('log')
    plt.xlabel(r'$d_{ij}$', fontsize=16)
    plt.ylabel(r'$f(d_{ij})$', fontsize=16)
    rng = np.amax(distances) - np.amin(distances)
    bins = np.linspace(np.amin(distances), np.amax(distances), rng)
    plt.hist(distances, histtype='step',bins=bins,normed=True)
    
    plt.subplot(122)
    ax = plt.gca()
    plt.xlim(0,50)
    plt.xlabel(r'$\ell_{i}$', fontsize=16)
    plt.ylabel(r'$f(\ell_{i})$', fontsize=16)

    rng = np.amax(distances) - np.amin(distances)
    bins = np.linspace(np.amin(avg_distances), np.amax(avg_distances), 10)
    #ax.set_xscale('log')
    plt.hist(avg_distances,histtype='step',bins=bins,normed=True)

plt.show()
