#include "cs.h"
#include "mysparse.h"

/*print the three arrays of compressed sparse column format*/

void csc (const cs *A)
{
	int m, n, nzmax, *i, *p, k, l, s, t;
	double *x;
	n = A->n; i = A->i; p = A->p; x = A->x; nzmax = A->nzmax;

	printf ("\nRow indices:\t");
	for (k=0;k<nzmax;k++) /*print row indices array*/ { printf ("%d\t",i[k]); }
	printf ("\nCol pointers:\t");
	for (k=0;k<n+1;k++) /*print column pointer array*/ { printf ("%d\t",p[k]); }
	printf ("\nValues:\t\t");
	for (k=0;k<nzmax;k++) /*print values array*/ { printf ("%.2f\t",x[k]); }
	printf ("\n\n");
}

/*prints compressed matrix onto screen*/

void print (const cs *A)
{
	printf ("%d-by-%d matrix of %d elements\n",A->m,A->n,A->nzmax);
	int r,c,m,n;
	double test;
	m = A->m; n = A->n;
	for (r=0; r<m; r++){
		for (c=0; c<n; c++){
			test = acc (A,r,c);
			printf ("%.0f\t", test);
		}
		printf ("\n");
	}
	printf ("\n");
}
