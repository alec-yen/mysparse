#include "cs.h"
#include <stdio.h>
#include <stdlib.h>

void create(char* name, int m, int n){
	FILE * fp = fopen(name, "w");	
	fprintf (fp, "%d %d %.2f\n", m-1, n-1, 0.00);
	fclose(fp);
}

int main(int argc, char* argv[]){

	//argument check
	if (argc != 5){
		printf ("Need 4 arguments\n");
		return 1;
	}

	FILE * fp1;
	FILE * fp2;
	char* name = "m_added.txt";
	cs *A, *B, *AC, *BC, *C;
	int *i, *j;
	double *x;
	int m, n, nz, k;


	//variable initialization
	double v = atof (argv[4]);
	if (v == 0){ printf ("Please enter value other than 0\n"); return 1; }

	fp1 = fopen( argv[1] , "r" );
	int r = atoi (argv[2]);
	int c = atoi (argv[3]);
	

	//load matrix that you want to add an element to
	A = cs_load(fp1);
	m = A->m; n = A->n;

	if (r>m-1 || c>n-1 || r<0 || c<0){
		printf ("Index (%d,%d) is outside the bounds of this %d by %d matrix\n",r,c,m,n);
		cs_spfree(A);
		fclose(fp1);
		return 1;
	}
	i = A->i; j = A->p; x = A->x; nz = A->nz;

	
	//break if spot is already taken
	for (k=0;k<nz;k++){
		if (i[k] == r && j[k] == c){
			printf ("Value %.2f already exists at this index\n", x[k]);
			cs_spfree(A);
			fclose(fp1);
			return 1;
		}
	}


	//compress matrix
	AC = cs_compress (A);
	fclose(fp1);

	//write back to file (optional)
	fp1 = fopen( argv[1], "w");
	for (k=0;k<nz;k++){
		fprintf (fp1, "%d %d %.2f\n", i[k], j[k], x[k]);
	}
	fprintf (fp1, "%d %d %.2f\n", r,c,v);

	//create second matrix to add element
	create (name, m, n);
	fp2 = fopen( name , "r");
	B = cs_load(fp2);	
	cs_entry(B,r,c,v);
	BC = cs_compress (B);

	//add matrices together
	C = cs_add (AC, BC, 1, 1);
	cs_print(C, 0);
	
	//free everything
	cs_spfree(A);
	cs_spfree(B);
	cs_spfree(AC);
	cs_spfree(BC);
	cs_spfree(C);
	fclose(fp1);
	fclose(fp2);

	return 0;
}
