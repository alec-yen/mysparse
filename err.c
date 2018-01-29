#include "cs.h"
#include "mysparse.h"

/*check if index is within bounds of matrix*/

int errbound (const cs* A, int r, int c)
{
	int m,n;
	m = A->m; n = A->n;
	if (r>m-1 || c>n-1 || r<0 || c<0) return 1;
	return 0;
}

/*check if m and n are positive*/

int errsize (int m, int n)
{
	if (m<0 || n<0) return 1;
	return 0;
}

/*check if passed arrays values are all positive
for indices array, stores number of rows/columns in max*/

int errarr (const int* a, int* max, int size)
{
	int k, temp;
	*max = a[0];
	for (k=0;k<size;k++)
	{
		if (a[k] < 0) return 1;
		if (a[k] > *max) *max = a[k];
	}
	(*max)++;
	printf ("%d\n", *max);
	return 0;
}
