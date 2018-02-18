#include "cs.h"

/* x = x + beta * A(:,j), where x is a dense vector and A(:,j) is sparse */
CS_INT scattercs (const cs *A, CS_INT j, CS_ENTRY beta, CS_INT *w, CS_ENTRY *x, CS_INT mark,
    cs *C, CS_INT nz, int* count)
{
    CS_INT i, p, *Ap, *Ai, *Ci ;
    CS_ENTRY *Ax ;
    if (!CS_CSC (A) || !w || !CS_CSC (C)) return (-1) ;     /* check inputs */
    Ap = A->p ; Ai = A->i ; Ax = A->x ; Ci = C->i ;

    for (p = Ap [j] ; p < Ap [j+1] ; p++)
    {
	(*count)++;
        i = Ai [p] ;                            /* A(i,j) is nonzero */
        if (w [i] < mark)
        {
            w [i] = mark ;                      /* i is new entry in column j */
            Ci [nz++] = i ;                     /* add i to pattern of C(:,j) */
            if (x) x [i] = beta * Ax [p] ;      /* x(i) = beta*A(i,j) */
        }
        else if (x) x [i] += beta * Ax [p] ;    /* i exists in C(:,j) already */
    }
    return (nz) ;
}

/* C = alpha*A + beta*B */
cs *addcs (const cs *A, const cs *B, CS_ENTRY alpha, CS_ENTRY beta)
{
    CS_INT p, j, nz = 0, anz, *Cp, *Ci, *Bp, m, n, bnz, *w, values ;
    CS_ENTRY *x, *Bx, *Cx ;
    cs *C ;
	int count = 0;
	int *pcount = &count;
    if (!CS_CSC (A) || !CS_CSC (B)) return (NULL) ;         /* check inputs */
    if (A->m != B->m || A->n != B->n) return (NULL) ;
    m = A->m ; anz = A->p [A->n] ;
    n = B->n ; Bp = B->p ; Bx = B->x ; bnz = Bp [n] ;
    w = cs_calloc (m, sizeof (CS_INT)) ;                       /* get workspace */
    values = (A->x != NULL) && (Bx != NULL) ;
    x = values ? cs_malloc (m, sizeof (CS_ENTRY)) : NULL ;    /* get workspace */
    C = cs_spalloc (m, n, anz + bnz, values, 0) ;           /* allocate result*/
    if (!C || !w || (values && !x)) return (cs_done (C, w, x, 0)) ;
    Cp = C->p ; Ci = C->i ; Cx = C->x ;
    for (j = 0 ; j < n ; j++)
    {
        Cp [j] = nz ;                   /* column j of C starts here */

        nz = scattercs (A, j, alpha, w, x, j+1, C, nz,pcount) ;   /* alpha*A(:,j)*/
        nz = scattercs (B, j, beta, w, x, j+1, C, nz,pcount) ;    /* beta*B(:,j) */
        if (values)
	{
		for (p = Cp [j] ; p < nz ; p++)
		{
			Cx [p] = x [Ci [p]] ;
			count++;
		}
	}
    }
    Cp [n] = nz ;                       /* finalize the last column of C */
    cs_sprealloc (C, 0) ;               /* remove extra space from C */
printf ("loops = %d\n",count);
    return (cs_done (C, w, x, 1)) ;     /* success; free workspace, return C */
}

