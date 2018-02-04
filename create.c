#include "cs.h"
#include "mysparse.h"

/*returns empty compressed or triplet matrix */

cs* create (int m, int n, int triplet)
{
	if (errsize (m,n)) return NULL;
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

/*removes all values from a matrix*/

int clear(cs *A)
{
	if (!A) return 4; /*return 1 if invalid*/
	int k,nz,nzmax,*i,*p,ok,n;
	double *x;
	ok = 1; nz = A->nz; n = A->n; i = A->i; p = A->p; x = A->x;
	if (nz == -1)
	{
		A->i = cs_realloc (i,0,sizeof(CS_INT),&ok);
		A->x = cs_realloc (x,0,sizeof(CS_ENTRY),&ok);		
		A->nzmax = 0;
		for (k=0;k<n+1;k++) p[k]=0;
		return 0; /*return 0 if success*/
	}
	else if (nz >= 0) { A->nz = 0; return 0; }
	else return 4;
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
