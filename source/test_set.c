#include "mysparse.h"

/* testing function for set function runtime*/
/* by spars: operation = 0 to create no diff, 1 to set no diff matrix
			10 to create some diff, 11 to set some diff matrix */
/* by size: operation = 20 to create no diff, 21 to set no diff matrix
			30 to create some diff, 31 to set some diff matrix */
/* ./main <operation> <start size/spars> <end size/spars> <increment> <constant spars/size> */
int test_set(int a, double start, double end, double increment, double s)
{

int m=0,n=0; double spars=0, check=0; char confirm;

/*ERROR CHECKING*/
if ( (a!=0)&&(a!=1)&&(a!=10)&&(a!=11)&&(a!=20)&&(a!=21)&&(a!=30)&&(a!=31))
{
	printf ("ERROR: invalid operation %d\n",a); return -1;
}
if (a < 20)
{
	m = s; n = s;
	if ( (start>=1) || (end>=1) || (increment>=1) ) { printf ("ERROR: invalid param\n"); return -1; }
}
else
{
	spars = s;
	if ( (start<10) || (end>30000) || (increment<10) ) { printf ("ERROR: invalid param\n"); return -1; }
}

/*VARIABLES*/
	int seed1 = 2, seed2 = 3;
	int val1 = 1, val2 = 2;
	int repeat = 500; //how many trials
	double frac = 0.1; //what fraction of values to be set

	FILE *fp1, *fp2, *ft;
	clock_t t1 = clock();
	cs *T, *A = NULL, *B = NULL, *C = NULL;
	int j, k; bool *nd;
	double tsum1, sparsity, i;
	char *fname1 = NULL, *fname2 = NULL;
	
/*CALCULATE NEEDED MEMORY TO CREATE*/
if (!(a%10))
{
	for (double i=start; i<end+increment; i+=increment)
	{
		if (a==0) check += 16*i*(1+frac)*m*n/1000000;
		else if (a==10) check += 2*16*i*m*n/1000000;
		else if (a==20) check += 16*spars*(1+frac)*i*i/1000000;
		else if (a==30) check += 2*16*spars*i*i/1000000;
	}
	printf ("Will take about %.2f MB total. Continue? (y/n) ",check);
	if (scanf ("%c",&confirm)) {};
	if (confirm=='n') return 0;
}

/*GENERATE MATRIX FILES NO DIFF BY SPARSITY*/
if (a==0)
{
	printf ("ND_SET CREATE: matrix: %dx%d, seed: %d, sparse: %.3f to %.3f\n",m,n,seed1,start,end);
	for (i=start; i<end+increment; i+=increment)
		test_create (fname1,m,i,seed1,val1,fname2,i*frac,seed1,val2,1);
	return 0;
}

/*GENERATE MATRIX FILES SOME DIFF BY SPARSITY*/
if (a == 10)
{
	printf ("SD_SET CREATE: matrix: %dx%d, seed: %d, sparse: %.3f to %.3f\n",m,n,seed1,start,end);
	for (i=start; i<end+increment; i+=increment)
		test_create (fname1,m,i,seed1,val1,fname2,i,seed2,val2,1);
	return 0;
}

/*GENERATE MATRIX FILES NO DIFF BY SIZE*/
else if (a == 20)
{
	printf ("ND_SET CREATE: spars: %.3f, seed: %d, size: %.0f to %.0f\n",spars,seed1,start,end);
	for (i=start; i<end+increment; i+=increment)
		test_create (fname1,i,spars,seed1,val1,fname2,spars*frac,seed1,val2,1);
	return 0;
}

/*GENERATE MATRIX FILES SOME DIFF BY SIZE*/
else if (a == 30)
{
	printf ("SD_SET CREATE: spars: %.3f, seed: %d, size: %.0f to %.0f\n",spars,seed1,start,end);
	for (i=start; i<end+increment; i+=increment)
		test_create(fname1,i,spars,seed1,val1,fname2,spars,seed2,val2,1);
	return 0;
}

/*SETTING MATRICES NO DIFF INDEX BY SPARSITY*/
else if (a == 1)
{
	ft = fopen ("time_set.txt","a");
	fprintf (ft, "%drows%ffrac\nsparsity nd_set\n",m,frac);
	printf ("ND_SET TEST: matrix: %dx%d, seed: %d, trials: %d, sparse: %.3f to %.3f\n",m,n,seed1,repeat,start,end);

	for (i=start; i<end+increment; i+=increment)
	{
		fname1 = name (m,i,seed1,val1);
		fname2 = name (m,i*frac,seed1,val2);	
		if (!(fp1 = fopen (fname1, "r"))) { free_all (A,B,C,fname1,fname2,NULL,ft,1); return -1; }
		if (!(fp2 = fopen (fname2, "r"))) { free_all (A,B,C,fname2,fname1,fp1,ft,1); return -1; }

		T = cs_load (fp1); A = cs_compress (T); cs_spfree (T);
		T = cs_load (fp2); B = cs_compress (T); cs_spfree (T);

		fclose (fp1); fclose (fp2); free (fname1); free (fname2);
		tsum1=0;
		sparsity = (double)A->nzmax/(m*n);

		for (j=0; j<repeat; j++)
		{
			t1 = clock();
			nd = calloc (B->nzmax, sizeof(bool));
			if (!(diff_s(A,B,nd))) nd_set(A,B);
			free (nd);
			t1 = clock() - t1;
			tsum1 += ((double)t1)/CLOCKS_PER_SEC;
			for (k=0;k<A->nzmax;k++) A->x[k] = val1;
		}

		printf ("%f %f\n",sparsity,tsum1/repeat);
		fprintf (ft, "%f %f\n",sparsity,tsum1/repeat);
		cs_spfree (A); A = NULL;
		cs_spfree (B); B = NULL;
	}
	fclose (ft);
	return 0;
}


/*SETTING MATRICES SOME DIFF INDEX BY SPARSITY*/
else if (a == 11)
{
	ft = fopen ("time_set.txt","a");
	fprintf (ft, "%drows\nsparsity sd_set\n",m);
	printf ("SD_SET TEST: matrix: %dx%d, seed: %d, trials: %d, sparse: %.3f to %.3f\n",m,n,seed1,repeat,start,end);

	for (i=start; i<end+increment; i+=increment)
	{
		fname1 = name (m,i,seed1,val1);
		fname2 = name (m,i,seed2,val2);	
		if (!(fp1 = fopen (fname1, "r"))) { free_all (A,B,C,fname1,fname2,NULL,ft,1); return -1; }
		if (!(fp2 = fopen (fname2, "r"))) { free_all (A,B,C,fname2,fname1,fp1,ft,1); return -1; }

		T = cs_load (fp1); A = cs_compress (T); cs_spfree (T);
		T = cs_load (fp2); B = cs_compress (T); cs_spfree (T);

		fclose (fp1); fclose (fp2); free (fname1); free (fname2);
		tsum1=0;
		sparsity = (double)A->nzmax/(m*n);

		for (j=0; j<repeat; j++)
		{
			t1 = clock();
			nd = calloc (B->nzmax, sizeof(bool));
			if (diff_s(A,B,nd) == 2) C = sd_set(A,B,nd);
			free (nd);
			t1 = clock() - t1;
			tsum1 += ((double)t1)/CLOCKS_PER_SEC;
			cs_spfree (C); C = NULL;
		}

		printf ("%f %f\n",sparsity,tsum1/repeat);
		fprintf (ft, "%f %f\n",sparsity,tsum1/repeat);
		cs_spfree (A); A = NULL;
		cs_spfree (B); B = NULL;
	}
	fclose (ft);
	return 0;
}

/*SETTING MATRICES NO DIFF INDEX BY SIZE*/
else if (a == 21)
{
	ft = fopen ("time_set.txt","a");
	fprintf (ft, "%fspars %ffrac\nsize nd_set\n",spars,frac);
	printf ("ND_SET TEST: spars: %.3f, seed: %d, trials: %d, size: %.0f to %.0f\n",spars,seed1,repeat,start,end);

	for (i=start; i<end+increment; i+=increment)
	{
		fname1 = name (i,spars,seed1,val1);
		fname2 = name (i,spars*frac,seed1,val2);	
		if (!(fp1 = fopen (fname1, "r"))) { free_all (A,B,C,fname1,fname2,NULL,ft,1); return -1; }
		if (!(fp2 = fopen (fname2, "r"))) { free_all (A,B,C,fname2,fname1,fp1,ft,1); return -1; }

		T = cs_load (fp1); A = cs_compress (T); cs_spfree (T);
		T = cs_load (fp2); B = cs_compress (T); cs_spfree (T);

		fclose (fp1); fclose (fp2); free (fname1); free (fname2);
		tsum1=0;

		for (j=0; j<repeat; j++)
		{
			t1 = clock();
			nd = calloc (B->nzmax, sizeof(bool));
			if (!diff_s(A,B,nd)) nd_set(A,B);
			free (nd);
			t1 = clock() - t1;
			tsum1 += ((double)t1)/CLOCKS_PER_SEC;
			for (k=0;k<A->nzmax;k++) A->x[k] = val1;
		}

		printf ("%.0f %f\n",i,tsum1/repeat);
		fprintf (ft, "%.0f %f\n",i,tsum1/repeat);
		cs_spfree (A); A = NULL;
		cs_spfree (B); B = NULL;
	}
	fclose (ft);
	return 0;
}

/*SETTING MATRICES SOME DIFF INDEX BY SIZE*/
else if (a == 31)
{
	ft = fopen ("time_set.txt","a");
	fprintf (ft, "%fspars\nsize sd_set\n",spars);
	printf ("SD_SET TEST: spars: %.3f, seed: %d, trials: %d, size: %.0f to %.0f\n",spars,seed1,repeat,start,end);

	for (i=start; i<end+increment; i+=increment)
	{
		fname1 = name (i,spars,seed1,val1);
		fname2 = name (i,spars,seed2,val2);	
		if (!(fp1 = fopen (fname1, "r"))) { free_all (A,B,C,fname1,fname2,NULL,ft,1); return -1; }
		if (!(fp2 = fopen (fname2, "r"))) { free_all (A,B,C,fname2,fname1,fp1,ft,1); return -1; }

		T = cs_load (fp1); A = cs_compress (T); cs_spfree (T);
		T = cs_load (fp2); B = cs_compress (T); cs_spfree (T);

		fclose (fp1); fclose (fp2); free (fname1); free (fname2);
		tsum1=0;

		for (j=0; j<repeat; j++)
		{
			t1 = clock();
			nd = calloc (B->nzmax, sizeof(bool));
			if (diff_s(A,B,nd) == 2) C = sd_set(A,B,nd);
			free (nd);
			t1 = clock() - t1;
			tsum1 += ((double)t1)/CLOCKS_PER_SEC;
			cs_spfree (C); C = NULL;
		}

		printf ("%.0f %f\n",i,tsum1/repeat);
		fprintf (ft, "%.0f %f\n",i,tsum1/repeat);
		cs_spfree (A); A = NULL;
		cs_spfree (B); B = NULL;
	}
	fclose (ft);
	return 0;
}

return -1;

}


/*------------------------------------HELPER FUNCTIONS----------------------------------------------*/

/*create matrix file name (0 for add, 1 for set)*/
char* name (int rows, double sparsity, int seed, int val)
{
	char buffer_rows[10];
	char buffer_spars[10];
	char buffer_seed[10];
	char buffer_val[5];
	int len = sprintf (buffer_rows,"%05d",rows);
	len += sprintf (buffer_spars,"%.4f",sparsity);
	len += sprintf (buffer_seed,"%02d",seed);
	len += sprintf (buffer_val,"%01d",val);
	char* fname = malloc (len+25);
	strcpy (fname, "data/m_");
	strcat (fname, buffer_rows); strcat (fname, "_");
	strcat (fname, buffer_spars); strcat (fname, "_");
	strcat (fname, buffer_seed); strcat (fname, "_");
	strcat (fname, buffer_val); strcat (fname, ".txt");
	return fname;
}

/*freeing elements*/
void free_all (cs* A, cs* B, cs* C, char* fname_print, char* fname_other, FILE* fp, FILE* ft, bool bad)
{
	if (bad) printf ("ERROR: file %s does not exist\n",fname_print);
	if (A != NULL) cs_spfree (A);
	if (B != NULL) cs_spfree (B);
	if (C != NULL) cs_spfree (C);
	if (fp != NULL) fclose (fp);
	if (ft != NULL) fclose (ft);
	if (fname_print != NULL) free (fname_print);
	if (fname_other != NULL) free (fname_other);
}

/*creating matrices*/
void test_create (char* fname1, int m, double spars1, int seed1, int val1, char* fname2, double spars2, int seed2, int val2, int two)
{
	fname1 = name (m,spars1,seed1,val1);
	frandmat (fname1,m,m,spars1,seed1,val1);
	printf ("%s\n",fname1);
	free (fname1);
	if (two)
	{
		fname2 = name (m,spars2,seed2,val2);
		frandmat (fname2,m,m,spars2,seed2,val2);
		printf ("%s\n",fname2);
		free (fname2);
	}
}
