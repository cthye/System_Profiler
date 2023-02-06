# CSE 221 Group 9

Full Report on [OverLeaf](https://www.overleaf.com/read/trttfkjfsvgq)

# Build
```sh
mkdir bin
make [cpu/ram/disk/network]
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
- Bus bandwidth: 64bits
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
  - Bandwidth: 400 Mb/s
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
