main : main.c client.o server.o calcul.h
	gcc $^ -o main #-Wall

client.o : client.c calcul.h
	gcc -c $< -o $@ -Wall

server.o : server.c calcul.h
	gcc -c $< -o $@ #-Wall
