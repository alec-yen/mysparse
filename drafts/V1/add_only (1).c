#include "cs.h"


void create(FILE * fp, int m, int n, double density){
	
	int nz = m*n*density*0.01;
	int nzm = nz/m;
	int v = 1;
	for (int i = 0 ; i < m ; i++){
		for (int j = 0 ; j < nzm ; j++){
			fprintf (fp, "%d %d %d\n", i, j, v);
		}
	}
	fprintf (fp, "%d %d %.2f\n", m-1, n-1, 0.00);
	fclose(fp);
}



int main(int argc, char* argv[]){
	FILE * fp1;
	FILE * fp2;
	FILE * fp3;	
	char* name = "m_added.txt";	
	cs *A, *B, *AC, *BC, *C;
	int m, n;

	if (argc != 5){
		printf ("Not enough arguments\n");
		return 1;
	}

	//variable initialization
	fp1 = fopen( argv[1] , "r" );
	fp2 = fopen( name , "w");
	
	CS_INT i = atoi (argv[2]);
	CS_INT j = atoi (argv[3]);
	CS_ENTRY x = atof (argv[4]);

	//load matrix that you want to add an element to
	A = cs_load(fp1);	
	m = A->m;
	n = A->n;
	AC = cs_compress (A);

	//create second matrix to add element
	create (fp2, m, n, 0);
	fp2 = fopen( name , "r");
	B = cs_load(fp2);
	cs_entry(B,i,j,x);
	BC = cs_compress (B);


	//add matrices together
	C = cs_add (AC, BC, 1, 1);
	cs_print(C, 0);

	cs_spfree(A);
	cs_spfree(B);
	cs_spfree(AC);
	cs_spfree(BC);
	cs_spfree(C);

	fclose(fp1);
	fclose(fp2);
	return 0;
}
