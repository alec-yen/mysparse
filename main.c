#include "mysparse.h"
#include <stdio.h>
#include <time.h>
#include <string.h>

int main(int argc, char ** argv)
{
/*argv[1] = operation1, argv[2] = operation2, argv[3] = sparsity */

if (argc != 4) { printf ("ERROR: incorrect number of command line arguments\n"); return -1; }
int a = atoi (argv[1]);
int b = atoi (argv[2]);


int m = 10000; //CHANGE ME
int n = 10000; //CHANGE ME

/*GENERATE MATRIX*/
	if (!a && !b)
	{
		double s = atof (argv[3]);
		char* fname = malloc (strlen(argv[3])+10);
		strcpy (fname, "m0");
		strcat (fname, argv[3]);
		strcat (fname, ".txt");
		frandmat (fname,m,n,s);
		free (fname);
		return 0;
	}

/*COMPARISON OF ADDING METHODS*/
	else if (a == 1)
	{
		int succ = 1;
		clock_t t = clock();
		double time_taken, time_sum=0, sparsity;
		int repeat = 30; //CHANGE ME

		FILE *fp, *ft;
		if (b==1) ft = fopen ("time_opt.txt","a");
		else if (b==2) ft = fopen ("time_old.txt","a");

		char* fname = malloc (strlen(argv[3])+10);
		strcpy (fname, "m0");
		strcat (fname, argv[3]);
		strcat (fname, ".txt");

		for (int i=0; i<repeat; i++)
		{
			fp = fopen (fname, "r");
			cs* T = cs_load (fp);
			cs* A = cs_compress (T);
			cs_spfree (T);
			fclose (fp);

			sparsity = (double)A->nzmax/(m*n);

			if (b == 1)
			{
				t = clock();
				if (!(diffshape(A,A))) mod(A,A);
				t = clock() - t;
			
//				printf ("optimized: ");
//				succ = 1; for (int i=0;i<A->nzmax;i++) { if (A->x[i] != 2) succ = 0; }
				cs_spfree (A);
			}
			else if (b == 2)
			{
				t = clock();
				cs* B = cs_add (A,A,1,1);
				t = clock() - t;

//				printf ("cs_add: ");
//				for (int i=0;i<B->nzmax;i++) { if (B->x[i] != 2) succ = 0; }
				cs_spfree (B);
				cs_spfree (A);
			}
			else { printf ("ERROR: wrong command line argument\n"); cs_spfree (A); return -1; }


//			if (succ) printf ("SUCCESS\n");
//			else printf ("FAILED\n");

			time_taken = ((double)t)/CLOCKS_PER_SEC;
			time_sum += time_taken;
		}
		printf ("%s %f %f\n",fname,sparsity,time_sum/repeat);
		fprintf (ft, "%s %f %f\n",fname,sparsity,time_sum/repeat);
		fclose (ft);
		free (fname);

		return 0;
	}
}
