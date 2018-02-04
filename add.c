#include "cs.h"
#include "mysparse.h"


/*adds matrix B to matrix A - requires allocations if new indices are added*/

cs* add(cs* A, cs* B)
{
	cs* C;
	if (!errshape (A,B)) { mod (A,B); return A; }
	else { C = cs_add (A,B,1,1); return C; }
}


/*check if B fits within shape of A*/

int errshape (cs* A, cs* B)
{
	int j,p,s,Bn,found;
	int *Ai, *Ap, *Bi, *Bp;
	double *Ax, *Bx;
	Ai = A->i; Ap = A->p; Ax = A->x; Bn = B->n;
	Bi = B->i; Bp = B->p; Bx = B->x;
	for (j=0;j<Bn;j++) /*loop through each column*/
	{
		for (p=Bp[j]; p<Bp[j+1]; p++) /*loop through B's row indices*/
		{
			found = 0;
			for (s=Ap[j]; s<Ap[j+1]; s++) /*compare with A's row indices*/
			{
				if (Bi[p] == Ai[s])
				{
					found = 1;
					break;
				}
			}
			if (!found ) return 1; /*return 1 if B does not fit in A*/
		}
	}
	return 0; /*return 0 if B fits in A*/
}

/*given that csc B has same shape as csc A, add B elements to A*/
/*Example:
	1 0 2		7 0 10			8 0 12
  A = 	4 0 3	,  B = 	0 0 0  ,   => 	  A =	4 0 3
	0 5 6		0 9 12			0 14 18
*/


int mod (cs *A, cs *B)
{
	int j,p,s,Bn;
	int *Ai, *Ap, *Bi, *Bp;
	double *Ax, *Bx;
	Ai = A->i; Ap = A->p; Ax = A->x; Bn = B->n;
	Bi = B->i; Bp = B->p; Bx = B->x;
	int count = 0;
	for (j=0;j<Bn;j++) /*loop through each column*/
	{
		for (p=Bp[j]; p<Bp[j+1]; p++) /*loop through B's row indices*/
		{
			for (s=Ap[j]; s<Ap[j+1]; s++) /*compare with A's row indices*/
			{
				count++;
				if (Bi[p] == Ai[s])
				{
					Ax[s] += Bx[p]; /*add value if equal row index*/
					break;
				}
			}
		}
	}
	printf ("checked %d spots\n",count);
	return 0; /*return 0 if successful*/
}

/*less efficient version of mod*/

int mod2 (cs *A, cs *B)
{
	int j,p,s,Bn,Bpmax;
	int *Ai, *Ap, *Bi, *Bp;
	double *Ax, *Bx;
	Ai = A->i; Ap = A->p; Ax = A->x; Bn = B->n;
	Bi = B->i; Bp = B->p; Bx = B->x;
	int count = 0;
	for (j=0;j<Bn;j++) /*loop through each column*/
	{
		Bpmax = Bp[j+1];
		for (p=Ap[j]; p<Ap[j+1]; p++) /*loop through A's row indices*/
		{
			if (Ai[p] > Bi[Bpmax-1]) break; /*break if A row index is already higher than B's highest*/
			for (s=Bp[j]; s<Bpmax; s++) /*compare with B's row indices*/
			{
				count++;
				if (Ai[p] == Bi[s])
				{
					Ax[p] += Bx[s]; /*add value if equal row index*/
					break;
				}
			}
		}
	}
	printf ("checked %d spots\n",count);
	return 0; /*return 0 if successful*/
}
