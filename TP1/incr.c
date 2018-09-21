#include <stdio.h>

int main() {
	int i, j, k, l;
	i = j = k = l = 0;
	while(i < 9) {
		printf("i++ = %d, ++j = %d, k-- = %d, --l = %d\n",
		i++, ++j, k--, --l);
	}
	printf ("i = %d, j = %d, k = %d, l = %d\n", i, j, k, l);
	return (0);
}

/*
i ++; renvoit i puis donne la valeur i+1 à i
++ j; donne la valeur j+1 à j puis renvoit j
*/
