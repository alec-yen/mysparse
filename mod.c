#include "cs.h"
#include "mysparse.h"

/*modify an existing triplet value, when passed compressed matrix, index, and new value*/

void mod(cs *A, int r, int c, double v)
{
	int m, n, nz, *i, *p, a, b, k, found;
	double *x, cv; /*cv is current value*/
	
	found = 0;
	m = A->m; n = A->n; i = A->i; p = A->p; x = A->x; nz = A->nz;
	a = p[c];
	b = p[c+1];

	cv = acc (A,r,c);	
	if (cv==0 || cv==999) { return; }

	for (k=0;k<b-a;k++) { if (r == i[k+a]) { found = 1; break; } }

	x[p[c]+k] = v;
}


/*removes triplet from compressed matrix
essentially alters a value to 0 and drops zeros*/

void del(cs *A, int r, int c)
{
	mod (A,r,c,0);
	cs_dropzeros (A);
}
