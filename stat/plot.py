import numpy as np
import matplotlib.pyplot as plt

data = np.loadtxt("./memory_access_data.txt")
save_dir = "./imgs/"
x = data[:,0]
y = data[:,1]
y = np.log2(y)
z = data[:,2]

fig = plt.figure()
ax = fig.add_subplot(111, projection = "3d")
ax.set_ylim(max(y), min(y))
ax.set_xlabel("Stride (8 Bytes)")
ax.set_ylabel("log2(ArraySize) (Bytes)")
ax.set_zlabel("ThoughtPut (MB/s)")
ax.view_init(elev = 20, azim = -50)
surf = ax.plot_trisurf(x, y, z, cmap = "magma")
# plt.show()
plt.savefig(save_dir+"memory_mountain.png", bbox_inches="tight")  

fig, ax = plt.subplots()
ax.set_xlabel("log2(ArraySize) (Bytes)")
ax.set_ylabel("Throughput (MB/s)")
groups = np.unique(data[:, 0])
for group in groups:
    group_data = data[data[:, 0] == group]
    x = group_data[:, 1]
    y = group_data[:, 2]
    x = np.log2(x)
    plt.plot(x, y, label = f'{int(group) * 8} Bytes Stride')
plt.legend(loc = (1.05, -0.15))
# plt.show()        
plt.savefig(save_dir+"part1.png", bbox_inches="tight")                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                        