#include "cs.h"
#include "mysparse.h"

/*modify an existing triplet value, when passed compressed matrix, index, and new value*/

int mod(cs *A, int r, int c, double v)
{
	if (!A) return 4; /*return 4 if invalid*/
	if (errbound(A,r,c)) return 3; /*return 3 if outside bounds*/
	if (!(acc(A,r,c))) return 2; /*return 2 if no value at index*/
	
	int *i, *p, a, b, k, found;
	double *x;
	found = 0;

	if (A->nz == -1)
	{
		i = A->i; p = A->p; x = A->x;
		a = p[c]; b = p[c+1];
		for (k=0;k<b-a;k++) { if (r == i[k+a]) {found=1; break; } }
		if(found) x[p[c]+k] = v;
		else return 2;
		return 0; /*return 0 if successful*/
	}
	else if (A->nz >= 0)
	{
		for (k=0; k<A->nz; k++){ if (A->i[k] == r && A->p[k] == c) {found=1; break; } }
		if(found) A->x[k] = v;
		else return 2;
		return 0;
	}
	else return 4; /*return 4 if invalid*/
}
