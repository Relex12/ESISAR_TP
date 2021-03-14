all:
	make app
	make module
	make test-app

clean:
	rm app module.o module.so test-app

app: my_app.c
	gcc -Wall my_app.c -o app -lpam -lpam_misc

module.o: module.c
	gcc -fPIC -c module.c -o module.o

module: module.o
	gcc -shared -o module.so module.o -lpam
	sudo cp module.so /lib/security/

test-app: test-app.c
	gcc -Wall test-app.c -o test-app -lpam -lpam_misc
