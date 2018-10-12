#include <stdio.h>

int palindrome (int n, char* mot) {
  if (n == 0 || n == 1) return 1;
  if (mot[0] != mot[n]) return 0;
  else {
    mot = mot+1;      // j'y crois pas trop mais en gros on fait pointer mot vers mot[1]
    return (palindrome((n-2), mot);
  }
}

int main() {
	printf ("Kayak est-il palindrome ? %d\n", palindrome(kayak));
	printf ("chips est-il palindrome ? %d\n", palindrome(chips));
	return (0);
}
