#include "mysparse.h"

/*returns empty compressed or triplet matrix */
cs* ecreate (int m, int n, int trip)
{
	int k; cs* A;
	if (!trip)
	{
		A = cs_spalloc (m,n,0,1,0);
		A->nzmax = 0;
		for (k=0;k<n+1;k++) A->p[k]=0;
	}
	else A = cs_spalloc (m,n,m*n,1,1);
	return A;
}


/*returns filled compressed matrix*/
cs* fcreate (int m, int n, int* i, int* j, double* x, int size, int trip)
{
	int k;
	cs* A = ecreate (m,n,1);
	for (k=0;k<size;k++) { cs_entry(A,i[k],j[k],x[k]); }
	if (!trip)
	{
		cs* C = cs_compress (A);
		cs_spfree (A);
		return C;
	}
	else return A;
}



/*removes all values from a matrix*/
int clear(cs *A)
{
	if (!A) return 1; /*return 1 if invalid*/
	int k,nz,*i,*p,ok,n;
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
	else return 1;
}
