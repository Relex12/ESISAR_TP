CFLAGS= -Wall
CC=gcc

all: swp

clean:
	rm -f *.o swp

swp: simulator.o lib.o swp.o
	$(CC) $(CFLAGS) -o swp swp.o simulator.o lib.o

swp.o: protocol.h

simulator.o: simulator.h protocol.h

lib.o: simulator.h protocol.h

