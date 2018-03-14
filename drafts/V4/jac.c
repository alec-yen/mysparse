#include "mysparse.h"

int NUM_JAC = 8;

/*allocates array of pointers to jacobian csc matrices*/
cs** alloc_jac (int m, int n)
{
	cs* Fx,*Fy,*Gx,*Gy,*Fx0,*Fy0,*Gx0,*Gy0;
	cs** jac_stor = malloc (NUM_JAC*sizeof(cs*));
	Fx = ecreate (m,n,0);
	Fy = ecreate (m,n,0);
	Gx = ecreate (m,n,0);
	Gy = ecreate (m,n,0);
	Fx0 = ecreate (m,n,0);
	Fy0 = ecreate (m,n,0);
	Gx0 = ecreate (m,n,0);
	Gy0 = ecreate (m,n,0);

	jac_stor[0]=Fx; jac_stor[1]=Fy; jac_stor[2]=Gx; jac_stor[3]=Gy;
	jac_stor[4]=Fx0; jac_stor[5]=Fy0; jac_stor[6]=Gx0; jac_stor[7]=Gy0;

	return jac_stor;
}

/*frees original pointer A and reassigns jac_stor[s]*/
int reassign_jac (cs** jac_stor, jac_name s, cs* A)
{
	cs* temp = jac_stor[s];
	jac_stor[s] = A;
	cs_spfree(temp);
	return 0;
}

/*frees array of pointers to jacobian matrices*/
int free_jac (cs** jac_stor)
{
	for (int k=0;k<NUM_JAC;k++) { if (jac_stor[k]!=NULL) cs_spfree (jac_stor[k]); }
	free (jac_stor);
	return 0;
}

/*returns jacobian matrix given jac_name*/
cs* acc_jac (cs** jac_stor, jac_name s)
{
	return jac_stor[s];
}


/*adds values to jacobian matrix*/
int add_jac (cs** jac_stor, jac_name s, int* i, int* j, double* x, int size)
{
	int diff = 0; /*assume no diff index at first*/
	cs *C, *B, *A = acc_jac (jac_stor,s);
	B = fcreate (A->m,A->n,i,j,x,size,0);

	if (!A->nzmax) reassign_jac (jac_stor,s,B);
	else
	{
		C = add (A,B,&diff);
		if (diff) reassign_jac (jac_stor,s,C); /*if diff index, reassign to T and free A*/
		cs_spfree (B);
	}
	return 0;
}

/*sets values of jacobian matrix*/
int set_jac (cs** jac_stor, jac_name s, int* i, int* j, double* x, int size)
{
	int diff = 0; /*assume no diff index at first*/
	cs *C, *B, *A = acc_jac (jac_stor,s);
	B = fcreate (A->m,A->n,i,j,x,size,0);

	if (!A->nzmax) reassign_jac (jac_stor,s,B);
	else
	{
		C = set (A,B,&diff);
		if (diff) reassign_jac (jac_stor,s,C); /*if diff index, reassign to T and free A*/
		cs_spfree (B);
	}
	return 0;
}
