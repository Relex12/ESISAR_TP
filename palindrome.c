#include <stdio.h>

int palindrome (int n, char* mot) {
  if (n == 0 || n == 1) return 1;
  if (mot[0] != mot[n-1]) return 0;
  else {
    mot = mot+1;      // j'y crois pas trop mais en gros on fait pointer mot vers mot[1]
    return (palindrome((n-2), mot);		// peut etre n-1, mais bon
  }
}

int main() {
	printf ("kayak est-il palindrome ? %d\n", palindrome(5, kayak));
	printf ("chips est-il palindrome ? %d\n", palindrome(5, chips));
	return (0);
}
