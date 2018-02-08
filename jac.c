#include "cs.h"
#include "mysparse.h"

int NUM_JAC = 8;

/*allocates array of pointers to jacobian matrices*/
cs** alloc_jac (int m, int n)
{
	int triplet = 0; /*allocate csc matrices*/
	cs* Fx,*Fy,*Gx,*Gy,*Fx0,*Fy0,*Gx0,*Gy0;
	cs** jac_stor = malloc (NUM_JAC*sizeof(cs*));
	Fx = ecreate (m,n,triplet);
	Fy = ecreate (m,n,triplet);
	Gx = ecreate (m,n,triplet);
	Gy = ecreate (m,n,triplet);
	Fx0 = ecreate (m,n,triplet);
	Fy0 = ecreate (m,n,triplet);
	Gx0 = ecreate (m,n,triplet);
	Gy0 = ecreate (m,n,triplet);

	jac_stor[0]=Fx; jac_stor[1]=Fy; jac_stor[2]=Gx; jac_stor[3]=Gy;
	jac_stor[4]=Fx0; jac_stor[5]=Fy0; jac_stor[6]=Gx0; jac_stor[7]=Gy0;
	return jac_stor;
}

/*frees original pointer and reassigns*/
int reassign_jac (cs** jac_stor, jac_name s, cs* A)
{
	if (!(A->nz == -1 && jac_stor[s]->nz == -1)) return 1;
	cs* temp = jac_stor[s];
	jac_stor[s] = A;
	cs_spfree(temp);
	return 0;
}

/*frees array of pointers to jacobian matrices*/
int free_jac (cs** jac_stor)
{
	int k;
	for (k=0;k<NUM_JAC;k++)
	{
		if (!(jac_stor[k])) return 1;
		cs_spfree (jac_stor[k]);
	}
	free (jac_stor);
	return 0;
}

/*returns jacobian matrix given jac_name*/
cs* acc_jac (cs** jac_stor, jac_name s)
{
	return jac_stor[s];
}


/*adds values to jacobian matrix*/
int add_jac (cs** jac_stor, jac_name s, int* r, int* c, double* v, int size)
{
	int diff = 0; /*assume not different shape at first*/
	cs* T;
	cs* A = acc_jac (jac_stor,s);
	if (A->nzmax == 0) {T = fcreate (r,c,v,size); reassign_jac (jac_stor,s,T); return 0; }
	cs* B = fcreate (r,c,v,size);
	T = add(A,B,&diff);
	if (diff) reassign_jac (jac_stor,s,T); /*if different shape discovered, realloc*/
	cs_spfree (B);
	return 0;
}

/*sets values of jacobian matrix*/
int set_jac (cs** jac_stor, jac_name s, int* r, int* c, double* v, int size)
{
	cs* T = fcreate (r,c,v,size);
	reassign_jac (jac_stor,s,T); /*we know it will definitely be different shape*/
	return 0;
}
