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
		cs_entry (T,i,j,x);
	}
	C = cs_compress (T);
	cs_spfree (T);
	return C;
}
