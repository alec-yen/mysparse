#include "mysparse.h"

/* testing function for add function runtime*/
/* by spars: operation = 0 to create no diff, 1 to add no diff matrix
			10 to create some diff, 11 to add some diff matrix */
/* by size: operation = 20 to create no diff, 21 to add no diff matrix
			30 to create some diff, 31 to add some diff matrix */
/* ./main <operation> <start size/spars> <end size/spars> <increment> <constant spars/size> */
int test_add(int a, double start, double end, double increment, double s)
{

int m=0,n=0; double spars=0, check=0; char confirm;

/*ERROR CHECKING*/
if (  (a!=0)&&(a!=1)&&(a!=10)&&(a!=11)&&(a!=20)&&(a!=21)&&(a!=30)&&(a!=31) )
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
	int val1 = 1;
	int repeat = 500; //how many trials

	FILE *fp1, *fp2, *ft;
	cs *T, *A = NULL, *B = NULL, *C = NULL;
	int j,k;
	clock_t t1 = clock(), t2 = clock();
	double tsum1, tsum2, sparsity1, sparsity2, i;
	char *fname1 = NULL, *fname2 = NULL;

/*CALCULATE NEEDED MEMORY TO CREATE*/
if (!(a%10))
{
	for (double i=start; i<end+increment; i+=increment)
	{
		if (a==0) check += 16*i*m*n/1000000;
		else if (a==10) check += 2*16*i*m*n/1000000;
		else if (a==20) check += 16*spars*i*i/1000000;
		else if (a==30) check += 2*16*spars*i*i/1000000;
	}
	printf ("Will take about %.2f MB total. Continue? (y/n) ",check);
	if (scanf ("%c",&confirm)) {};
	if (confirm=='n') return 0;
}

/*CREATE MATRIX FILES BY SPARSITY*/
if (a==0)
{
	printf ("ND_ADD CREATE: matrix: %dx%d, seed: %d, sparse: %.3f to %.3f\n",m,n,seed1,start,end);
	for (i=start; i<end+increment; i+=increment) test_create(fname1,m,i,seed1,val1,NULL,1,1,1,0);
	return 0;
}

/*CREATE MATRICES OF DIFF INDEX BY SPARSITY*/
else if (a==10)
{
	printf ("SD_ADD CREATE: matrix: %dx%d, seed: %d, sparse: %.3f to %.3f\n",m,n,seed1,start,end);
	for (i=start; i<end+increment; i+=increment) test_create (fname1,m,i,seed1,val1,fname2,i,seed2,val1,1);
}

/*CREATE MATRIX FILES BY SIZE*/
else if (a==20)
{
	printf ("ND_ADD CREATE: spars: %.3f, seed: %d, size: %.0f to %.0f\n",spars,seed1,start,end);
	for (i=start; i<end+increment; i+=increment) test_create(fname1,i,spars,seed1,val1,NULL,1,1,1,0);
	return 0;
}

/*CREATE MATRICES OF DIFF INDEX BY SIZE*/
else if (a==30)
{
	printf ("SD_ADD CREATE: spars: %.3f, seed: %d, size: %.0f to %.0f\n",spars,seed1,start,end);
	for (i=start; i<end+increment; i+=increment)
		test_create(fname1,i,spars,seed1,val1,fname2,spars,seed2,val1,1);
	return 0;
}

/*ADDING MATRICES NO DIFF INDEX BY SPARSITY*/
else if (a==1)
{
	ft = fopen ("time_add.txt","a");
	fprintf (ft, "%d\nsparsity id_add cs_add\n",m);
	printf ("ND_ADD TEST: matrix: %dx%d, seed: %d, trials: %d, sparse: %.3f to %.3f\n",m,n,seed1,repeat,start,end);

	for (i=start; i<end+increment; i+=increment)
	{
		fname1 = name (m,i,seed1,val1);	
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

			for (k=0;k<A->nzmax;k++) A->x[k] = val1;
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
else if (a==11)
{
	ft = fopen ("time_add.txt","a");
	fprintf (ft, "\nTEST: %dx%d, seeds: %d/%d, trials: %d, sparse: %.3f to %.3f\n",
		m,n,seed1,seed2,repeat,start,end);
	printf ("SD_ADD TEST: matrix: %dx%d, seeds: %d/%d, trials: %d, sparse: %.3f to %.3f\n",
		m,n,seed1,seed2,repeat,start,end);

	for (i=start; i<end+increment; i+=increment)
	{
		fname1 = name (m,i,seed1,val1);
		fname2 = name (m,i,seed2,val1);	
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
				free_all (A,B,C,NULL,NULL,NULL,ft,0); return -1;
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

/*ADDING MATRICES NO DIFF INDEX BY SIZE*/
else if (a==21)
{
	ft = fopen ("time_add.txt","a");
	fprintf (ft, "%.3f\nsize id_add cs_add\n",spars);
	printf ("ND_ADD TEST: spars: %.3f, seed: %d, trials: %d, size: %.0f to %.0f\n",spars,seed1,repeat,start,end);

	for (i=start; i<end+increment; i+=increment)
	{
		fname1 = name (i,spars,seed1,val1);
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

			for (k=0;k<A->nzmax;k++) A->x[k] = val1;
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

/*ADDING MATRICES OF DIFF INDEX BY SIZE*/
else if (a==31)
{
	ft = fopen ("time_add.txt","a");
	fprintf (ft, "%.3f\nsize id_add cs_add\n",spars);
	printf ("SD_ADD TEST: spars: %.3f, seeds: %d/%d, trials: %d, size: %.0f to %.0f\n",
		spars,seed1,seed2,repeat,start,end);

	for (i=start; i<end+increment; i+=increment)
	{
		fname1 = name (i,spars,seed1,val1);
		fname2 = name (i,spars,seed2,val1);
		if (!(fp1 = fopen (fname1, "r"))) { free_all (A,B,C,fname1,fname2,NULL,ft,1); return -1; }
		if (!(fp2 = fopen (fname2, "r"))) { free_all (A,B,C,fname2,fname1,fp1,ft,1); return -1; }

		T = cs_load (fp1); A = cs_compress (T); cs_spfree (T);
		T = cs_load (fp2); B = cs_compress (T); cs_spfree (T);

		fclose (fp1); fclose (fp2); free (fname1); free (fname2);
		tsum1=0; tsum2=0;

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
				free_all (A,B,C,NULL,NULL,NULL,ft,0); return -1;
			}
			else C = cs_add (A,B,1,1);
			t1 = clock() - t1;
			tsum1 += ((double)t1)/CLOCKS_PER_SEC;
			tsum2 += ((double)t2)/CLOCKS_PER_SEC;
			cs_spfree (C); C = NULL;
		}
		printf ("%5.0f %f %f\n",i, tsum1/repeat, tsum2/repeat);
		fprintf (ft, "%.0f %f %f\n",i, tsum1/repeat, tsum2/repeat);
		if (A != NULL) { cs_spfree (A); A = NULL; }
		if (B != NULL) { cs_spfree (B); B = NULL; }
		if (C != NULL) { cs_spfree (C); C = NULL; }
	}
	fclose (ft);
	return 0;
}

return -1;
}
