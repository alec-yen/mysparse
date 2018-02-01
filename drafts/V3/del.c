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
		return 0; /*return 0 if success*/
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
	if (!A) return 4; /*return 1 if invalid*/
	int k,nz,nzmax,*i,*p,ok,n;
	double *x;
	ok = 1; nz = A->nz; n = A->n; i = A->i; p = A->p; x = A->x;
	if (nz == -1)
	{
		A->i = cs_realloc (i,0,sizeof(CS_INT),&ok);
		A->x = cs_realloc (x,0,sizeof(CS_ENTRY),&ok);		
		A->nzmax = 0;
		for (k=0;k<n+1;k++) p[k]=0;
		return 0; /*return 0 if success*/
	}
	else if (nz >= 0) { A->nz = 0; return 0; }
	else return 4;
}
