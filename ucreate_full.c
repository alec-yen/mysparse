#include "cs.h"
#include "mysparse.h"
#include <stdio.h>
#include <stdlib.h>


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
    T = cs_spalloc (m,n,m*n,1,1);
    for (k=0;k<size;k++)
    {
        if (!cs_entry(T,r[k],c[k],v[k]))
        {
            printf ("cs_entry failed\n");
            return NULL;
        }
    }
    return T;
}
