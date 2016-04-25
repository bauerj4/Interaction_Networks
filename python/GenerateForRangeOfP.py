import sys
import os
import numpy as np
import matplotlib.pylab as plt
# the range of logp
logprng = np.linspace(-3.8,0,14)
average_distances = []
p_vals = []

Nodes = sys.argv[1]
Z = sys.argv[2]

for val in logprng:
    p = 10**val
    lines = []
    f = open("Config.sh")
    for line in f:
        if (line.split("=")[0] != "JUMP_FRACTION"):
            lines.append(line)
        else:
            thisline = "JUMP_FRACTION=" + str(p)
            lines.append(thisline)
            print thisline

    f.close()

    os.system("rm Config.sh")
    f = open("Config.sh",  'w')
    f.writelines(lines)

    f.close()
    os.system("make")
    os.system("./bin/sw_network")
    
    dirname = "./Archives/sw_auto_n"+ str(Nodes)+"_z" +str(Z) +"_p" + str(val)
    os.system("mkdir " + dirname)
    os.system("mv OUTPUTS/* " + dirname)

    distances = np.fromfile(dirname + "/sw_distances.bin", dtype=np.dtype("i4"))
    print "Average distance at " + str(p) + " = " + str(np.mean(distances))
    average_distances.append(np.mean(distances))
    p_vals.append(p)
    #os.system("mkdir " + dirname)
    #os.system("mv OUTPUTS/* " + dirname)
    
plt.figure()
ax = plt.gca()
ax.set_xscale('log')
plt.scatter(p_vals,np.array(average_distances)/average_distances[0])
plt.xlabel(r"$p$", fontsize=18)
plt.ylabel(r"$\ell(p) / \ell(0)$",fontsize=18)
plt.show()


print "Writing output to file..."

p_vals = np.array(p_vals)
average_distances = np.array(average_distances)/average_distances[0]

dt = np.dtype(float)
p_vals.tofile("OUTPUTS/domain.bin")
average_distances.tofile("OUTPUTS/range.bin")
