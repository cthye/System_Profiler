import numpy as np
import matplotlib.pyplot as plt

save_dir = "stat/imgs/"

fig, ax = plt.subplots()
ax.set_xlabel("file size (MB)")
ax.set_ylabel("read speed (MB/s)")

local_seq = np.loadtxt("stat/read_file_dat_local_seq.txt")
block_num = local_seq[:,0]
file_size = local_seq[:,1] 
file_size_MB = local_seq[:,1] / (2**20)
cycles = local_seq[:, 2]
speed = file_size / (cycles / 2700)

plt.plot(file_size_MB, speed, label = "local sequential read")
   
local_radom = np.loadtxt("stat/read_file_dat_local_radom.txt")
block_num = local_radom[:,0]
file_size = local_radom[:,1] 
file_size_MB = local_radom[:,1] / (2**20)
cycles = local_radom[:, 2]
speed = file_size / (cycles / 2700)

plt.plot(file_size_MB, speed, label = "local random read")
plt.legend()
# plt.show()
plt.savefig(save_dir+"read_file_local.png", bbox_inches="tight") 


fig2, ax2 = plt.subplots()
ax2.set_xlabel("file size (MB)")
ax2.set_ylabel("read speed (KB/s)")

remote_seq = np.loadtxt("stat/read_file_dat_remote_seq.txt")
block_num = remote_seq[:,0]
file_size = remote_seq[:,1] 
file_size_MB = remote_seq[:,1] / (2**20)
cycles = remote_seq[:, 2]
speed = file_size / (cycles / 2700000)

plt.plot(file_size_MB, speed, label = "remote sequential read")
   
remote_radom = np.loadtxt("stat/read_file_dat_remote_radom.txt")
block_num = remote_radom[:,0]
file_size = remote_radom[:,1] 
file_size_MB = remote_radom[:,1] / (2**20)
cycles = remote_radom[:, 2]
speed = file_size / (cycles / 2700000)

plt.plot(file_size_MB, speed, label = "remote random read")
plt.legend()

plt.savefig(save_dir+"read_file_remote.png", bbox_inches="tight")       


# y axis : cycles
fig3, ax3 = plt.subplots()
ax3.set_xlabel("file size (MB)")
ax3.set_ylabel("read time (1000 cycles)")

local_seq = np.loadtxt("stat/read_file_dat_local_seq.txt")
block_num = local_seq[:,0]
file_size = local_seq[:,1] 
file_size_MB = local_seq[:,1] / (2**20)
cycles = local_seq[:, 2]
speed = file_size / (cycles / 2700)

plt.plot(file_size_MB, cycles / 1000 / block_num, label = "local sequential read")
cycles_per_block = cycles / block_num
print("local sequential")
print(np.average(cycles_per_block[:]))
print(np.average(cycles_per_block[10:]))
   
local_radom = np.loadtxt("stat/read_file_dat_local_radom.txt")
block_num = local_radom[:,0]
file_size = local_radom[:,1] 
file_size_MB = local_radom[:,1] / (2**20)
cycles = local_radom[:, 2]
speed = file_size / (cycles / 2700)

plt.plot(file_size_MB, cycles / 1000 / block_num, label = "local random read")
plt.legend()

cycles_per_block = cycles / block_num
print("local random")
print(np.average(cycles_per_block[:]))
print(np.average(cycles_per_block[10:]))
# plt.show()
plt.savefig(save_dir+"read_file_local_cycles.png", bbox_inches="tight") 

## for remote
fig3, ax3 = plt.subplots()
ax3.set_xlabel("file size (MB)")
ax3.set_ylabel("read time (1000 cycles)")

local_seq = np.loadtxt("stat/read_file_dat_remote_seq.txt")
block_num = local_seq[:,0]
file_size = local_seq[:,1] 
file_size_MB = local_seq[:,1] / (2**20)
cycles = local_seq[:, 2]
speed = file_size / (cycles / 2700)

plt.plot(file_size_MB, cycles / 1000 / block_num, label = "remote sequential read")
cycles_per_block = cycles / block_num
print("remote sequential")
print(np.average(cycles_per_block[:]))
print(np.average(cycles_per_block[6:]))
   
local_radom = np.loadtxt("stat/read_file_dat_remote_radom.txt")
block_num = local_radom[:,0]
file_size = local_radom[:,1] 
file_size_MB = local_radom[:,1] / (2**20)
cycles = local_radom[:, 2]
speed = file_size / (cycles / 2700)

plt.plot(file_size_MB, cycles / 1000 / block_num, label = "remote random read")
plt.legend()

cycles_per_block = cycles / block_num
print("remote random")
print(np.average(cycles_per_block[:]))
print(np.average(cycles_per_block[6:]))
# plt.show()
plt.savefig(save_dir+"read_file_remote_cycles.png", bbox_inches="tight") 



