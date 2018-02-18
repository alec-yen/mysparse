#include "cs.h"
#include "mysparse.h"

/*adds triplet to compressed matrix
adds element to A and returns C*/

cs * add(cs *A, int r, int c, double v)
{
	char* name2 = "m_added.txt";
	cs *B, *C; /*B is compressed matrix that will be added*/
	int m, n;
	m = A->m; n = A->n;

	B = ccreate_empty (name2,m,n,1,r,c,v); /*create matrix with added element*/
	C = cs_add (A, B, 1, 1);
	cs_spfree(A);	
	cs_spfree(B);
	return C;
}
