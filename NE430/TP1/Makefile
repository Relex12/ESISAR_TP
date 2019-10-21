# nous obtenons un résultat de 87.78 % de réponses correctes
# avec la commande : ./main routes iptest.result

CC=gcc
CFLAGS=-Wall -g


main: main.o my.o
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)
main.o: main.c binome6MyAlgo.h
	$(CC) $(CFLAGS) -o $@ -c $<
my.o: binome6MyAlgo.c binome6MyAlgo.h
	$(CC) $(CFLAGS) -o $@ -c $<
clean:
	rm main *.o
