CC = gcc
#OPT = -O3 -m32
#OPT = -g -m32
OPT = -g  
WARN = -Wall
CFLAGS = $(OPT) $(WARN) 

SIM_SRC = main.c

SIM_OBJ = main.o
 


all: sim_cache
	@echo "my work is done here..."


sim_cache: $(SIM_OBJ)
	$(CC) -o sim $(CFLAGS) $(SIM_OBJ) -lm
	@echo "-----------DONE WITH SIM_CACHE-----------"


.cc.o:
	$(CC) $(CFLAGS)  -c $*.cc

clean:
	rm -f *.o sim_cache



clobber:
	rm -f *.o
