#include "cs.h"
#include "mysparse.h"

/*removes value from matrix*/

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

int clear(cs *A)
{
	int k,nz;
	nz = A->nz;
	for (k=0;k<nz;k++) if (del(A,A->i[0],A->p[0])) return 1;
}
