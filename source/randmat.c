#include "mysparse.h"

/*write random matrix to file*/
int frandmat(char* f, int m, int n, double sparsity, int seed, int val)
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
			cs_entry (T,i,j,val);
		}
	}
	cs_entry (T,m-1,n-1,val); /*ensure size of m rows and n columns*/
	for (i=0; i<T->nz; i++)
	{
		fprintf (fp, "%d %d %.2f\n", T->i[i], T->p[i], T->x[i]);
	}
	cs_spfree (T);
	fclose(fp);
	return 0;
}


/*create random csc matrix*/
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
			if ( ( ((double)rand()/(double)RAND_MAX) < sparsity ) && (T->nz < nz) ) cs_entry (T,i,j,rand()%100);
		}
	}
	cs* C = cs_compress (T);
	cs_spfree (T);
	return C;

}
