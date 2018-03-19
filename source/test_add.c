#include "mysparse.h"
#include <stdio.h>
#include <time.h>
#include <string.h>

/*create matrix file name*/
char* aname (int rows, double sparsity, int seed)
{
	char buffer_rows[10];
	char buffer_spars[10];
	char buffer_seed[10];
	int len = sprintf (buffer_rows,"%05d",rows);
	len += sprintf (buffer_spars,"%.3f",sparsity);
	len += sprintf (buffer_seed,"%02d",seed);
	char* fname = malloc (len+25);
	strcpy (fname, "data/add_");
	strcat (fname, buffer_rows); strcat (fname, "_");
	strcat (fname, buffer_spars); strcat (fname, ".txt");
	strcat (fname, buffer_seed); strcat (fname, "_");
	return fname;
}

/* testing function for add function runtime*/
/* by spars: operation = 0 to create, 1 to add no diff matrix, 2 to add some diff matrix */
/* by size: operation = 10 to create by size, 11 to add same matrix*/
/* ./main <operation> <start size/spars> <end size/spars> <increment> <constant spars/size> */

int test_add(int a, double start, double end, double increment, double s)
{

int m=0,n=0;
double spars=0;
double check; char confirm;

if ( (a!=0)&&(a!=1)&&(a!=2)&&(a!=10)&&(a!=11) ) { printf ("ERROR: invalid operation %d\n",a); return -1; }

if ( (a==0) || (a==1) || (a==2) )
{
	m = s; n = s;
	if ( (start>=1) || (end>=1) || (increment>=1) ) { printf ("ERROR: invalid start/end/increment\n"); return -1; }
}
else if ( (a==10) || (a==11) )
{
	spars = s;
	if ( (start<10) || (end>25000) || (increment<10) ) { printf ("ERROR: invalid start/end/increment\n"); return -1; }

}

if (a==0)
{
	check = 16*m*n*(start+end)*(1000*(end-start)+1)/2000000;
	printf ("Will take about %.2f MB total. Continue? (y/n) ",check);
	if (scanf ("%c",&confirm)) {};
	if (confirm=='n') return 0;
}
else if (a==10)
{
	//check = WILL FIGURE OUT LATER
	printf ("Will take about %.2f MB total. Continue? (y/n) ",check);
	if (scanf ("%c",&confirm)) {};
	if (confirm=='n') return 0;
}



/*VARIABLES*/
	int seed1 = 2;
	int seed2 = 3;
	int repeat = 300;

	FILE *fp1, *fp2, *ft;
	cs *T, *A = NULL, *B = NULL, *C = NULL;
	int j,k;
	clock_t t1 = clock(), t2 = clock();
	double tsum1, tsum2, sparsity1, sparsity2, i;
	char *fname1, *fname2;


/*GENERATE MATRIX FILES BY SIZE*/
if (a==10)
{
	printf ("ND_ADD CREATE: spars: %.3f, seed: %d, size: %.0f to %.0f\n",spars,seed1,start,end);
	for (i=start; i<end+increment; i+=increment)
	{
		fname1 = aname (i,spars,seed1);
		frandmat (fname1,i,i,spars,seed1,1);
		printf ("%s\n",fname1);
		free (fname1);
	}
	return 0;
}

/*ADDING MATRICES NO DIFF INDEX BY SIZE*/
else if (a==11)
{
	ft = fopen ("time_add.txt","a");
	fprintf (ft, "%.3f\nsize id_add cs_add\n",spars);
	printf ("ND_ADD TEST: spars: %.3f, seed: %d, size: %.0f to %.0f\n",spars,seed1,start,end);

	for (i=start; i<end+increment; i+=increment)
	{
		fname1 = aname (i,spars,seed1);
		if (!(fp1 = fopen (fname1, "r"))) { free_all (A,B,NULL,fname1,NULL,NULL,ft,1); return -1; }
		
		T = cs_load (fp1);
		A = cs_compress (T);
		cs_spfree (T); fclose (fp1); free (fname1);
		tsum1=0; tsum2=0;

		for (j=0; j<repeat; j++)
		{
			t2 = clock();
			B = cs_add (A,A,1,1);
			t2 = clock() - t2;
			t1 = clock();
			if (!(diff_a(A,A))) nd_add(A,A);
			t1 = clock() - t1;
			tsum1 += ((double)t1)/CLOCKS_PER_SEC;
			tsum2 += ((double)t2)/CLOCKS_PER_SEC;

			for (k=0;k<A->nzmax;k++) A->x[k] = 1;
			cs_spfree (B); B = NULL;
		}

		printf ("%5.0f %f %f\n",i,tsum1/repeat, tsum2/repeat);
		fprintf (ft, "%.0f %f %f\n",i,tsum1/repeat, tsum2/repeat);
		if (A != NULL) { cs_spfree (A); A = NULL; }
		if (B != NULL) { cs_spfree (B); B = NULL; }
	}
	fclose (ft);
	return 0;	
}


/*GENERATE MATRIX FILES BY SPARSITY*/
if (!a)
{
	printf ("ND_ADD CREATE: matrix: %dx%d, seed: %d, sparse: %.3f to %.3f\n",m,n,seed1,start,end);
	for (i=start; i<end+increment; i+=increment)
	{
		fname1 = aname (m,i,seed1);
		frandmat (fname1,m,n,i,seed1,1);
		printf ("%s\n",fname1);
		free (fname1);
	}
	return 0;
}

/*ADDING MATRICES NO DIFF INDEX BY SPARSITY*/
else if (a == 1)
{
	ft = fopen ("time_add.txt","a");
	fprintf (ft, "%d\nsparsity id_add cs_add\n",m);
	printf ("ND_ADD TEST: matrix: %dx%d, seed: %d, trials: %d, sparse: %.3f to %.3f\n",m,n,seed1,repeat,start,end);

	for (i=start; i<end+increment; i+=increment)
	{
		fname1 = aname (m,i,seed1);	
		if (!(fp1 = fopen (fname1, "r"))) { free_all (A,B,NULL,fname1,NULL,NULL,ft,1); return -1; }

		T = cs_load (fp1);
		A = cs_compress (T);
		cs_spfree (T); fclose (fp1); free (fname1);
		tsum1=0; tsum2=0;
		sparsity1 = (double)A->nzmax/(m*n);

		for (j=0; j<repeat; j++)
		{
			t2 = clock();
			B = cs_add (A,A,1,1);
			t2 = clock() - t2;
			t1 = clock();
			if (!(diff_a(A,A))) nd_add(A,A);
			t1 = clock() - t1;
			tsum1 += ((double)t1)/CLOCKS_PER_SEC;
			tsum2 += ((double)t2)/CLOCKS_PER_SEC;

			for (k=0;k<A->nzmax;k++) A->x[k] = 1;
			cs_spfree (B); B = NULL;
		}
		printf ("%f %f %f\n",sparsity1,tsum1/repeat, tsum2/repeat);
		fprintf (ft, "%f %f %f\n",sparsity1,tsum1/repeat, tsum2/repeat);
		if (A != NULL) { cs_spfree (A); A = NULL; }
		if (B != NULL) { cs_spfree (B); B = NULL; }
	}
	fclose (ft);
	return 0;
}


/*ADDING MATRICES OF DIFF INDEX BY SPARSITY*/
else if (a==2)
{

	ft = fopen ("time_add.txt","a");
	fprintf (ft, "\nTEST: %dx%d, seeds: %d/%d, trials: %d, sparse: %.3f to %.3f\n",
		m,n,seed1,seed2,repeat,start,end);
	printf ("SD_ADD TEST: matrix: %dx%d, seeds: %d/%d, trials: %d, sparse: %.3f to %.3f\n",
		m,n,seed1,seed2,repeat,start,end);

	for (i=start; i<end+increment; i+=increment)
	{
		fname1 = aname (m,i,seed1);
		fname2 = aname (m,i,seed2);	
		if (!(fp1 = fopen (fname1, "r"))) { free_all (A,B,C,fname1,fname2,NULL,ft,1); return -1; }
		if (!(fp2 = fopen (fname2, "r"))) { free_all (A,B,C,fname2,fname1,fp1,ft,1); return -1; }

		T = cs_load (fp1); A = cs_compress (T); cs_spfree (T);
		T = cs_load (fp2); B = cs_compress (T); cs_spfree (T);

		fclose (fp1); fclose (fp2); free (fname1); free (fname2);
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
			if (!(diff_a(A,B)))
			{
				printf("ERROR: matrices should not be same\n");
				free_all (A,B,C,fname1,fname2,fp1,ft,0); fclose (fp2); return -1;
			}
			else C = cs_add (A,B,1,1);
			t1 = clock() - t1;
			tsum1 += ((double)t1)/CLOCKS_PER_SEC;
			tsum2 += ((double)t2)/CLOCKS_PER_SEC;
			cs_spfree (C); C = NULL;
		}
		printf ("%f %f %f %f\n",sparsity1, sparsity2, tsum1/repeat, tsum2/repeat);
		fprintf (ft, "%f %f %f %f\n",sparsity1, sparsity2, tsum1/repeat, tsum2/repeat);
		if (A != NULL) { cs_spfree (A); A = NULL; }
		if (B != NULL) { cs_spfree (B); B = NULL; }
		if (C != NULL) { cs_spfree (C); C = NULL; }
	}
	fclose (ft);
	return 0;
}

return -1;
}
