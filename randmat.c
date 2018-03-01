#include "mysparse.h"
#include <string.h>

/*write random matrix to file*/
int frandmat(char* f, int m, int n, double sparsity, int seed)
{
	FILE* fp = fopen( f , "w");	
	int i,j;
	int nz = m*n*sparsity;
	cs* T = cs_spalloc (m,n,nz,1,1);
	srand (seed);
	for (i=0; i<m-1; i++)
	{
		for (j=0; j<n-1; j++)
		{
			if ( ( ((double)rand()/(double)RAND_MAX) < sparsity ) && (T->nz < nz-1) )
			cs_entry (T,i,j,1);
		}
	}
	cs_entry (T,m-1,n-1,1); /*ensure size of m rows and n columns*/
	for (i=0; i<T->nz; i++)
	{
		fprintf (fp, "%d %d %.2f\n", T->i[i], T->p[i], T->x[i]);
	}
	cs_spfree (T);
	fclose(fp);
	return 0;
}

/*create random matrix file name*/
char* name (int rows, double sparsity, int seed)
{
	char buffer_rows[10];
	char buffer_spars[10];
	char buffer_seed[10];
	int len = sprintf (buffer_rows,"%05d",rows);
	len += sprintf (buffer_spars,"%.3f",sparsity);
	len += sprintf (buffer_seed,"%02d",seed);
	char* fname = malloc (len+15);
	strcpy (fname, "data/m");
	strcat (fname, buffer_rows); strcat (fname, "_");
	strcat (fname, buffer_seed); strcat (fname, "_");
	strcat (fname, buffer_spars); strcat (fname, ".txt");
	return fname;
}

/*create random matrix*/
cs* randmat(int m, int n, double sparsity, int seed)
{
	int i,j;
	int nz = m*n*sparsity;
	cs* T = cs_spalloc (m,n,nz,1,1);
	srand (seed);
	for (i=0; i<m; i++)
	{
		for (j=0; j<n; j++)
		{
			if ( ( ((double)rand()/(double)RAND_MAX) < sparsity ) && (T->nz < nz) ) cs_entry (T,i,j,1);
		}
	}
	return T;

}
