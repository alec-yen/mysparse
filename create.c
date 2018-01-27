#include "cs.h"
#include "mysparse.h"

/*returns empty compressed or triplet (uncompressed) matrix */

cs* create (int m, int n, int triplet)
{
	int k; cs* T;
	if (!triplet)
	{
		T = cs_spalloc (m,n,0,1,0);
		T->nzmax = 0;
		for (k=0;k<n+1;k++) T->p[k]=0;
	}
	else if (triplet) T = cs_spalloc (m,n,m*n,1,1);
	return T;
}


/*returns triplet matrix with nzmax = m*n */

cs* ucreate_full (int *r, int *c, double *v, int size)
{
    int k,m,n,max; cs* T;
    max = r[0];
    for (k=1;k<size;k++) { if (r[k]>max) { max = r[k]; } }
    m = max;
    max = c[0];
    for (k=1;k<size;k++) { if (c[k]>max) { max = c[k]; } }
    n = max;
    m++; n++;
    T = cs_spalloc (m,n,m*n,1,1); //check this line m*n vs size
    for (k=0;k<size;k++)
    {
        if (!cs_entry(T,r[k],c[k],v[k]))
        {
            return NULL;
        }
    }
    return T;
}
