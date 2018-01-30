#include "cs.h"
#include "mysparse.h"
#include <stdio.h>
#include <stdlib.h>

/*returns compressed matrix of size m by n
returns empty matrix if cond == 0
returns matrix with one element if cond != 0 (mechanism for add function)
changes triplet matrix A to compressed matrix AC*/

cs* ccreate_empty (char *name, int m, int n, int cond, int r, int c, double v)
{
	FILE * fp1;
	cs *A, *AC;

	fp1 = fopen (name , "w");
	fprintf (fp1, "%d %d %.2f\n", m-1, n-1, 0.00);
	fclose (fp1);
	fp1 = fopen (name, "r");
	A = cs_load (fp1);
	if (cond) { cs_entry (A,r,c,v); } /*if cond != 0, input a value*/
	AC = cs_compress (A);
	fclose (fp1);
	cs_spfree(A);
	cs_dropzeros(AC);
	return AC;
}

/*returns uncompressed matrix with nzmax = max_count*/

cs* ucreate_empty (int nzmax)
{
	cs* T;
	T = (cs*) malloc(sizeof(cs));
	int* i = (int*) malloc(nzmax * sizeof(int));
	int* j = (int*) malloc(nzmax * sizeof(int));
	double* t = (double*) malloc(nzmax * sizeof(double));
	T->i = i; T->p = j; T->x = t;
	T->m = 0; T->n = 0;
	T->nz = 0; T->nzmax = nzmax;
	return T;
}

/*returns compressed matrix with row, col, and val arrays passed*/

cs* ccreate_full (cs *T, int r[], int c[], double v[], int size)
{
	int k,m,n,max; cs* TC;
	int *i,*j; double *t;
	max = r[0];
	for (k=1;k<size;k++) { if (r[k]>max) { max = r[k]; } }
	m = max;
	max = c[0];
	for (k=1;k<size;k++) { if (c[k]>max) { max = c[k]; } }
	n = max;
	m++; n++;

	i = T->i; j = T->p; t = T->x; //remember where the pointers are
	T->i = r; T->p = c; T->x = v;
	T->m = m; T->n = n; T->nz += size;

	TC = cs_compress(T);
	free (i); free (j); free (t); free (T);
	return TC;
}
