#include "cs.h"
#include "mysparse.h"

/*print the three arrays of compressed sparse column format*/

int csc (const cs *A)
{
	if (!A) return 1; /*return 1 if invalid*/
	if (A->nz != -1) return 1;

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
	return 0;
}

/*prints compressed matrix onto screen*/

int print (const cs *A)
{
	if (!A) return 1; /*return 1 if invalid*/
	int r,c,m,n,k,nz,found;
	m = A->m; n = A->n;
	double test;
	if (A->nz == -1){
		nz = A->nzmax;
		printf ("%d-by-%d Compressed Matrix of %d Elements\n",m,n,nz);
		for (r=0; r<m; r++){
			for (c=0; c<n; c++){
				test = acc (A,r,c);
				printf ("%.0f\t", test);
			}
			printf ("\n");
		}
	}
	else if (A->nz >= 0){
		nz = A->nz;
		printf ("%d-by-%d Triplet Matrix of %d Elements\n",m,n,nz);
		for (r=0; r<m; r++){
			for (c=0; c<n; c++){
				test = acc (A,r,c);
				printf ("%.0f\t",test);
			}
			printf ("\n");
		}
	}
	printf ("\n");
	return 0; /*return 0 if successful*/
}
