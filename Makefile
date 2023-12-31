CC ?= gcc 
CFLAGS = -g -Wall -O0 -std=c99 
LDLIBS = -lm -lpthread
EXECUTABLEDIR = ./bin
UTILSDIR = ./src/utils
SOURCEDIR_CPU = ./src/cpu
SOURCEDIR_MEM = ./src/memory
SOURCEDIR_NET = ./src/network
SOURCEDIR_FS = ./src/filesystem
OBJS_CPU = cycle_counter read_time_overhead context_switch_process context_switch_thread measure_syscall measure_task measure_procedure 
OBJS_MEM = measure_access page_fault measure_bandwidth
OBJS_NET = setup_close_client setup_close_server bandwidth_client bandwidth_server measure_rtt_server measure_rtt_client measure_rtt_client_remote
OBJS_FS = measure_filecache read_file contention

all: $(OBJS_CPU) $(OBJS_MEM) $(OBJS_NET) $(OBJS_FS)

cpu: $(OBJS_CPU)
$(OBJS_CPU): %: $(SOURCEDIR_CPU)/%.c $(UTILSDIR)/*.h
	$(CC) $(CFLAGS) -o $(EXECUTABLEDIR)/$@ $< $(LDLIBS)

mem: $(OBJS_MEM)
$(OBJS_MEM): %: $(SOURCEDIR_MEM)/%.c $(UTILSDIR)/*.h
	$(CC) $(CFLAGS) -o $(EXECUTABLEDIR)/$@ $< $(LDLIBS)

net: $(OBJS_NET)
$(OBJS_NET): %: $(SOURCEDIR_NET)/%.c $(UTILSDIR)/*.h
	$(CC) $(CFLAGS) -o $(EXECUTABLEDIR)/$@ $< $(LDLIBS)

fs: $(OBJS_FS)
$(OBJS_FS): %: $(SOURCEDIR_FS)/%.c $(UTILSDIR)/*.h
	$(CC) $(CFLAGS) -o $(EXECUTABLEDIR)/$@ $< $(LDLIBS)
	
clean:
	rm -f $(EXECUTABLEDIR)/*
