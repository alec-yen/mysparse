#include "cs.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]){

	//argument check
	if (argc != 5){
		printf ("Need 4 arguments\n");
		return 1;
	}

	FILE * fp1;
	cs *A, *AC;
	int *i, *j;
	double *x;
	int m, n, nz, k, found;

	//variable initialization
	double v = atof (argv[4]);
	if (v == 0){ printf ("Please enter value other than 0\n"); return 1; }

	fp1 = fopen( argv[1] , "r" );
	int r = atoi (argv[2]);
	int c = atoi (argv[3]);

	//load matrix that you want to modify an element
	A = cs_load(fp1);
	m = A->m; n = A->n;

	if (r>m-1 || c>n-1 || r<0 || c<0){
		printf ("Index (%d,%d) is outside the bounds of this %d by %d matrix\n",r,c,m,n);
		cs_spfree(A);
		fclose(fp1);
		return 1;
	}
	i = A->i; j = A->p; x = A->x; nz = A->nz;
	
	//find and replace
	found = 0;	
	for (k=0;k<nz;k++){
		if (i[k] == r && j[k] == c){
			printf ("Value %.2f has been modified to %.2f\n", x[k], v);
			x[k] = v;
			found = 1;
			break;
		}
	}
	if (!found) {
		printf ("No value at this index to modify\n");
		cs_spfree(A);
		fclose(fp1);
		return 1;
	}

	//compress matrix
	AC = cs_compress (A);
	fclose(fp1);

	//write back to file (optional)
	fp1 = fopen( argv[1], "w");
	for (k=0;k<nz;k++){
		fprintf (fp1, "%d %d %.2f\n", i[k], j[k], x[k]);
	}

	cs_print(AC, 0);
	
	//free everything
	cs_spfree(A);
	cs_spfree(AC);
	fclose(fp1);

	return 0;
}
