#include "cs.h"
#include "mysparse.h"

/*removes value from matrix*/

int del(cs *A, int r, int c)
{
	if (!A) return 4; /*return 4 if invalid*/
	if (errbound(A,r,c)) return 3; /*return 3 if outside bounds*/
	if (!(acc(A,r,c))) return 2; /*return 2 if no value at index*/

	int k,s,a,b,nz,*i, *p;
	double *x;
	i = A->i; p = A->p; x = A->x; nz = A->nz;
	if (nz == -1)
	{
		a = p[c]; b = p[c+1];
		for (k=0;k<b-a;k++) { if (r == i[k+a]) break; }
		x[p[c]+k] = 0;
		cs_dropzeros (A); /*works only on compressed*/
		return 0;
	}
	else if (nz >= 0)
	{
		for (k=0; k<nz; k++){ if (i[k] == r && p[k] == c) break; }
		for (s=k;s<nz-1;s++)
		{
			A->i[s] = A->i[s+1];
			A->p[s] = A->p[s+1];
			A->x[s] = A->x[s+1];
		}
		A->nz--;
		return 0;
	}
	else return 4; /*return 4 if invalid matrix*/
}

/*removes all values from a matrix*/

int clear(cs *A)
{
	int k,nz,nzmax,*i,*p;
	nz = A->nz; nzmax = A->nzmax; i = A->i; p = A->p;
	if (nz == -1)
	{
		int r,c;
		for (r=0;r<A->m;r++)
		{
			for (c=0;c<A->n;c++)
			{
				del (A,r,c);
			}
		}
		return 0;
	}
	else if (nz >= 0)
	{
		for (k=0;k<nz;k++)
		{
			if (del(A,i[0],p[0])) return 1;
		}
		return 0;
	}
	else return 4; /*return 4 if invalid matrix*/
}
