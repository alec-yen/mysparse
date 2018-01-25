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
		printf ("%d-by-%d Uncompressed Matrix of %d Elements\n",m,n,nz);
		for (r=0; r<m; r++){
			for (c=0; c<n; c++){
				for (k=0; k<nz; k++){
					found = 0;
					if (A->i[k] == r && A->p[k] == c)
					{ printf ("%.0f\t", A->x[k]); found = 1; break;}
				}
				if (!found) { printf ("%d\t", 0); }
			}
			printf ("\n");
		}
	}
	printf ("\n");
}
