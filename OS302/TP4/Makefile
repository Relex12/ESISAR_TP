all :
	echo "pr�cisez exo1 ou main"

exo1 : exo1.c
	gcc -Wall exo1.c -o exo1

main : main.c client.o server.o calcul.h
	gcc $^ -o main #-Wall

client.o : client.c calcul.h
	gcc -c $< -o $@ -Wall

server.o : server.c calcul.h
	gcc -c $< -o $@ #-Wall
