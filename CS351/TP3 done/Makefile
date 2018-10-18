all : 
	echo "precisez notes ou arguments ou matrice ou clean"

clean :
	rm notes arguments matrice

notes : gestion_notes.c
	gcc -Wall $< -lm -o $@

arguments : arg_main.c
	gcc -Wall $< -lm -o $@

matrice : matrice.c
	gcc -Wall $< -lm -o $@

