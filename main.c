#include "mysparse.h"
#include <stdio.h>
#include <time.h>
#include <string.h>

/*0 to create, 1 to test */
/*argv[1] = operation, argv[2] = sparsity */
int main(int argc, char ** argv)
{

if (argc != 3) { printf ("ERROR: incorrect number of command line arguments\n"); return -1; }
int a = atoi (argv[1]);

int m = 10000; //CHANGE ME
int n = 10000;
double start = .001;
double increment = .001;
int repeat = 300;

/*GENERATE MATRIX*/
if (!a)
{
	double i, s = atof (argv[2]);
	for (i=start; i<s; i+=increment)
	{
		char buffer[10];
		int len = sprintf (buffer,"%.4f",i);
		char* fname = malloc (len+20);
		strcpy (fname, "data/m"); strcat (fname, buffer); strcat (fname, ".txt");
		frandmat (fname,m,n,i);
		printf ("created %s\n",fname);
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
	double ttaken1, ttaken2, tsum1, tsum2, sparsity;
	double i,s = atof (argv[2]);

	ft = fopen ("time.txt","a");
	fprintf (ft, "new test\n");

	for (i=start; i<s; i+=increment) /*loop through files*/
	{
		tsum1=0; tsum2=0;

		char buffer[10];
		int len = sprintf (buffer,"%.4f",i);
		char* fname = malloc (len+20);
		strcpy (fname, "data/m"); strcat (fname, buffer); strcat (fname, ".txt");
	
		fp = fopen (fname, "r");
		T = cs_load (fp);
		A = cs_compress (T);
		cs_spfree (T); fclose (fp);

		sparsity = (double)A->nzmax/(m*n);

		for (j=0; j<repeat; j++) /*loop through trials*/
		{
			t2 = clock();
			B = cs_add (A,A,1,1);
			t2 = clock() - t2;

			t1 = clock();
			if (!(diffshape(A,A))) mod(A,A);
			t1 = clock() - t1;

/*			int succ = 1;
			for (k=0;k<A->nzmax;k++) { if (A->x[k] != 2) succ = 0; }
			for (k=0;k<B->nzmax;k++) { if (B->x[k] != 2) succ = 0; }
			if (!succ) printf ("FAILED\n");
*/			for (k=0;k<A->nzmax;k++) A->x[k] = 1;

			ttaken1 = ((double)t1)/CLOCKS_PER_SEC;
			ttaken2 = ((double)t2)/CLOCKS_PER_SEC;
			tsum1 += ttaken1; tsum2 += ttaken2;
			cs_spfree (B); B = NULL;
		}
		printf ("%f %f %f\n",sparsity,tsum1/repeat, tsum2/repeat);
		fprintf (ft, "%f %f %f\n",sparsity,tsum1/repeat, tsum2/repeat);

		if (A != NULL) cs_spfree (A);
		if (B != NULL) cs_spfree (B);	
		free (fname);
	}
	fclose (ft);
	return 0;
}

}
