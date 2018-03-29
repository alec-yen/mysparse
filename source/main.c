#include "mysparse.h"

int main(int argc, char ** argv)
{

	/* ./main <add(0) or set(1)> <operation> <start size/spars> <end size/spars> <increment> <constant spars/size> */
/*ADD.C*/
	/* by spars: operation = 0 to create no diff, 1 to add no diff matrix, 12 to add some diff matrix */
	/* by size: operation = 10 to create no diff, 11 to add no diff matrix*/

/*SET.C*/
	/* by spars: operation = 0 to create no diff, 1 to set no diff matrix, 12 to add some diff matrix 
				10 to create some diff, 11 to set some diff matrix */
	/* by size: operation = 20 to create no diff, 21 to set no diff matrix
				30 to create some diff, 31 to set some diff matrix */

	if (argc != 7)
	{
		printf ("ERROR: incorrect number of command line arguments\n");
		printf ("./main <add(0) or set(1)> <operation> <start size/spars> <end size/spars> <increment> <constant spars/size>\n");
		printf ("\tby spars: operation =\t0 to create no diff\t1 to test no diff matrix\n\t\t\t\t10 to create some diff\t11 to test some diff matrix\n\tby size: operation =\t20 to create no diff\t21 to test no diff matrix\n\t\t\t\t30 to create some diff\t31 to test some diff matrix\n");
		return -1;
	}
	int op = atoi (argv[1]);
	int a = atoi (argv[2]);
	double start = atof(argv[3]);
	double end = atof(argv[4]);
	double increment = atof(argv[5]);
	double m = atof (argv[6]);
	if (!op) test_add (a,start,end,increment,m);
	else test_set (a,start,end,increment,m);


/*jac.c functions testing*/
/*	int r1[] =    {3, 0,3,2,1, 0,2,4, 1,5, 1,2,4, 0,5};
	int c1[] =    {4, 4,0,0,0, 1,1,1, 3,3, 4,5,5, 6,6};
	double v1[] = {11,2,4,7,10,1,8,12,5,14,6,9,13,3,15};
	int size1 = sizeof(r1)/sizeof(r1[0]);
        int r2[] =    {1,4,5,3,4,5};
	int c2[] =    {3,1,4,4,5,5};
	double v2[] = {100,100,100,100,100,100};
	int size2 = sizeof(r2)/sizeof(r2[0]);
	int m = 7; int n = 7;

	jac** jac_stor = alloc_jac (m,n);
	add_jac (jac_stor,Fx,r1,c1,v1,size1);
	print (acc_jac(jac_stor,Fx));
	inc_jac (jac_stor,Fx,10,10);
	print (acc_jac(jac_stor,Fx));


	add_jac (jac_stor,Gx,r1,c1,v1,size1);
	set_jac (jac_stor,Gx,r2,c2,v2,size2);
	print (acc_jac(jac_stor,Gx));

	add_jac (jac_stor,Gy,r1,c1,v1,size1);
	add_jac (jac_stor,Gy,r1,c1,v1,size1);
	print (acc_jac(jac_stor,Gy));

	add_jac (jac_stor,Fx0,r2,c2,v2,size2);
	set_jac (jac_stor,Fx0,r1,c1,v1,size1);
	print (acc_jac(jac_stor,Fx0));

	free_jac (jac_stor);
*/	return 0;
}
