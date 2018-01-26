#include "cs.h"
#include "mysparse.h"

/*sets element in compressed matrix - requires 2 allocations*/

int set(cs *A, int r, int c, double v)
{
	if (errbound(A,r,c)) return 2; /*return 2 if out of bounds*/
	if (acc(A,r,c)) return 1; /*return 1 if existing value*/
	if (A->nz == -1){
		int cp1,cp2,k,t; /*index*/
		int newmax = A->nzmax + 1;
		int ok = 1;

		cp1 = A->p[c]; /*index of Ci and Cx array to start iteration*/
		cp2 = A->p[c+1];
		for (k = cp1; k < cp2; k++){
			if (A->i[k] > r){
				break;
			}
		}

		for (t=c+1; t<A->n+1; t++){ /*assume no change in Cp size with columns*/
			A->p[t]++;
		}
		A->i = cs_realloc (A->i,newmax,sizeof(CS_INT),&ok);
		A->x = cs_realloc (A->x,newmax,sizeof(CS_ENTRY),&ok);
		for (t=A->nzmax; t>k; t--){ /*shift values after index k to right*/
			A->i[t] = A->i[t-1];
			A->x[t] = A->x[t-1];
		}
		A->i[k] = r;
		A->x[k] = v;
		A->nzmax++;
		A->m = CS_MAX (A->m, r+1) ;
		A->n = CS_MAX (A->n, c+1) ;
		return 0; /*return 0 if success*/
	}
	else if (A->nz >= 0){
		cs_entry(A,r,c,v);
		return 0;
	}
	else return 3; /*return 3 if invalid*/
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
