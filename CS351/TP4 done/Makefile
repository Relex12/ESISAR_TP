all : 
	echo "precisez donnees ou string ou reboot ou clean"

clean :
	rm donnees string

reboot : 
	rm ans.txt
	touch ans.txt

donnees : donnees.c
	gcc -Wall $< -o $@

string : string.c
	gcc -Wall $< -o $@

