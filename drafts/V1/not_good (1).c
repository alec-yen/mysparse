#include "cs.h"
#include <stdio.h>
#include <stdlib.h>

void create(FILE * fp, int m, int n, double density){
	
	int nz = m*n*density*0.01;
	int nzm = nz/m;
	CS_ENTRY v = 1;
	for (CS_INT i = 0 ; i < m ; i++){
		for (CS_INT j = 0 ; j < nzm ; j++){
			fprintf (fp, "%d %d %.2f\n", i, j, v);
		}
	}
	fprintf (fp, "%d %d %.2f\n", m-1, n-1, 0.00);
	fclose(fp);
}


cs *add(cs *C, int i, int j, double x, int *r, int *c, double *v, int m, int n){
	FILE * fp2;
	cs *B,*BC;
	char* name = "m_added.txt";
	int size = C->nzmax;

	//break if spot is already taken
	int k;
	for (k=0;k<size;k++){
		if (r[k] == i && c[k] == j){
			printf ("Value %.2f already exists at this index\n", v[k]);
			return C;
		}
	}
	
	fp2 = fopen( name , "w");
	//create second matrix to add element
	create (fp2, m, n, 0);
	fp2 = fopen( name , "r");
	B = cs_load(fp2);	
	cs_entry(B,i,j,x);

	BC = cs_compress (B);


	//add matrices together

	C = cs_add (C, BC, 1, 1);
	r[size] = i;
	c[size] = j;
	v[size] = x;

	cs_print (C,0);
	return C;
}

cs *mod (cs *C, int i, int j, double x, int *r, int *c, double *v, int m, int n){
	int size = C->nzmax;
	int found = 0;	
	int k;
	for (k=0;k<size;k++){
		if (r[k] == i && c[k] == j){						
			printf ("Value %.2f has been modified to %.2f\n", v[k], x);
			v[k] = x; //Questionable?
			found = 1;
			break;
		}
	}
	if (!found) {
		printf ("No value at this index to modify\n");
		return C;
	}
	
	cs_print (C,0);
	return C;
}



int main(int argc, char* argv[]){
	FILE * fp1;
	cs *A, *C;
	int *r,*c;
	double *v;
	int m, n, nz;
	char *command = (char*) malloc (10*sizeof(char));

	CS_INT i;
	CS_INT j;
	CS_ENTRY x;

	if (argc != 2){
		printf ("Not enough arguments\n");
		return 1;
	}

	fp1 = fopen( argv[1] , "r" );	

	//load matrix that you want to add an element to
	A = cs_load(fp1);
	m = A->m;
	n = A->n;
	nz = A->nz;
	fclose(fp1);

	//allocate space
	r = (int*) malloc (m*n*sizeof(int));
	c = (int*) malloc (m*n*sizeof(int));
	v = (double*) malloc (m*n*sizeof(double));
	C = cs_spalloc (m, n, nz, 1, 0) ;
	
	//compress matrix
	C = cs_compress (A);
	v = A->x;
	r = A->i;	
	c = A->p;
	
	//user commands	
	do{
	printf ("Enter a command: ");
	scanf ("%s", command);
		if (*command == *("add")){
			scanf ("%d %d %lf", &i,&j,&x);
			C = add (C,i,j,x,r,c,v,m,n);
		}

		if (*command == *("debug")){
			int k;			
			for (k=0;k<C->nzmax;k++){
				printf ("%.2f ", v[k]);
			}
			printf("\n");
		}
		
		if (*command == *("mod")){
			scanf ("%d %d %lf",&i,&j,&x);
			C = mod (C,i,j,x,r,c,v,m,n);
		}
	}while (*command != *("stop"));

	free(r);
	free(v);
	free(c);
	free(command);	
	free(A);
	free(C);

	
	return 0;
}



	//write back
/*	fp1 = fopen( argv[1], "w");
	for (k=0;k<size;k++){
		fprintf (fp1, "%d %d %.2f\n", A->i[k], A->p[k], A->x[k]);
	}
	fprintf (fp1, "%d %d %.2f\n", i,j,x);
*/
