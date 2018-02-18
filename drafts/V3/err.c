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
	if (k==0) printf ("Success\n"); /*can comment out*/
	else if (k==1) printf ("Error %d: invalid value of zero passed (add, modify)\n",k);
	else if (k==2) printf ("Error %d: either existing value (add) or no value (modify, delete)\n",k);
	else if (k==3) printf ("Error %d: invalid row or column indices\n",k);
	else if (k==4) printf ("Error %d: invalid matrix\n",k);
	else printf ("Invalid error\n");
}

void errprint_jac (int k)
{
	if (k==0) printf ("Success\n"); /*can comment out*/
	else if (k==1) printf ("Error %d: either clear function failed (set) or jac matrices don't exist (free)\n",k);
	else if (k==2) printf ("Error %d: add function failed (set, add)\n",k);
	else if (k==3) printf ("Error %d: invalid row or column indice array (set, add)\n",k);
	else printf ("Invalid error\n");
}
