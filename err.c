#include "cs.h"
#include "mysparse.h"

/*check if index is within bounds of matrix*/

int errbound (const cs* A, int r, int c)
{
	int m,n;
	m = A->m; n = A->n;
	if (r>m-1 || c>n-1 || r<0 || c<0) return 1;
	return 0;
}
