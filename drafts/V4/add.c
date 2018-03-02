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
int mod3 (cs *A, cs *B)
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
