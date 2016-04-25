import numpy as np
import matplotlib.pylab as plt
import sys

dt = np.dtype("i4")
distances = np.fromfile("OUTPUTS/cosmic_distances.bin", dtype=dt)

count = distances[0];
distances = distances[1:]
distances_matrix = np.reshape(distances, (count,count))
avg_distances = np.zeros(count)

for i in range(0, count):
    idxs = np.any(distances_matrix[i] == -1)
    avg_distances_matrix = np.delete(distances_matrix[i],idxs)
    avg_distances[i] = np.mean(avg_distances_matrix)




bins = np.linspace(1,7,75)
dx = bins[1] - bins[0]
avg_distance_hist, _ = np.histogram(avg_distances,bins=bins)
plt.clf()

ax = plt.gca()

plt.xlabel(r"$\bar{d_i}$ (mean degree of separation)",fontsize=18)
plt.ylabel(r"$f(\bar{d_i})$",fontsize=18)
plt.plot(bins[1:] + dx, avg_distance_hist/np.linalg.norm(avg_distance_hist), color='black')

plt.show()

bins = np.linspace(-1,15,17)
dx = bins[1] - bins[0]
hist, _, _ = plt.hist(distances, histtype='step', bins=bins,color='black',normed=True)
plt.plot([0,0], [0, 1.25 * np.amax(hist)], color='red')
plt.ylim(0, 1.25 * np.amax(hist))
plt.xlabel(r"$d_{ij}$",fontsize=18)
plt.ylabel(r"$f(d_{ij})$",fontsize=18)
plt.show()
