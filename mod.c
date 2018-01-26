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
		a = p[c];
		b = p[c+1];
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


/*removes triplet from compressed matrix
essentially alters a value to 0 and drops zeros*/

int del(cs *A, int r, int c)
{
	int err,nz,ok;
	int k,s;
	ok = 1;
	nz = A->nz;
	if (nz == -1)
	{
		err = mod (A,r,c,0);
		if (err) return err;
		cs_dropzeros (A); /*works only on compressed*/
		return err;
	}
	else if (nz >= 0)
	{
		err = mod (A,r,c,0);
		if (err) return err;
		for (k=0;k<nz;k++) { if (A->x[k]==0) break; }
		for (s=k;s<nz-1;s++)
		{
			A->i[s] = A->i[s+1];
			A->p[s] = A->p[s+1];
			A->x[s] = A->x[s+1];
		}
		A->nz--;
		return err;
	}
}
