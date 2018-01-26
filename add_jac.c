#include "cs.h"
#include "mysparse.h"

/*allocates array of pointers to jacobian matrices*/
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

/*frees array of pointers to jacobian matrices*/
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

/*returns jacobian matrix given jac_name*/
cs* acc_jac (cs** jac_stor, jac_name s){
	return jac_stor[s];
}


/*returns triplet (uncompressed) matrix*/
void add_jac (cs** jac_stor, jac_name s, int* r, int* c, double* v, int size)
{
	cs* T;
	int k,err;
	T = acc_jac (jac_stor,s);
	for (k=0;k<size;k++)
	{
		err = set(T,r[k],c[k],v[k]);
		if (err) {
			printf ("set failed; err = %d\n", err);
			return;
		}
	}
}

/*returns triplet (uncompressed) matrix*/
void set_jac (cs** jac_stor, jac_name s, int* r, int* c, double* v, int size)
{
	cs* T;
	int k,err,nz;
	T = acc_jac (jac_stor,s);
	nz = T->nz;
	
	for (k=0;k<nz;k++){
		printf ("loop %d\n", k);
		printf ("On element %.2f\n", acc(T,T->i[0],T->p[0]));
		array (T);
		err = del(T,T->i[0],T->p[0]);
		if (err) {
			printf ("del failed; err = %d\n", err);
			return;	
		}
	}
	for (k=0;k<size;k++)
	{
		err = set(T,r[k],c[k],v[k]);
		if (err) {
			printf ("set failed; err = %d\n", err);
			return;
		}
	}
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
