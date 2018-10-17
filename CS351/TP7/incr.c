#include <stdio.h>

void incr(int *a) 
{
	*a = (*a) + 1;
}

int main()
{
	int x = 5;
	incr(&x);
	printf("%d", x); /* ce programme affiche 6 */
	return 0;
}
