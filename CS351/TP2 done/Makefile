# ceci est un commentaire


all : 
	echo "precisez jeu ou pgcd ou pgcd_pts ou test_math_lib ou dessine ou clean"

clean :
	rm jeu pgcd pgcd_pts test_math_lib

jeu : jeu.c 
	gcc -Wall $< -o $@

pgcd : pgcd.c math_lib.h
	gcc -Wall $^ -o $@

pgcd_pts : pgcd.c
	gcc -Wall $^ -D MISEAUPOINT -o $@

test_math_lib : math_lib.c math_lib.h pgcd.c
	gcc -Wall $^ -D LIBRARY -o $@

#bibliothèque graphlib trop compliquée à utiliser



