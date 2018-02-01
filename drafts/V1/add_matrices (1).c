#include "cs.h"

/* C = alpha*A + beta*B */
cs *cs_add (const cs *A, const cs *B, CS_ENTRY alpha, CS_ENTRY beta)
{
    CS_INT p, j, nz = 0, anz, *Cp, *Ci, *Bp, m, n, bnz, *w, values ;
    CS_ENTRY *x, *Bx, *Cx ;
    cs *C ;
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
        nz = cs_scatter (A, j, alpha, w, x, j+1, C, nz) ;   /* alpha*A(:,j)*/
        nz = cs_scatter (B, j, beta, w, x, j+1, C, nz) ;    /* beta*B(:,j) */
        if (values) for (p = Cp [j] ; p < nz ; p++) Cx [p] = x [Ci [p]] ;
    }
    Cp [n] = nz ;                       /* finalize the last column of C */
    cs_sprealloc (C, 0) ;               /* remove extra space from C */
    return (cs_done (C, w, x, 1)) ;     /* success; free workspace, return C */
}

int main(int argc, char* argv[]){
	FILE * fp1;
	FILE * fp2;
	cs *A, *B, *AC, *BC, *C;
	if (argc != 6){
		printf ("Not enough arguments\n");
		return 1;
	}
	fp1 = fopen( argv[1] , "r" );
	fp2 = fopen( argv[2] , "r" );
	CS_INT i = atoi (argv[3]);
	CS_INT j = atoi (argv[4]);
	CS_ENTRY x = atof (argv[5]);


	A = cs_load(fp1);
	B = cs_load(fp2);
	AC = cs_compress (A);
	cs_entry(B,i,j,x);
	BC = cs_compress (B);


	C = cs_add (AC, BC, 1, 1);
	cs_print(C, 0);

	cs_spfree(A);
	cs_spfree(B);
	cs_spfree(AC);
	cs_spfree(BC);
	cs_spfree(C);

	return 0;
}
