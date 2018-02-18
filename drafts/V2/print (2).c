#include "cs.h"

/*print a compressed matrix*/

int print (const cs *A)
{
    printf ("\n");
    int p, j, m, n, nzmax, nz, *Ap, *Ai ;
    double *Ax ;
    if (!A) { printf ("(null)\n") ; return (0) ; }
    m = A->m ; n = A->n ; Ap = A->p ; Ai = A->i ; Ax = A->x ;
    nzmax = A->nzmax ; nz = A->nz ;
    printf ("Compressed Matrix %g-by-%g, nzmax: %g\n", (double) m, (double) n, (double) nzmax);
    if (nz < 0)
    {
        for (j = 0 ; j < n ; j++)
        {
            printf ("    col %g : locations %g to %g\n", (double) j, (double) (Ap [j]), (double) (Ap [j+1]-1));
            for (p = Ap [j] ; p < Ap [j+1] ; p++)
            {
                printf ("      %g : ", (double) (Ai [p])) ;
                printf ("%g\n", Ax ? Ax [p] : 1) ;
            }
        }
    }
    printf ("\n");
    return 1;
}
