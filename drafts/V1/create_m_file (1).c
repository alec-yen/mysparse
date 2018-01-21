#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
	FILE * fp;
	if (argc != 5){
		printf ("Not enough arguments\n");
		return 1;
	}
	//fp = fopen("test.txt","w");
	fp = fopen( argv[1] , "w");	
	int m = atoi( argv[2] );
	int n = atoi( argv[3] );
	double density = atof( argv[4] );
	int nz = m*n*density*0.01;
	int nzm = nz/m;
	float v = 1;
	for (int i = 0 ; i < m ; i++){
		for (int j = 0 ; j < nzm ; j++){
			fprintf (fp, "%d %d %.2f\n", i, j, v);
		}
	}
	fprintf (fp, "%d %d %.2f\n", m-1, n-1, 1.00);
	fclose(fp);
	return 0;
}
