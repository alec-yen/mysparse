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

/*check if m and n are positive*/

int errsize (int m, int n)
{
	if (m<0 || n<0) return 1;
	return 0;
}

/*check if passed arrays values are all positive
for indices array, stores number of rows/columns in max*/

int errarr (cs* A, int* r, int* c, int size)
{
	int k, rmax, cmax;
	rmax = r[0]; cmax = c[0];
	for (k=0;k<size;k++)
	{
		if (r[k] < 0 || c[k] < 0) return 1;
		if (r[k] > rmax) rmax = r[k];
		if (c[k] > cmax) cmax = c[k];
	}
	if (rmax+1 > A->m || cmax+1 > A->n) return 1;	
	return 0;
}

/*print error for one-at-a-time functions*/
void errprint_one (int k)
{
	if (k==0) printf ("Success\n");
	else if (k==1) printf ("Invalid value of zero passed\n");
	else if (k==2) printf ("Either existing value (add) or no value (modify/delete)\n");
	else if (k==3) printf ("Invalid row or column indices\n");
	else if (k==4) printf ("Invalid matrix\n");
	else printf ("Invalid error\n");
}

void errprint_jac (int k)
{
	if (k==0) printf ("Success\n");
	else if (k==1) printf ("No jacobian matrices to free\n");
	else if (k==2) printf ("Functions add or clear failed\n");
	else if (k==3) printf ("Invalid row or column indices\n");
	else printf ("Invalid error\n");
}
