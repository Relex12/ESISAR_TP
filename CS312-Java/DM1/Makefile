all :
	echo "exo 1 : précisez class1, class2, chrono, time ou clean"
	echo "exo 2 : précisez fraction, division ou clean"
	echo "les réponses aux questions se trouvent en commentaire dans main.java et fraction.java"

clean :
	rm *.class

class1 : chrono1.java
	javac chrono1.java

class2 : chrono2.java
	javac chrono2.java

chrono : chrono.java class1 class2
	javac chrono.java

time : chrono
	java chrono


fraction : fraction.java
	javac fraction.java

division : division.java fraction
	javac division.java
	java division
