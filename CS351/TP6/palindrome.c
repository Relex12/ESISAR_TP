#include <stdio.h>

int palindrome (int n, char* mot) {
	if (n == 0 || n == 1) return 1;
	else if (mot[0] != mot[n-1]) return 0;
  	else {
    		mot = mot+1;      // j'y crois pas trop mais en gros on fait pointer mot vers mot[1]
	return (palindrome((n-2), mot);		// peut etre n-1, mais bon
	}
// 	return ((n<2) || mot[0] != mot[n-1] && palindrome(n-2, tab+1);
}

int main() {
	printf ("kayak est-il palindrome ? %d\n", palindrome(5, kayak));
	printf ("chips est-il palindrome ? %d\n", palindrome(5, chips));
	return (0);
}
