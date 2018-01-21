#include "cs.h"
#include "mysparse.h"

/*sets element in compressed matrix - requires 2 allocations*/

void set(cs *A, int r, int c, double v)
{

	int index1,index2,k;
	int t,s; /*index*/
	int newmax = A->nzmax + 1;
	int ok = 1;   

	index1 = A->p[c]; /*index of Ci and Cx array to start iteration*/
	index2 = A->p[c+1];
	for (k = index1; k < index2; k++){
		if (A->i[k] > r){
			break;
		}
	}

	for (t=c+1; t<A->n+1; t++){ /*assume no change in Cp size with columns*/
		A->p[t]++;
	}
	A->i = cs_realloc (A->i,newmax,sizeof(CS_INT),&ok);
	A->x = cs_realloc (A->x,newmax,sizeof(CS_ENTRY),&ok);
	for (s=A->nzmax; s>k; s--){ /*shift values after index k to right*/
		A->i[s] = A->i[s-1];
		A->x[s] = A->x[s-1];
	}
	A->i[k] = r;
	A->x[k] = v;
	A->nzmax++;
	A->m = CS_MAX (A->m, r+1) ;
	A->n = CS_MAX (A->n, c+1) ;
}


/*less efficient version of set - requires 17 allocations*/

cs * add(cs *A, int r, int c, double v)
{
	cs *B, *BC, *C;
	int m, n;
	m = A->m; n = A->n;

	B = cs_spalloc (m,n,m*n,1,1);
	cs_entry(B,r,c,v);
	BC = cs_compress (B);
	cs_spfree (B);

	C = cs_add (A, BC, 1, 1);
	cs_spfree(A);	
	cs_spfree(BC);
	return C;
}
