# commandes
all:
	echo "Precisez decode, registre, memoire ou clean"
	echo "Pour les .o : decodage.o,registre.o ou memoire.o"

clean :
	rm main memoire decode registre *.o


# exécutables de test
decode : decodage.c decodage.h
	gcc -g -Wall -lm -D TESTS decodage.c -o decodage

memoire : memoire.c memoire.h
	gcc -g -Wall -D TESTS memoire.c -o memoire

registre : registre.c registre.h
	gcc -g -Wall -D TESTS registre.c -o registre


# fichiers liens
decodage.o : decodage.c decodage.h
	gcc -g -Wall -c decodage.c -Wall -o decodage.o

memoire.o : memoire.c memoire.h
	gcc -g -Wall -c memoire.c -o memoire.o

registre.o : registre.c registre.h
	gcc -g -Wall -c registre.c -o registre.o


# main
main : main.c memoire.o registre.o
	gcc -g -Wall main.c memoire.o registre.o -o main
