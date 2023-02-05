CC ?= gcc 
CFLAGS = -g -Wall -O0 -std=c99
EXECUTABLEDIR = ./bin
UTILSDIR = ./src/utils
SOURCEDIR_CPU = ./src/cpu
OBJS_CPU = cycle_counter procedure

cpu: $(OBJS_CPU)

cycle_counter : $(SOURCEDIR_CPU)/cycle_counter.c 
	$(CC) $(CFLAGS) -o $(EXECUTABLEDIR)/$@ $<

procedure : $(SOURCEDIR_CPU)/measure_procedure.c $(UTILSDIR)/cycle_counter.h
	$(CC) $(CFLAGS) -o $(EXECUTABLEDIR)/$@ $<

clean:
	rm -f $(EXECUTABLEDIR)/*