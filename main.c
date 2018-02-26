#include "mysparse.h"
#include <stdio.h>
#include <time.h>
#include <string.h>

/* operation = 0 to create, 1 to test */
/* ./main <start spars> <end spars> <increment> <operation> */

int main(int argc, char ** argv)
{

if (argc != 5) { printf ("ERROR: incorrect number of command line arguments\n"); return -1; }

double start = atof(argv[1]);
double end = atof(argv[2]);
double increment = atof(argv[3]);
int a = atoi (argv[4]);

if ( ((a!=0)&&(a!=1)) ) { printf ("ERROR: invalid operation %d\n",a); return -1; }
if ( (start>=1) || (end>=1) || (increment>=1) ) { printf ("ERROR: invalid start/end/increment\n"); return -1; }

int m = 15000; //CHANGE ME
int n = 15000;
int seed = 2;
int repeat = 30;

/*GENERATE MATRIX*/
if (!a)
{
	double i;
	printf ("CREATE: matrix: %dx%d, seed: %d, sparse: %.3f to %.3f\n",m,n,seed,start,end);
	for (i=start; i<end+increment; i+=increment)
	{
		char buffer_rows[10];
		char buffer_spars[10];
		char buffer_seed[10];
		int len = sprintf (buffer_rows,"%05d",m);
		len += sprintf (buffer_spars,"%.3f",i);
		len += sprintf (buffer_seed,"%02d",seed);
		char* fname = malloc (len+15);
		strcpy (fname, "data/m");
		strcat (fname, buffer_rows); strcat (fname, "_");
		strcat (fname, buffer_seed); strcat (fname, "_");
		strcat (fname, buffer_spars); strcat (fname, ".txt");
		frandmat (fname,m,n,i,seed);
		printf ("%s\n",fname);
		free (fname);
	}
	return 0;
}

/*COMPARISON OF ADDING METHODS*/
else if (a == 1)
{
	FILE *fp, *ft;
	cs *T, *A = NULL, *B = NULL;
	int j,k;
	clock_t t1 = clock();
	clock_t t2 = clock();
	double ttaken1, ttaken2, tsum1, tsum2, sparsity, i;

	ft = fopen ("time.txt","a");
	fprintf (ft, "\nTEST: %dx%d, seed: %d, trials: %d, sparse: %.3f to %.3f\n",m,n,seed,repeat,start,end);
	printf ("TEST: matrix: %dx%d, seed: %d, trials: %d, sparse: %.3f to %.3f\n",m,n,seed,repeat,start,end);

	for (i=start; i<end+increment; i+=increment)
	{
		char buffer_rows[10];
		char buffer_spars[10];
		char buffer_seed[10];
		int len = sprintf (buffer_rows,"%05d",m);
		len += sprintf (buffer_spars,"%.3f",i);
		len += sprintf (buffer_seed,"%02d",seed);
		char* fname = malloc (len+15);
		strcpy (fname, "data/m");
		strcat (fname, buffer_rows); strcat (fname, "_");
		strcat (fname, buffer_seed); strcat (fname, "_");
		strcat (fname, buffer_spars); strcat (fname, ".txt");
	
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
				if (!(diffshape(A,A))) mod(A,A);
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

}


/*old test for validity of sum matrix*/
/*				int succ = 1;
				for (k=0;k<A->nzmax;k++) { if (A->x[k] != 2) succ = 0; }
				for (k=0;k<B->nzmax;k++) { if (B->x[k] != 2) succ = 0; }
				if (!succ) printf ("FAILED\n");
*/
