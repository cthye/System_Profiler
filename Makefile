CC?=gcc
CFLAGS=-O0
SOURCEDIR=./src/cpu
EXECUTABLEDIR=./bin
OBJS=cycle_counter

all: $(OBJS)

$(OBJS): %: $(SOURCEDIR)/%.c
	$(CC) $(CFLAGS) -o $(EXECUTABLEDIR)/$@ $<


clean:
	rm -f $(EXECUTABLEDIR)/*