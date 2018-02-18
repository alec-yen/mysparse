#include "mysparse.h"

/*adds csc matrix B to csc matrix A - requires allocations if new indices are added AKA different shapes*/
/*diff should be 0 when passed*/

cs* add(cs* A, cs* B, int *diff)
{
	cs* C;
	if (!diffshape (A,B)) { mod (A,B); return A; }
	else { C = cs_add (A,B,1,1); *diff = 1; return C; }
}

/*check if B fits inside A*/
int diffshape (cs *A, cs *B)
{
	int j,p,i,mark;
	int m = A->m;
	CS_INT *Ap, *Ai, *Bi, *Bp ;
	Ap = A->p ; Ai = A->i ; Bi = B->i; Bp = B->p;
	int* w = cs_calloc (m,sizeof(int)); //stores count of each column

	for (j=0;j<A->n;j++)
	{
		mark = j+1;
		for (p=Ap[j]; p<Ap[j+1]; p++)
		{
			i = Ai [p] ;                            
			if (w [i] < mark)
			{
				w [i] = mark ;
			}
		}
		for (p=Bp[j]; p<Bp[j+1]; p++)
		{
			i = Bi [p] ;                            
			if (w [i] < mark) //if true, different shape and return
			{
				free (w);
				return 1;
			}
		}
	}
	free (w);
	return 0;
}

/*given that csc B fits in csc A, add B elements to A*/
/*Example:
  1 0 2		7 0 10			8 0 12
  A = 	4 0 3	,  B = 	0 0 0  ,   => 	  A =	4 0 3
  0 5 6		0 9 12			0 14 18
 */
int mod (cs *A, cs *B)
{
	int j,p,i,mark;
	int m = A->m, nz=0;
	CS_INT *Ap, *Ai, *Bi, *Bp ;
	CS_ENTRY *Ax , *Bx;
	Ap = A->p ; Ai = A->i ; Ax = A->x ; Bi = B->i; Bp = B->p; Bx = B->x;
	int* w = cs_calloc (m,sizeof(int));
	double* x = cs_malloc (m,sizeof(double));

	for (j=0;j<A->n;j++)
	{
		mark = j+1;
		for (p=Ap[j]; p<Ap[j+1]; p++)
		{
			i = Ai [p] ;                            
			if (w [i] < mark)
			{
				w [i] = mark ;
				nz++;
				x[i] = 0;      
			}
		}
		for (p=Bp[j]; p<Bp[j+1]; p++)
		{
			i = Bi [p] ;
			if (w [i] < mark) //should never be true
			{
				printf ("ERROR\n");
				return 1;
			}
			x [i] += Bx [p] ;
		}
		for (p = Ap [j] ; p < nz ; p++)
		{

			Ax [p] += x [Ai [p]] ;
		}
	}
	free (w); free (x);
	return 0;
}



/*----------------------------------OLD VERSIONS---------------------------------------*/
/*doesn't have diff parameter*/
cs* add2(cs* A, cs* B)
{
	cs* C;
	if (!diffshape (A,B)) { mod (A,B); return A; }
	else { C = cs_add (A,B,1,1); cs_spfree(A); return C; }
}


/*checks if B fits inside A*/
int diffshape2 (cs* A, cs* B)
{
	int j,p,s,Bn,found;
	int *Ai, *Ap, *Bi, *Bp;
	Ai = A->i; Ap = A->p; Bn = B->n;
	Bi = B->i; Bp = B->p;
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


/*less efficient version of mod*/
int mod2 (cs *A, cs *B)
{
	int j,p,s,Bn;
	int *Ai, *Ap, *Bi, *Bp;
	double *Ax, *Bx;
	Ai = A->i; Ap = A->p; Ax = A->x; Bn = B->n;
	Bi = B->i; Bp = B->p; Bx = B->x;
	for (j=0;j<Bn;j++) /*loop through each column*/
	{
		for (p=Bp[j]; p<Bp[j+1]; p++) /*loop through B's row indices*/
		{
			for (s=Ap[j]; s<Ap[j+1]; s++) /*compare with A's row indices*/
			{
				if (Bi[p] == Ai[s])
				{
					Ax[s] += Bx[p]; /*add value if equal row index*/
					break;
				}
			}
		}
	}
	return 0; /*return 0 if successful*/
}
