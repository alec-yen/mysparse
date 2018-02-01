#include "cs.h"
#include "mysparse.h"

/*modify an existing element value, when passed matrix, index, and new value*/

int mod(cs *A, int r, int c, double v)
{
	if (!A) return 4; /*return 4 if invalid*/
	if (errbound(A,r,c)) return 3; /*return 3 if outside bounds*/
	if (v==0) return 1; /*return 1 if value is zero*/
	if (!acc(A,r,c)) return 2; /*return 2 if no value at index*/	

	int *i, *p, a, b, k, nz;
	double *x;
	i = A->i; p = A->p; x = A->x; nz = A->nz;

	if (nz == -1)
	{
		a = p[c]; b = p[c+1];
		for (k=0;k<b-a;k++) { if (r == i[k+a]) break; }
		x[p[c]+k] = v;
		return 0; /*return 0 if successful*/
	}
	else if (nz >= 0)
	{
		for (k=0; k<nz; k++){ if (i[k] == r && p[k] == c) break; }
		x[k] = v;
		return 0;
	}
	else return 4; /*return 4 if invalid*/
}
