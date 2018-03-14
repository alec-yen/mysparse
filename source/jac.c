#include "mysparse.h"

int NUM_JAC = 8;

/*returns filled compressed or triplet matrix*/
cs* create (int m, int n, int* i, int* j, double* x, int size, int trip)
{
	int k;
	cs* A = cs_spalloc (m,n,m*n,1,1);
	for (k=0;k<size;k++) cs_entry(A,i[k],j[k],x[k]);
	if (!trip)
	{
		cs* C = cs_compress (A);
		cs_spfree (A);
		return C;
	}
	else return A;
}

/*allocates array of pointers to jac structs*/
jac** alloc_jac (int m, int n)
{
	jac** jac_stor = malloc (NUM_JAC*sizeof(jac*));
	for (int i=0; i<NUM_JAC; i++)
	{
		jac_stor[i] = malloc (sizeof(jac));
		jac_stor[i]->jac_matrix = NULL;
		jac_stor[i]->m = m; //FIX ME: can be adjusted if Fx,Fy,etc. have different sizes
		jac_stor[i]->n = n;
	}
	return jac_stor;
}

/*frees array of pointers to jac structs*/
int free_jac (jac** jac_stor)
{
	for (int i=0;i<NUM_JAC;i++)
	{
		if (jac_stor[i]->jac_matrix!=NULL) cs_spfree (jac_stor[i]->jac_matrix);
		free (jac_stor[i]);
	}
	free (jac_stor);
	return 0;
}

/*frees original pointer A and reassigns jac_matrix*/
int reassign_jac (jac** jac_stor, jac_name s, cs* A)
{
	cs* temp = jac_stor[s]->jac_matrix;
	jac_stor[s]->jac_matrix = A;
	cs_spfree(temp);
	return 0;
}

/*returns jac_matrix given jac_name*/
cs* acc_jac (jac** jac_stor, jac_name s)
{
	printf ("accessing "); //FIX ME: printout for testing
	switch (s)
	{
		case Fx: printf ("Fx"); break;
		case Fy: printf ("Fy"); break;
		case Gx: printf ("Gx"); break;
		case Gy: printf ("Gy"); break;
		case Fx0: printf ("Fx0"); break;
		case Fy0: printf ("Fy0"); break;
		case Gx0: printf ("Gx0"); break;
		case Gy0: printf ("Gy0"); break;
	}
	printf ("\n");
	return jac_stor[s]->jac_matrix;
}


/*adds values to jac_matrix*/
int add_jac (jac** jac_stor, jac_name s, int* i, int* j, double* x, int size)
{
	int diff = 0; /*assume no diff index at first*/
	cs *C, *B, *A = acc_jac (jac_stor,s);
	B = create (jac_stor[s]->m,jac_stor[s]->n,i,j,x,size,0);

	if (A==NULL) reassign_jac (jac_stor,s,B);
	else
	{
		C = add (A,B,&diff);
		if (diff) reassign_jac (jac_stor,s,C); /*if diff index, reassign to T and free A*/
		cs_spfree (B);
	}
	return 0;
}

/*sets values of jac_matrix*/
int set_jac (jac** jac_stor, jac_name s, int* i, int* j, double* x, int size)
{
	int diff = 0; /*assume no diff index at first*/
	cs *C, *B, *A = acc_jac (jac_stor,s);
	B = create (jac_stor[s]->m,jac_stor[s]->n,i,j,x,size,0);

	if (A==NULL) reassign_jac (jac_stor,s,B);
	else
	{
		C = set (A,B,&diff);
		if (diff) reassign_jac (jac_stor,s,C); /*if diff index, reassign to T and free A*/
		cs_spfree (B);
	}
	return 0;
}
