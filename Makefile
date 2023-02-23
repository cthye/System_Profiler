CC ?= gcc 
CFLAGS = -g -Wall -O0 -std=c99 
LDLIBS = -lm -lpthread
EXECUTABLEDIR = ./bin
UTILSDIR = ./src/utils
SOURCEDIR_CPU = ./src/cpu
SOURCEDIR_MEM = ./src/memory
OBJS_CPU = cycle_counter read_time_overhead context_switch_process context_switch_thread measure_syscall measure_task measure_procedure 
OBJS_MEM = measure_access page_fault measure_bandwidth

all: $(OBJS_CPU) $(OBJS_MEM)

cpu: $(OBJS_CPU)
$(OBJS_CPU): %: $(SOURCEDIR_CPU)/%.c $(UTILSDIR)/*.h
	$(CC) $(CFLAGS) -o $(EXECUTABLEDIR)/$@ $< $(LDLIBS)

mem: $(OBJS_MEM)
$(OBJS_MEM): %: $(SOURCEDIR_MEM)/%.c $(UTILSDIR)/*.h
	$(CC) $(CFLAGS) -o $(EXECUTABLEDIR)/$@ $< $(LDLIBS)

clean:
	rm -f $(EXECUTABLEDIR)/*