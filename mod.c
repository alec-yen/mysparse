#include "cs.h"
#include "mysparse.h"

/*modify an existing triplet value, when passed compressed matrix, index, and new value*/

int mod(cs *A, int r, int c, double v)
{
	if (errbound(A,r,c)) return 2; /*return 2 if outside bounds*/
	if (!(acc(A,r,c))) return 1; /*return 1 if no value at index*/
	
	int *i, *p, a, b, k;
	double *x;

	if (A->nz == -1)
	{
		i = A->i; p = A->p; x = A->x;
		a = p[c];
		b = p[c+1];
		for (k=0;k<b-a;k++) { if (r == i[k+a]) break; }
		x[p[c]+k] = v;
		return 0; /*return 0 if successful*/
	}
	else if (A->nz >= 0)
	{
		for (k=0; k<A->nz; k++){ if (A->i[k] == r && A->p[k] == c) break; }
		A->x[k] = v;
		return 0;
	}
	else return 3; /*return 3 if invalid*/
}


/*removes triplet from compressed matrix
essentially alters a value to 0 and drops zeros*/

int del(cs *A, int r, int c)
{
	int err = mod (A,r,c,0);
	if (!err) cs_dropzeros (A);
	return err;
}
