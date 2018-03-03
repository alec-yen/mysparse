#include "mysparse.h"

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

/*if no diff index, set each value one by one*/
int nd_set (cs * A, cs * B)
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
cs* sd_set (cs * A, cs * B)
{
	int p,j; cs * C;
	for (j=0 ; j<B->n ; j++)
	{
		for (p = B->p[j] ; p < B->p[j+1] ; p++)
		{
			set_one (A,B->i[p],j,0);
		}
	}
	C = cs_add (A,B,1,1);
	return C;
}

/*set values in csc matrix A to values in csc matrix B - requires allocations if all/some diff index*/
/*flag should be 0 when passed*/
cs* set (cs * A, cs * B, int *flag)
{
	cs * C = NULL;
	int f = diff (A,B);
	if (!f)
	{
		nd_set (A,B);
		return A;
	}
	else if (f == 1) C = cs_add (A,B,1,1);
	else if (f == 2) C = sd_set (A,B);
	*flag = 1;
	cs_spfree (A);
	return C;
}

/*doesn't have flag parameter*/
cs* set2 (cs * A, cs * B)
{
	cs * C = NULL;
	int f = diff (A,B);
	if (!f)
	{
		nd_set (A,B);
		return A;
	}
	else if (f == 1) C = cs_add (A,B,1,1);
	else if (f == 2) C = sd_set (A,B);
	cs_spfree (A);
	return C;
}
