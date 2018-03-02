#include "mysparse.h"

int main(int argc, char ** argv)
{

/*	if (argc != 6) { printf ("ERROR: incorrect number of command line arguments\n"); return -1; }
	int a = atoi (argv[1]);
	double start = atof(argv[2]);
	double end = atof(argv[3]);
	double increment = atof(argv[4]);
	int m = atoi (argv[5]);
	test (a,start,end,increment,m);
*/


	int r1[] =    {1,2,3, 0,2,4, 1,5, 0,1,3, 2,4, 0,5};
	int c1[] =    {0,0,0, 1,1,1, 3,3, 4,4,4, 5,5, 6,6};
	double v1[] = {4,7,10,1,8,12,5,14,2,6,11,9,13,3,15};
	int size1 = sizeof(r1)/sizeof(r1[0]);
        int r2[] =    {1,2,1,1};
	int c2[] =    {0,1,3,5};
	double v2[] = {100,100,100,100};
	int size2 = sizeof(r2)/sizeof(r2[0]);
	int m = 7; int n = 7;

	cs* A = fcreate (m,n,r1,c1,v1,size1);
	cs* B = fcreate (m,n,r2,c2,v2,size2);
	print (A);	
	print (B);	

	A = add2 (A,B);
	print (A);	

	cs_spfree (A);
	cs_spfree (B);

	return 0;
}
