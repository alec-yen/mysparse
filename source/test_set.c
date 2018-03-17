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
	strcat (fname, buffer_seed); strcat (fname, "_");
	strcat (fname, buffer_spars); strcat (fname, "_");
	strcat (fname, buffer_val); strcat (fname, ".txt");
	return fname;
}

/* testing function for set.c runtime*/
/* by size: operation = 0 to create no diff, 1 to set no diff matrix
			10 to create some diff, 11 to set some diff matrix */
/* ./main <operation> <start size/spars> <end size/spars> <increment> <constant spars/size> */

int test_set(int a, double start, double end, double increment, double s)
{

int m=0,n=0;
double spars=0;

if ( (a!=0)&&(a!=1)&&(a!=10)&&(a!=11) ) { printf ("ERROR: invalid operation %d\n",a); return -1; }

if ( (a==0) || (a==1) || (a==10) || (a==11) )
{
	m = s;
	n = s;
	if ( (start>=1) || (end>=1) || (increment>=1) )
	{ printf ("ERROR: invalid start/end/increment\n"); return -1; }
}
if ( (a==20) || (a==21) )
{
	spars = s;
	if ( (start<10) || (end>25000) || (increment<10) )
	{ printf ("ERROR: invalid start/end/increment\n"); return -1; }
}

int seed1 = 2;
int seed2 = 3;
int val1 = 1;
int val2 = 2;
int repeat = 100; //CHANGE ME

/*GENERATE MATRIX FILES NO DIFF BY SPARSITY*/
if (!a)
{
	double i;
	char* fname;
	printf ("ND_SET CREATE: matrix: %dx%d, seed: %d, sparse: %.3f to %.3f\n",m,n,seed1,start,end);
	for (i=start; i<end+increment; i+=increment)
	{
		fname = sname (m,i,seed1,val1);
		frandmat (fname,m,n,i,seed1,val1);
		printf ("%s\n",fname);
		free (fname);
		fname = sname (m,i,seed1,val2);
		frandmat (fname,m,n,i,seed1,val2);
		printf ("%s\n",fname);
		free (fname);
	}
	return 0;
}

/*GENERATE MATRIX FILES SOME DIFF BY SPARSITY*/
if (a == 10)
{
	double i;
	char* fname;
	printf ("SD_SET CREATE: matrix: %dx%d, seed: %d, sparse: %.3f to %.3f\n",m,n,seed1,start,end);
	for (i=start; i<end+increment; i+=increment)
	{
		fname = sname (m,i,seed1,val1);
		frandmat (fname,m,n,i,seed1,val1);
		printf ("%s\n",fname);
		free (fname);
		fname = sname (m,i,seed2,val2);
		frandmat (fname,m,n,i,seed2,val2);
		printf ("%s\n",fname);
		free (fname);
	}
	return 0;
}


/*SETTING MATRICES NO DIFF INDEX BY SPARSITY*/
else if (a == 1)
{
	FILE *fp1, *fp2, *ft;
	cs *T, *A = NULL, *B = NULL;
	int j,k;
	clock_t t1 = clock();
	double ttaken1, tsum1, sparsity, i;
	char *fname1, *fname2;
	bool *nd;

	ft = fopen ("time_set.txt","a");
	fprintf (ft, "%d\nsparsity nd_set\n",m);
	printf ("ND_SET TEST: matrix: %dx%d, seed: %d, trials: %d, sparse: %.3f to %.3f\n",m,n,seed1,repeat,start,end);

	for (i=start; i<end+increment; i+=increment)
	{
		fname1 = sname (m,i,seed1,val1);
		fname2 = sname (m,i,seed1,val2);	
		if (!(fp1 = fopen (fname1, "r")))
		{
			printf ("ERROR: file %s does not exist\n",fname1);
			if (A != NULL) cs_spfree (A);
			if (B != NULL) cs_spfree (B);
			fclose (fp1);
			free (fname1); free (fname2);
			return -1;
		}
		if (!(fp2 = fopen (fname2, "r")))
		{
			printf ("ERROR: file %s does not exist\n",fname2);
			if (A != NULL) cs_spfree (A);
			if (B != NULL) cs_spfree (B);
			fclose (fp2);
			free (fname1); free (fname2);
			return -1;
		}


		T = cs_load (fp1);
		A = cs_compress (T); cs_spfree (T);
		T = cs_load (fp2);
		B = cs_compress (T); cs_spfree (T);
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
			ttaken1 = ((double)t1)/CLOCKS_PER_SEC;
			tsum1 += ttaken1;
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


/*SETTING MATRICES SOME DIFF INDEX BY SPARSITY*/
else if (a == 11)
{
	FILE *fp1, *fp2, *ft;
	cs *T, *A = NULL, *B = NULL; cs *C = NULL;
	int j;
	clock_t t1 = clock();
	double ttaken1, tsum1, sparsity, i;
	char *fname1, *fname2;
	bool *nd;

	ft = fopen ("time_set.txt","a");
	fprintf (ft, "%d\nsparsity nd_set\n",m);
	printf ("SD_SET TEST: matrix: %dx%d, seed: %d, trials: %d, sparse: %.3f to %.3f\n",m,n,seed1,repeat,start,end);

	for (i=start; i<end+increment; i+=increment)
	{
		fname1 = sname (m,i,seed1,val1);
		fname2 = sname (m,i,seed2,val2);	
		if (!(fp1 = fopen (fname1, "r")))
		{
			printf ("ERROR: file %s does not exist\n",fname1);
			if (A != NULL) cs_spfree (A);
			if (B != NULL) cs_spfree (B);
			if (C != NULL) cs_spfree (C);
			fclose (fp1);
			free (fname1); free (fname2);
			return -1;
		}
		if (!(fp2 = fopen (fname2, "r")))
		{
			printf ("ERROR: file %s does not exist\n",fname2);
			if (A != NULL) cs_spfree (A);
			if (B != NULL) cs_spfree (B);
			if (C != NULL) cs_spfree (C);
			fclose (fp2);
			free (fname1); free (fname2);
			return -1;
		}


		T = cs_load (fp1);
		A = cs_compress (T); cs_spfree (T);
		T = cs_load (fp2);
		B = cs_compress (T); cs_spfree (T);
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
			ttaken1 = ((double)t1)/CLOCKS_PER_SEC;
			tsum1 += ttaken1;
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
