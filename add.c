#include "mysparse.h"

/*adds csc matrix B to csc matrix A - requires allocations if different indices*/
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
				free (w); free (x);
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

