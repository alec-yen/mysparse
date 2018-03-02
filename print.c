#include "mysparse.h"

/*returns value at give row and column of a matrix
item (i, j) can be accessed as data[indptr[j]+k], where k is position of i in indices[indptr[j]:indptr[j+1]]*/

double acc(const cs *A, int r, int c)
{
	int p;
	if (A->nz == -1)
	{	
		for (p = A->p[c] ; p < A->p[c+1] ; p++) { if (r == A->i[p]) return A->x[p]; } /*return if found*/
	}
	else if (A->nz >= 0)
	{
		for (p=0; p<A->nz; p++)	{ if (A->i[p] == r && A->p[p] == c) return A->x[p]; }
	}
	return 0; /*return 0 if not found*/
}

/*print the three arrays of compressed sparse column format*/

int array (const cs *A)
{
	if (!A) return 1; /*return 1 if invalid*/
	
	int m,n,nz,nzmax, *i, *p, k;
	double *x;
	m = A-> m; n = A->n; i = A->i; p = A->p; x = A->x; nzmax = A->nzmax; nz = A->nz;
	if (nz == -1)
	{
		printf ("%d-by-%d Compressed Matrix of %d Elements",m,n,nzmax);
		printf ("\nRow indices:\t");
		for (k=0;k<nzmax;k++) /*print row indices array*/ { printf ("%d\t",i[k]); }
		printf ("\nCol pointers:\t");
		for (k=0;k<n+1;k++) /*print column pointer array*/ { printf ("%d\t",p[k]); }
		printf ("\nValues:\t\t");
		for (k=0;k<nzmax;k++) /*print values array*/ { printf ("%.2f\t",x[k]); }
		printf ("\n\n");
	}
	else if (nz >= 0)
	{
		printf ("%d-by-%d Triplet Matrix of %d Elements",m,n,nz);
		printf ("\nRow indices:\t");
		for (k=0;k<nz;k++) /*print row indices array*/ { printf ("%d\t",i[k]); }
		printf ("\nCol indices:\t");
		for (k=0;k<nz;k++) /*print column indices array*/ { printf ("%d\t",p[k]); }
		printf ("\nValues:\t\t");
		for (k=0;k<nz;k++) /*print values array*/ { printf ("%.2f\t",x[k]); }
		printf ("\n\n");
	}
	else return 1;
	return 0; /*return 0 if success*/
}

/*prints compressed matrix onto screen*/

int print (const cs *A)
{
	if (!A) return 1; /*return 1 if invalid*/
	int r,c,m,n,nz;
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
