CC=gcc
CFLAGS=-Wall -g
LDFLAGS=-lwebsockets -lm



narvalo: narvalo.o client.o
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

client.o: client.c narvalo.h client.h
	$(CC) $(CFLAGS) -o $@ -c $<

narvalo.o: narvalo.c narvalo.h
	$(CC) $(CFLAGS) -o $@ -c $<

clean:
	rm -rf *.o

mrproper: clean
	rm -rf $(EXEC)  
