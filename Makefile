CC ?= gcc 
CFLAGS = -g -Wall -O0 -std=c99 
LDLIBS = -lm -lpthread
EXECUTABLEDIR = ./bin
UTILSDIR = ./src/utils
SOURCEDIR_CPU = ./src/cpu
OBJS_CPU = cycle_counter measure_procedure measure_syscall measure_task

all: $(OBJS_CPU)

$(OBJS_CPU): %: $(SOURCEDIR_CPU)/%.c $(UTILSDIR)/*.h
	$(CC) $(CFLAGS) -o $(EXECUTABLEDIR)/$@ $< $(LDLIBS)

clean:
	rm -f $(EXECUTABLEDIR)/*