#include "cs.h"
#include "mysparse.h"

//int jac_storage[] = {0,1,2,3,4,5,6,7};
/*
cs* acc_jac (jac_mat s, int m, int n)
{
	cs* T;
	if (s==Fx) { T = cs_spalloc (m,n,m*n,1,1); }
	if (s==Fy) { T = cs_spalloc (m,n,m*n,1,1); }
	if (s==Gx) { T = cs_spalloc (m,n,m*n,1,1); }
	if (s==Gy) { T = cs_spalloc (m,n,m*n,1,1); }
	if (s==Fx0) { T = cs_spalloc (m,n,m*n,1,1); }
	if (s==Fy0) { T = cs_spalloc (m,n,m*n,1,1); }
	if (s==Gx0) { T = cs_spalloc (m,n,m*n,1,1); }
	if (s==Gy0) { T = cs_spalloc (m,n,m*n,1,1); }
	return T;
}
*/

cs* add_jac (jac_mat s, int* r, int* c, double* v, int size)
{

	int k;
	if (s!=Fx && s!=Fy && s!=Gx && s!=Gy && s!=Fx0 && s!=Fy0 && s!=Gx0 && s!=Gy0)
	{
		printf ("Wrong Jacobian matrix name\n");
		return NULL;
	}
	cs* T = jac_storage [s];
	for (k=0;k<size;k++)
	{
		if (cs_entry (T,r[k],c[k],v[k])) {
			printf ("Attempt %d\n",k);
		}
	}
	return T;
}

cs* set_jac (jac_mat s, int* r, int* c, double* v, int size)
{

}
