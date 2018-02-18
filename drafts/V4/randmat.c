#include "mysparse.h"

cs* randmat(int m, int n, double sparsity)
{
	int k,nz,i,j;
	double x=1;
	nz = m*n*sparsity;
	cs* C;
	cs* T = cs_spalloc (m,n,nz,1,1);
	for (k=0; k<nz; k++)
	{
		i = rand() % m;
		j = rand() % n;
//		cs_entry (T,k,k,x);
		if (!acc(T,i,j)) cs_entry (T,i,j,x);
	}
	C = cs_compress (T);
	cs_spfree (T);
	return C;
}

int frandmat(char* f, int m, int n, double sparsity)
{
	FILE* fp = fopen( f , "w");	
	int k,nz,i,j;
	nz = m*n*sparsity;
	double x = 1;
	cs* T = cs_spalloc (m,n,nz,1,1);
	for (k=0; k<nz; k++)
	{
		i = rand() % m;
		j = rand() % n;
//		cs_entry (T,k,k,x);
		if (!acc(T,i,j)) cs_entry (T,i,j,x);
	}
	for (k=0; k<T->nz; k++)
	{
		fprintf (fp, "%d %d %.2f\n", T->i[k], T->p[k], T->x[k]);
	}
	cs_spfree (T);
	fclose(fp);
	return 0;

}
