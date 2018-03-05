#include "mysparse.h"
#include <stdio.h>
#include <time.h>
#include <string.h>

/*create random matrix file name*/
char* name (int rows, double sparsity, int seed)
{
	char buffer_rows[10];
	char buffer_spars[10];
	char buffer_seed[10];
	int len = sprintf (buffer_rows,"%05d",rows);
	len += sprintf (buffer_spars,"%.3f",sparsity);
	len += sprintf (buffer_seed,"%02d",seed);
	char* fname = malloc (len+15);
	strcpy (fname, "data/m");
	strcat (fname, buffer_rows); strcat (fname, "_");
	strcat (fname, buffer_seed); strcat (fname, "_");
	strcat (fname, buffer_spars); strcat (fname, ".txt");
	return fname;
}


/* operation = 0 to create, 1 to add same matrix, 2 to add diff matrix */
/* ./main <operation> <start size/spars> <end size/spars> <increment> <constant spars/size> */

int test(int a, double start, double end, double increment, double s)
{

int m=0,n=0;
double spars=0;

if ( (a!=0)&&(a!=1)&&(a!=2)&&(a!=10)&&(a!=11) ) { printf ("ERROR: invalid operation %d\n",a); return -1; }

if ( (a==0) || (a==1) || (a==2) )
{
	m = s;
	n = s;
	if ( (start>=1) || (end>=1) || (increment>=1) )
	{ printf ("ERROR: invalid start/end/increment\n"); return -1; }
}
if ( (a==10) || (a==11) )
{
	spars = s;
	if ( (start<10) || (end>25000) || (increment<10) )
	{ printf ("ERROR: invalid start/end/increment\n"); return -1; }
}

int seed = 2;
int seed2 = 3;
int repeat = 300; //CHANGE ME





/*GENERATE MATRIX FILES BY SIZE*/
if (a==10)
{
	double i;
	char* fname;
	printf ("CREATE: spars: %.3f, seed: %d, size: %.0f to %.0f\n",spars,seed,start,end);
	for (i=start; i<end+increment; i+=increment)
	{
		fname = name (i,spars,seed);
		frandmat (fname,i,i,spars,seed);
		printf ("%s\n",fname);
		free (fname);
	}
	return 0;
}

/*ADDING MATRICES NO DIFF INDEX BY SIZE*/
else if (a==11)
{
	FILE *fp, *ft;
	cs *T, *A = NULL, *B = NULL;
	int j,k;
	clock_t t1 = clock(), t2 = clock();
	double ttaken1, ttaken2, tsum1, tsum2, i;
	char* fname;

	ft = fopen ("time.txt","a");
	fprintf (ft, "\nTEST: spars: %.3f, seed: %d, trials: %d, size: %.0f to %.0f\n",spars,seed,repeat,start,end);
	printf ("TEST: spars: %.3f, seed: %d, size: %.0f to %.0f\n",spars,seed,start,end);

	for (i=start; i<end+increment; i+=increment)
	{
		fname = name (i,spars,seed);
		if ((fp = fopen (fname, "r")))
		{
			T = cs_load (fp);
			A = cs_compress (T);
			cs_spfree (T); fclose (fp); free (fname);
			tsum1=0; tsum2=0;

			for (j=0; j<repeat; j++)
			{
				t2 = clock();
				B = cs_add (A,A,1,1);
				t2 = clock() - t2;
				t1 = clock();
				if (!(a_diff(A,A))) nd_add(A,A);
				t1 = clock() - t1;
				ttaken1 = ((double)t1)/CLOCKS_PER_SEC;
				ttaken2 = ((double)t2)/CLOCKS_PER_SEC;
				tsum1 += ttaken1; tsum2 += ttaken2;

				for (k=0;k<A->nzmax;k++) A->x[k] = 1;
				cs_spfree (B); B = NULL;
			}

			printf ("%5.0f %f %f\n",i,tsum1/repeat, tsum2/repeat);
			fprintf (ft, "%.0f %f %f\n",i,tsum1/repeat, tsum2/repeat);
			if (A != NULL) { cs_spfree (A); A = NULL; }
			if (B != NULL) { cs_spfree (B); B = NULL; }
		}
		else
		{
			printf ("ERROR: file %s does not exist\n",fname);
			if (A != NULL) cs_spfree (A);
			if (B != NULL) cs_spfree (B);
			fclose (ft);
			free (fname);
			return -1;	
		}
	}
	fclose (ft);
	return 0;	
}


/*GENERATE MATRIX FILES BY SPARSITY*/
if (!a)
{
	double i;
	char* fname;
	printf ("CREATE: matrix: %dx%d, seed: %d, sparse: %.3f to %.3f\n",m,n,seed,start,end);
	for (i=start; i<end+increment; i+=increment)
	{
		fname = name (m,i,seed);
		frandmat (fname,m,n,i,seed);
		printf ("%s\n",fname);
		free (fname);
	}
	return 0;
}

/*ADDING MATRICES NO DIFF INDEX BY SPARSITY*/
else if (a == 1)
{
	FILE *fp, *ft;
	cs *T, *A = NULL, *B = NULL;
	int j,k;
	clock_t t1 = clock(), t2 = clock();
	double ttaken1, ttaken2, tsum1, tsum2, sparsity, i;
	char* fname;

	ft = fopen ("time.txt","a");
	fprintf (ft, "\nTEST: %dx%d, seed: %d, trials: %d, sparse: %.3f to %.3f\n",m,n,seed,repeat,start,end);
	printf ("TEST: matrix: %dx%d, seed: %d, trials: %d, sparse: %.3f to %.3f\n",m,n,seed,repeat,start,end);

	for (i=start; i<end+increment; i+=increment)
	{
		fname = name (m,i,seed);	
		if ((fp = fopen (fname, "r")))
		{
			T = cs_load (fp);
			A = cs_compress (T);
			cs_spfree (T); fclose (fp); free (fname);
			tsum1=0; tsum2=0;
			sparsity = (double)A->nzmax/(m*n);

			for (j=0; j<repeat; j++)
			{
				t2 = clock();
				B = cs_add (A,A,1,1);
				t2 = clock() - t2;
				t1 = clock();
				if (!(a_diff(A,A))) nd_add(A,A);
				t1 = clock() - t1;
				ttaken1 = ((double)t1)/CLOCKS_PER_SEC;
				ttaken2 = ((double)t2)/CLOCKS_PER_SEC;
				tsum1 += ttaken1; tsum2 += ttaken2;

				for (k=0;k<A->nzmax;k++) A->x[k] = 1;
				cs_spfree (B); B = NULL;
			}

			printf ("%f %f %f\n",sparsity,tsum1/repeat, tsum2/repeat);
			fprintf (ft, "%f %f %f\n",sparsity,tsum1/repeat, tsum2/repeat);
			if (A != NULL) { cs_spfree (A); A = NULL; }
			if (B != NULL) { cs_spfree (B); B = NULL; }
		}
		else
		{
			printf ("ERROR: file %s does not exist\n",fname);
			if (A != NULL) cs_spfree (A);
			if (B != NULL) cs_spfree (B);
			fclose (ft);
			free (fname);
			return -1;	
		}
	}
	fclose (ft);
	return 0;
}


/*ADDING MATRICES OF DIFF INDEX BY SPARSITY*/
else if (a==2)
{
	FILE *fp1, *fp2, *ft;
	cs *T, *S, *A = NULL, *B = NULL, *C = NULL;
	int j;
	clock_t t1 = clock(), t2 = clock();
	double ttaken1, ttaken2, tsum1, tsum2, sparsity1, sparsity2, i;
	char *fname1, *fname2;

	ft = fopen ("time.txt","a");
	fprintf (ft, "\nTEST: %dx%d, seeds: %d/%d, trials: %d, sparse: %.3f to %.3f\n",
		m,n,seed,seed2,repeat,start,end);
	printf ("TEST: matrix: %dx%d, seeds: %d/%d, trials: %d, sparse: %.3f to %.3f\n",
		m,n,seed,seed2,repeat,start,end);

	for (i=start; i<end+increment; i+=increment)
	{
		fname1 = name (m,i,seed);
		fname2 = name (m,i,seed2);	
		if ((fp1 = fopen (fname1, "r")) && (fp2 = fopen (fname2,"r")))
		{
			T = cs_load (fp1); S = cs_load (fp2);
			A = cs_compress (T); B = cs_compress (S);

			cs_spfree (T); cs_spfree (S); fclose (fp1); fclose (fp2); free (fname1); free (fname2);
			tsum1=0; tsum2=0;
			sparsity1 = (double)A->nzmax/(m*n);
			sparsity2 = (double)B->nzmax/(m*n);

			for (j=0; j<repeat; j++)
			{
				t2 = clock();
				C = cs_add (A,B,1,1);
				t2 = clock() - t2;
				cs_spfree (C); C = NULL;
				t1 = clock();
				if (!(a_diff(A,B)))
				{
					nd_add(A,B);
					printf("ERROR: matrices should not be same\n");
					if (A != NULL) cs_spfree (A);
					if (B != NULL) cs_spfree (B);
					if (C != NULL) cs_spfree (C);
					fclose (ft); free (fname1); free (fname2);
					return -1;
				}
				else C = cs_add (A,B,1,1);
				t1 = clock() - t1;
				ttaken1 = ((double)t1)/CLOCKS_PER_SEC;
				ttaken2 = ((double)t2)/CLOCKS_PER_SEC;
				tsum1 += ttaken1; tsum2 += ttaken2;
				cs_spfree (C); C = NULL;
			}
			printf ("%f %f %f %f\n",sparsity1, sparsity2, tsum1/repeat, tsum2/repeat);
			fprintf (ft, "%f %f %f %f\n",sparsity1, sparsity2, tsum1/repeat, tsum2/repeat);
			if (A != NULL) { cs_spfree (A); A = NULL; }
			if (B != NULL) { cs_spfree (B); B = NULL; }
			if (C != NULL) { cs_spfree (C); C = NULL; }
		}
		else //FIX ME: does not close files correctly
		{
			printf ("ERROR: file %s or %s does not exist\n",fname1,fname2);
			if (A != NULL) cs_spfree (A);
			if (B != NULL) cs_spfree (B);
			if (C != NULL) cs_spfree (C);
			fclose (ft); free (fname1); free (fname2);
			return -1;
		}
	}
	fclose (ft);
	return 0;
}

return -1;
}
