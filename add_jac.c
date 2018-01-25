#include "cs.h"
#include "mysparse.h"


cs** alloc_jac (int m, int n)
{
	cs* Fx,*Fy,*Gx,*Gy,*Fx0,*Fy0,*Gx0,*Gy0;
	cs** jac_stor = malloc (8*sizeof(cs*));
	Fx = cs_spalloc (m,n,m*n,1,1);
	Fy = cs_spalloc (m,n,m*n,1,1);
	Gx = cs_spalloc (m,n,m*n,1,1);
	Gy = cs_spalloc (m,n,m*n,1,1);
	Fx0 = cs_spalloc (m,n,m*n,1,1);
	Fy0 = cs_spalloc (m,n,m*n,1,1);
	Gx0 = cs_spalloc (m,n,m*n,1,1);
	Gy0 = cs_spalloc (m,n,m*n,1,1);

	jac_stor[0]=Fx; jac_stor[1]=Fy; jac_stor[2]=Gx; jac_stor[3]=Gy;
	jac_stor[4]=Fx0; jac_stor[5]=Fy0; jac_stor[6]=Gx0; jac_stor[7]=Gy0;
	return jac_stor;
}

void free_jac (cs** jac_stor){
	cs_spfree (jac_stor[0]);
	cs_spfree (jac_stor[1]);
	cs_spfree (jac_stor[2]);
	cs_spfree (jac_stor[3]);
	cs_spfree (jac_stor[4]);
	cs_spfree (jac_stor[5]);
	cs_spfree (jac_stor[6]);
	cs_spfree (jac_stor[7]);
	free (jac_stor);
}

cs* acc_jac (cs** jac_stor, jac_name s){
	return jac_stor[s];
}


/*returns triplet (uncompressed) matrix*/
void add_jac (cs** jac_stor, jac_name s, int* r, int* c, double* v, int size)
{
	cs* T;
	int k,max,m,n;
	if (s!=Fx && s!=Fy && s!=Gx && s!=Gy && s!=Fx0 && s!=Fy0 && s!=Gx0 && s!=Gy0)
	{
		printf ("Wrong Jacobian matrix name\n");
		return;
	}

	
	T = acc_jac (jac_stor,s);
	for (k=0;k<size;k++)
	{
		if (!(cs_entry (T,r[k],c[k],v[k]))) {
			printf ("cs_entry failed\n");
			return;
		}
	}
}

/*returns triplet (uncompressed) matrix*/
cs* set_jac (jac_name s, int* r, int* c, double* v, int size)
{
	
}



/*
	max = r[0];
	for (k=1;k<size;k++) { if (r[k]>max) { max = r[k]; } }
	m = max;
	max = c[0];
	for (k=1;k<size;k++) { if (c[k]>max) { max = c[k]; } }
	n = max;
	m++; n++;
*/
