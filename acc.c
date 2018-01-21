#include "cs.h"
#include "mysparse.h"

/*access a value, if given compressed matrix, row and column index
item (i, j) can be accessed as data[indptr[j]+k], where k is position of i in indices[indptr[j]:indptr[j+1]]*/

double acc(const cs *A, int r, int c)
{
	int m, n, nz, *i, *p, a, b, k, found;
	double *x, v;

	found = 0;
	m = A->m; n = A->n; i = A->i; p = A->p; x = A->x; nz = A->nz;
	if (r>m-1 || c>n-1 || r<0 || c<0) { return 999; } /*return 999 if outside bounds*/

	a = p[c];
	b = p[c+1];

	for (k=0;k<b-a;k++) { if (r == i[k+a]) { found = 1; break; } }
	if (!found) { return 0; } /*return 0 if not found*/

	v = x[p[c]+k];
	return v; /*return value if found*/
}
