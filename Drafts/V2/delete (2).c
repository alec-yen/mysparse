#include "cs.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]){

	//argument check
	if (argc != 4){
		printf ("Need 3 arguments\n");
		return 1;
	}

	FILE * fp1;
	cs *A, *AC;
	int *i, *j;
	double *x;
	int m, n, nz, k, found, index;

	//variable initialization
	fp1 = fopen( argv[1] , "r" );
	int r = atoi (argv[2]);
	int c = atoi (argv[3]);

	//load matrix that you want to delete an element
	A = cs_load(fp1);
	m = A->m; n = A->n;

	if (r>m-1 || c>n-1 || r<0 || c<0){
		printf ("Index (%d,%d) is outside the bounds of this %d by %d matrix\n",r,c,m,n);
		cs_spfree(A);
		fclose(fp1);
		return 1;
	}
	i = A->i; j = A->p; x = A->x; nz = A->nz;
	
	//find the index
	found = 0;	
	for (k=0;k<nz;k++){
		if (i[k] == r && j[k] == c){
			printf ("Value %.2f at (%d,%d) has been deleted\n", x[k], i[k], j[k]);
			index = k;
			found = 1;
			break;
		}
	}
	if (!found) {
		printf ("No value at this index to delete\n");
		cs_spfree (A);
		fclose(fp1);
		return 1;
	}


	//delete the value
	for (k=index;k<nz-1;k++){
		i[k] = i[k+1];
		j[k] = j[k+1];
		x[k] = x[k+1];
	}
	A->nz -= 1;


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
