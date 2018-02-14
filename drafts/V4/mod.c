/*less efficient version of mod*/
int mod2 (cs *A, cs *B)
{
	int j,p,s,Bn,Bpmax;
	int *Ai, *Ap, *Bi, *Bp;
	double *Ax, *Bx;
	Ai = A->i; Ap = A->p; Ax = A->x; Bn = B->n;
	Bi = B->i; Bp = B->p; Bx = B->x;
	for (j=0;j<Bn;j++) /*loop through each column*/
	{
		Bpmax = Bp[j+1];
		for (p=Ap[j]; p<Ap[j+1]; p++) /*loop through A's row indices*/
		{
			if (Ai[p] > Bi[Bpmax-1]) break; /*break if A row index is already higher than B's highest*/
			for (s=Bp[j]; s<Bpmax; s++) /*compare with B's row indices*/
			{
				if (Ai[p] == Bi[s])
				{
					Ax[p] += Bx[s]; /*add value if equal row index*/
					break;
				}
			}
		}
	}
	return 0; /*return 0 if successful*/
}
