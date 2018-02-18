#include "mysparse.h"

int frandmat(char* f, int m, int n, double sparsity)
{
	FILE* fp = fopen( f , "w");	
	int i,j;
	int nz = m*n*sparsity;
	cs* T = cs_spalloc (m,n,nz,1,1);
	for (i=0; i<m; i++)
	{
		for (j=0; j<n; j++)
		{
			if ( ( ((double)rand()/(double)RAND_MAX) < sparsity ) && (T->nz < nz) ) cs_entry (T,i,j,1);
		}
	}
	for (i=0; i<T->nz; i++)
	{
		fprintf (fp, "%d %d %.2f\n", T->i[i], T->p[i], T->x[i]);
	}
	cs_spfree (T);
	fclose(fp);
	return 0;

}
