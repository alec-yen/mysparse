#include "cs.h"
#include "mysparse.h"

/*access a value, if given compressed matrix, row and column index
item (i, j) can be accessed as data[indptr[j]+k], where k is position of i in indices[indptr[j]:indptr[j+1]]*/

double acc(const cs *A, int r, int c)
{

	if (errbound(A,r,c)) return 0; /*return 0 if outside bounds*/
	int *i, *p, a, b, k, found;
	double *x, v;
	found = 0;
	if (A->nz == -1)
	{	
		i = A->i; p = A->p; x = A->x;
		a = p[c]; b = p[c+1];
		for (k=0;k<b-a;k++) { if (r == i[k+a]) { found = 1; break; } }
		if (!found) return 0; /*return 0 if not found*/
		v = x[p[c]+k];
		return v; /*return value if found*/
	}
	else if (A->nz >= 0)
	{
		for (k=0; k<A->nz; k++)	if (A->i[k] == r && A->p[k] == c) {v = A->x[k]; found = 1; break;}
		if (!found) return 0;
		return v;
	}
	//add else statement
}
