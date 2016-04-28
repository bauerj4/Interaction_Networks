import numpy as np
import matplotlib.pylab as plt
import sys


"""

Cosmic distances distribution

Usage:

python <program_name> <file_list>

"""


dirs = sys.argv[1:]

avg_x_vals = []
x_vals = []

avg_f_vals = []
f_vals =[]

for d in dirs:
    dt = np.dtype("i4")
    distances = np.fromfile(d + "cosmic_distances.bin", dtype=dt)

    count = distances[0];
    distances = distances[1:]
    distances_matrix = np.reshape(distances, (count,count))
    avg_distances = np.zeros(count)
    

    bins = np.linspace(-1,15,17)
    dx = bins[1] - bins[0]

    x_vals.append(bins)
    #hist, _, _ = plt.hist(distances, histtype='step', bins=bins,color='black',normed=True)
    f_vals.append(distances)

    #plt.clf()

    for i in range(0, count):
        idxs = np.any(distances_matrix[i] == -1)
        avg_distances_matrix = np.delete(distances_matrix[i],idxs)
        avg_distances[i] = np.mean(avg_distances_matrix)

    bins = np.linspace(1,7,75)
    dx = bins[1] - bins[0]
    avg_x_vals.append(bins[1:] - dx)
    avg_distance_hist, _ = np.histogram(avg_distances,bins=bins)
    avg_f_vals.append(avg_distance_hist)
    plt.clf()
        
ax = plt.gca()

for x,y in zip(avg_x_vals, avg_f_vals):
    plt.xlabel(r"$\ell_i$",fontsize=18)
    plt.ylabel(r"$F(\ell_i)$",fontsize=18)
    plt.plot(x,y)

plt.show()

maximum = -1
for x,y in zip(x_vals, f_vals):
    hist, _, _ = plt.hist(y, histtype='step', bins=x,normed=False)
    #plt.plot([0,0], [0, 1.25 * np.amax(hist)], color='black')
    #plt.ylim(0, 1.25 * np.amax(hist))
    if (np.amax(hist) > maximum):
        maximum = np.amax(hist)
    plt.xlabel(r"$d_{ij}$",fontsize=18)
    plt.ylabel(r"$F(d_{ij})$",fontsize=18)
plt.ylim(0, 1.25 * maximum)
plt.plot([0,0], [0, 1.25 * maximum], color='black')
plt.show()
    
