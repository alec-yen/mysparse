#include "cs.h"
#include "mysparse.h"

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


cs* add_jac (jac_mat s, int* r, int* c, double* v, int size)
{
	int k,m,n,max;
	cs* T;

	if (s!=Fx && s!=Fy && s!=Gx && s!=Gy && s!=Fx0 && s!=Fy0 && s!=Gx0 && s!=Gy0)
	{
		printf ("Wrong Jacobian matrix name\n");
		return NULL;
	}
	
	max = r[0]; /*find m-by-n of matrix*/
	for (k=1;k<size;k++) { if (r[k]>max) { max = r[k]; } }
	m = max;
	max = c[0];
	for (k=1;k<size;k++) { if (c[k]>max) { max = c[k]; } }
	n = max;
	m++; n++;

	T = acc_jac (s,m,n);
	for (k=0; k<size; k++) { cs_entry (T,r[k],c[k],v[k]); }
	return T;
}

cs* set_jac (jac_mat s, int* r, int* c, double* v, int size)
{

}
