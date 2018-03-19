#include "mysparse.h"
#include <stdio.h>
#include <time.h>
#include <string.h>

/*create matrix file name*/
char* sname (int rows, double sparsity, int seed, int val)
{
	char buffer_rows[10];
	char buffer_spars[10];
	char buffer_seed[10];
	char buffer_val[5];
	int len = sprintf (buffer_rows,"%05d",rows);
	len += sprintf (buffer_spars,"%.3f",sparsity);
	len += sprintf (buffer_seed,"%02d",seed);
	len += sprintf (buffer_val,"%01d",val);
	char* fname = malloc (len+25);
	strcpy (fname, "data/set_");
	strcat (fname, buffer_rows); strcat (fname, "_");
	strcat (fname, buffer_spars); strcat (fname, "_");
	strcat (fname, buffer_seed); strcat (fname, "_");
	strcat (fname, buffer_val); strcat (fname, ".txt");
	return fname;
}

/*freeing elements in test_set*/
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

/* testing function for set function runtime*/
/* by spars: operation = 0 to create no diff, 1 to set no diff matrix
			10 to create some diff, 11 to set some diff matrix */
/* by size: operation = 20 to create no diff, 21 to set no diff matrix
			30 to create some diff, 31 to set some diff matrix */
/* ./main <operation> <start size/spars> <end size/spars> <increment> <constant spars/size> */

int test_set(int a, double start, double end, double increment, double s)
{

int m=0,n=0;
double spars=0;
double check; char confirm;

if ( (a!=0)&&(a!=1)&&(a!=10)&&(a!=11) ) { printf ("ERROR: invalid operation %d\n",a); return -1; }

if ( (a==0) || (a==1) || (a==10) || (a==11) )
{
	m = s; n = s;
	if ( (start>=1) || (end>=1) || (increment>=1) ) { printf ("ERROR: invalid start/end/increment\n"); return -1; }

}
else if ( (a==20) || (a==21) || (a==30) || (a==31) )
{
	spars = s;
	if ( (start<10) || (end>25000) || (increment<10) ) { printf ("ERROR: invalid start/end/increment\n"); return -1; }
}

if ( (a==0) || (a==10) )
{
	check = 16*m*n*(start+end)*(1000*(end-start)+1)/1000000;
	printf ("Will take about %.2f MB total. Continue? (y/n) ",check);
	if (scanf ("%c",&confirm)) {};
	if (confirm=='n') return 0;
}
else if ( (a==20) || (a==30) )
{
	//check = WILL FIGURE OUT LATER
	printf ("Will take about %.2f MB total. Continue? (y/n) ",check);
	if (scanf ("%c",&confirm)) {};
	if (confirm=='n') return 0;
}

/*VARIABLES*/
	int seed1 = 2;
	int seed2 = 3;
	int val1 = 1;
	int val2 = 2;
	int repeat = 300;

	FILE *fp1, *fp2, *ft;
	cs *T, *A = NULL, *B = NULL; cs *C = NULL;
	int j, k;
	clock_t t1 = clock();
	double tsum1, sparsity, i;
	char *fname1, *fname2;
	bool *nd;

/*GENERATE MATRIX FILES NO DIFF BY SPARSITY*/
if (!a)
{
	printf ("ND_SET CREATE: matrix: %dx%d, seed: %d, sparse: %.3f to %.3f\n",m,n,seed1,start,end);
	for (i=start; i<end+increment; i+=increment)
	{
		fname1 = sname (m,i,seed1,val1);
		frandmat (fname1,m,n,i,seed1,val1);
		printf ("%s\n",fname1);
		free (fname1);
		fname2 = sname (m,i,seed1,val2);
		frandmat (fname2,m,n,i,seed1,val2);
		printf ("%s\n",fname2);
		free (fname2);
	}
	return 0;
}

/*SETTING MATRICES NO DIFF INDEX BY SPARSITY*/
else if (a == 1)
{
	ft = fopen ("time_set.txt","a");
	fprintf (ft, "%d\nsparsity nd_set\n",m);
	printf ("ND_SET TEST: matrix: %dx%d, seed: %d, trials: %d, sparse: %.3f to %.3f\n",m,n,seed1,repeat,start,end);

	for (i=start; i<end+increment; i+=increment)
	{
		fname1 = sname (m,i,seed1,val1);
		fname2 = sname (m,i,seed1,val2);	
		if (!(fp1 = fopen (fname1, "r"))) { free_all (A,B,NULL,fname1,fname2,NULL,ft,1); return -1; }
		if (!(fp2 = fopen (fname2, "r"))) { free_all (A,B,NULL,fname2,fname1,fp1,ft,1); return -1; }

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
			for (k=0;k<A->nzmax;k++) A->x[k] = 1;
		}

		printf ("%f %f\n",sparsity,tsum1/repeat);
		fprintf (ft, "%f %f\n",sparsity,tsum1/repeat);
		if (A != NULL) { cs_spfree (A); A = NULL; }
		if (B != NULL) { cs_spfree (B); B = NULL; }
	}
	fclose (ft);
	return 0;
}

/*GENERATE MATRIX FILES SOME DIFF BY SPARSITY*/
if (a == 10)
{
	printf ("SD_SET CREATE: matrix: %dx%d, seed: %d, sparse: %.3f to %.3f\n",m,n,seed1,start,end);
	for (i=start; i<end+increment; i+=increment)
	{
		fname1 = sname (m,i,seed1,val1);
		frandmat (fname1,m,n,i,seed1,val1);
		printf ("%s\n",fname1);
		free (fname1);
		fname2 = sname (m,i,seed2,val2);
		frandmat (fname2,m,n,i,seed2,val2);
		printf ("%s\n",fname2);
		free (fname2);
	}
	return 0;
}

/*SETTING MATRICES SOME DIFF INDEX BY SPARSITY*/
else if (a == 11)
{
	ft = fopen ("time_set.txt","a");
	fprintf (ft, "%d\nsparsity sd_set\n",m);
	printf ("SD_SET TEST: matrix: %dx%d, seed: %d, trials: %d, sparse: %.3f to %.3f\n",m,n,seed1,repeat,start,end);

	for (i=start; i<end+increment; i+=increment)
	{
		fname1 = sname (m,i,seed1,val1);
		fname2 = sname (m,i,seed2,val2);	
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
		if (A != NULL) { cs_spfree (A); A = NULL; }
		if (B != NULL) { cs_spfree (B); B = NULL; }
		if (C != NULL) { cs_spfree (C); C = NULL; }
	}
	fclose (ft);
	return 0;
}

return -1;

}
