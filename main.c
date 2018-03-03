#include "mysparse.h"

int main(int argc, char ** argv)
{
/*
	// operation = 0 to create, 1 to add same matrix, 2 to add diff matrix
	// ./main <operation> <start spars> <end spars> <increment> <number of rows/columns>

	if (argc != 6) { printf ("ERROR: incorrect number of command line arguments\n"); return -1; }
	int a = atoi (argv[1]);
	double start = atof(argv[2]);
	double end = atof(argv[3]);
	double increment = atof(argv[4]);
	int m = atoi (argv[5]);
	test (a,start,end,increment,m);
*/


/*	int r1[] =    {3, 0,3,2,1, 0,2,4, 1,5, 1,2,4, 0,5};
	int c1[] =    {4, 4,0,0,0, 1,1,1, 3,3, 4,5,5, 6,6};
	double v1[] = {11,2,4,7,10,1,8,12,5,14,6,9,13,3,15};
	int size1 = sizeof(r1)/sizeof(r1[0]);
        int r2[] =    {6,4,5,3,6,6};
	int c2[] =    {3,2,4,5,5,6};
	double v2[] = {101,102,103,104,105,106};
	int size2 = sizeof(r2)/sizeof(r2[0]);
	int m = 7; int n = 7;


	cs* A = fcreate (m,n,r1,c1,v1,size1,0);
	cs* B = fcreate (m,n,r2,c2,v2,size2,0);
	print (A);	
	print (B);

	A = set2 (A,B);
	array (B);
	print (A);

	cs_spfree (A);
	cs_spfree (B);
*/

	cs* A = randmat (10,10,.5,2);
        int r2[] =    {1,8};
	int c2[] =    {1,9};
	double v2[] = {100,100};
	int size2 = sizeof(r2)/sizeof(r2[0]);
	cs* B = fcreate(10,10,r2,c2,v2,size2,0);
	print (A);
	print (B);
	A = set2 (A,B);
	print (A);
	cs_spfree (A);
	cs_spfree (B);

	return 0;
}
