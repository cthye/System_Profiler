# CSE 221 System Profiler

Full Report on [google drive](https://drive.google.com/file/d/1gzSMchWW5IhgmUmyG1VDGNeFmQIP_grI/view?usp=sharing) [OverLeaf](https://www.overleaf.com/read/trttfkjfsvgq)

# Build
```sh
mkdir bin
make [cpu/mem/net/fs]
```

# Introduction
Operating System performance is a crucial aspect in today's computing environments. It determines the overall effectiveness and efficiency of a computer system in handling various tasks. The performance of an OS is influenced by various factors including the underlying hardware, system design, and the workload. Understanding how hardware affects the performance of the OS is important in optimizing and tuning the system to meet the specific needs and demands.

In this report, we will focus on exploring the relationship between hardware and OS performance. We will analyze the impact of hardware components such as the CPU, RAM, disk and network on the performance of the OS and how they contribute to the overall system efficiency.

Our group members include Xinyuan Liang, Siran Ma and Wentao Huang. We conducted experiments on an x86_64 and Linux based machine using C and GNU C compiler[version] with -O0[maybe -O1 for some experiments] optimization level. For machine details see the Machine Description section below. The estimated workload is 30 to 40 hours for each team member.

# Machine Description
1. Processor
```sh
# for cpu info
cat /proc/cpuinfo

# for cache L1, L2, L3
lscpu | grep "cache"
```
- Process Model: Intel(R) Core(TM) i5-7200U @ 2.50GHz x 4
- Cycle Time: 800.000 MHz (max: 3100.0000 MHz, min: 400.0000)
- Cache Sizes: 3072KB (L1d: 32K, L1i: 32K, L2:256K, L3:3072K)
2. DRAM (Memory)
```sh
sudo lshw -C memory
```
- Model: [HMA81GS6AFR8N-UH SK Hynix 8GB 2400 SODIMM](https://memory.net/product/hma81gs6afr8n-uh-sk-hynix-1x-8gb-ddr4-2400-sodimm-pc4-19200t-s-single-rank-x8-module/)
- DRAM type: SODIMM (DDR4)
- Clock: 2400MHz (0.4ns)
- Capacity: 8GiB
3. I/O
```sh
lspci -v
```
- SATA Controller: link up 6.0Gbps
4. Disk
```sh
iostat -dx
sudo hdparm -tT /dev/sda # depends on the device
```
- SSD: 
  - Model: [TOSHIBA THNSNK128GVN8](https://smarthdd.com/database/TOSHIBA-THNSNK128GVN8/K8AS4102/) (K8AS4102)
  - Capacity: 128G
  - Transfer rate(maximum interface speed): 600 MB/s
  - IOPs: Not mentioned in specs???
  - Latencies: Not mentioned in specs???
- HDD: 
    - Model: [ST1000LM035-1RK172](https://www.disctech.com/Seagate-ST1000LM035-1TB-SATA-Hard-Drive) (SDM1) 
    - Capacity: 1TB 
    - RPM: 5400
    - Transfer rate: 140 MB/s
    - Latencies: Not mentioned in specs???
5. Network
```sh
sudo ethtool enx144fd7c3f0d0 # depends on the interface name
lwconfig wlp2s0 # depends on the interface name
```
- Ethernet
  - Bandwidth: 1000 Mb/s
- Wireless
  - Ubuntu: Bandwidth: 400 Mb/s
  - MacOS (for gradhousing's WiFi) transmit rate: 400 Mbps
6. Operating System
- Ubuntu 16.04.4 LTS
7. Notebook Description
- ASUSTeK X510UQ

### Useful Links
1. [How to set CPU frequency](https://manpages.ubuntu.com/manpages/impish/man1/cpupower-frequency-set.1.html)
```sh
sudo cpupower frequency-info
sudo cpupower frequency-set -d 3.10GHz
```
2. How to run in single core
- [taskset](https://askubuntu.com/questions/483824/how-to-run-a-program-with-only-one-cpu-core)
```sh
taskset -c 0 program
```
- [sched_setaffinity](https://man7.org/linux/man-pages/man2/sched_setaffinity.2.html)
3. get page size
```sh
getconf PAGESIZE #4096B
```
4. generate certain size file
```sh
truncate -s 1G 1G
ls -lh
```
5. get #page fault
```sh
/usr/bin/time -v execfile
```
6. Create NFS (server) on MacOS and connect from Ubuntu (client) with SMB protocol
- step1: open file sharing on MacOS (System Preference, search "file sharing")
- step2: create shared directory (default: Public) in the panel with "+"
- step3: install cifs-utils on Ubuntu 
```sh
sudo apt-get install cifs-utils
```
- step4: 
```sh
sudo mount -t cifs //$ip/$remote_dir $local_dir -o username=$account,password=$password,nounix
```
- step5:
```sh
sudo umount -f -l $local_dir
```
7. Cancel file buffer cache
- flush buffer cache with command (not sticky):
  ```sh
  sudo sh -c "sync; echo 3 > /proc/sys/vm/drop_caches"
  ```
  https://unix.stackexchange.com/questions/17936/setting-proc-sys-vm-drop-caches-to-clear-cache
- see current buff cache size
  ```sh
  free -h
  ```
