CC ?= gcc 
CFLAGS = -g -Wall -O0 -std=c99 -lm -lpthread
EXECUTABLEDIR = ./bin
UTILSDIR = ./src/utils
SOURCEDIR_CPU = ./src/cpu
OBJS_CPU = cycle_counter measure_procedure measure_task

cpu: $(OBJS_CPU)

$(OBJS_CPU): % : $(SOURCEDIR_CPU)/%.c
	$(CC) $(CFLAGS) -o $(EXECUTABLEDIR)/$@ $<

clean:
	rm -f $(EXECUTABLEDIR)/*