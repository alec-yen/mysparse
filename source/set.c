#include "mysparse.h"
#include <stdbool.h>

/*set one element*/
int set_one (cs * A, int i, int j, double v)
{
	int p;
	for (p = A->p[j] ; p < A->p[j+1] ; p++)
	{
		if (i == A->i[p]) { A->x[p] = v; return 1; }
	}
	return 0;
}

/*returns 0 if no diff indices, 1 if all diff, 2 if some diff*/
int diff_s (cs* A, cs* B, bool* nd)
{
	int j,p,i,mark,k=0;
	int flag=-1;
	CS_INT *Ap, *Ai, *Bi, *Bp ;

	Ap = A->p ; Ai = A->i ; Bi = B->i; Bp = B->p;
	int* w = cs_calloc (A->m,sizeof(int)); //stores count of each column

	for (j=0;j<A->n;j++)
	{
		mark = j+1;
		for (p=Ap[j]; p<Ap[j+1]; p++)
		{
			i = Ai [p] ;                            
			if (w [i] < mark) w [i] = mark ;
		}
		for (p=Bp[j]; p<Bp[j+1]; p++)
		{
			i = Bi [p] ;
			if (w [i] < mark) //diff index
			{
				if (!flag) flag = 2; //some diff indices
				else if (flag == -1) flag = 1;
			}
			else //existing index
			{
				if (flag==1) flag = 2; //some diff indices
				else if (flag == -1) flag = 0;
				nd[k] = 1;
			}
			k++;
		}
	}
	free (w);
	return flag;
}


/*if no diff index, set each value one by one*/
int nd_set (cs* A, cs* B)
{
	int p,j;
	for (j=0 ; j<B->n ; j++)
	{
		for (p = B->p[j] ; p < B->p[j+1] ; p++)
		{
			set_one (A,B->i[p],j,B->x[p]);
		}
	}
	return 0;
}

/*if some diff index, set not diff index to 0 and cs_add*/
cs* sd_set (cs* A, cs* B, bool* nd)
{
	int p,j,k=0;
	cs * C;
	for (j=0 ; j<B->n ; j++)
	{
		for (p = B->p[j] ; p < B->p[j+1] ; p++)
		{
			if (nd[k]) set_one (A,B->i[p],j,0);
			k++;
		}
	}
	C = cs_add (A,B,1,1);
	return C;
}

/*set values in csc matrix A to values in csc matrix B - requires allocations if all/some diff index*/
/*flag should be 0 when passed*/
cs* set (cs* A, cs* B, int* flag)
{
	cs * C = NULL;
	bool* nd = calloc (B->nzmax, sizeof(bool));
	int f = diff_s (A,B,nd);
	if (!f)
	{
		nd_set (A,B);
		free (nd);
		return A;
	}
	else if (f == 1) C = cs_add (A,B,1,1);
	else if (f == 2) C = sd_set (A,B,nd);
	free (nd); *flag = 1;
	return C;
}

/*doesn't have flag parameter and frees A (for testing purposes)*/
cs* set2 (cs* A, cs* B)
{
	cs * C = NULL;
	bool* nd = calloc (B->nzmax, sizeof(bool));
	int f = diff_s (A,B,nd);
	if (!f)
	{
		printf ("no diff index\n");
		nd_set (A,B);
		free (nd);
		return A;
	}
	else if (f == 1)
	{
		printf ("all diff index\n");
		C = cs_add (A,B,1,1);
	}
	else if (f == 2)
	{
		printf ("some diff index\n");
		C = sd_set (A,B,nd);
	}
	cs_spfree (A); free (nd);
	return C;
}
