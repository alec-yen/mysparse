#include "cs.h"
#include "mysparse.h"

/*add_jac test*/

int main()
{
	cs** jac_stor;
	cs* mGy;

	int r1[] =    {1,2,3, 0,2,4, 1,6, 0,1,3, 2,4, 0,5};
	int c1[] =    {0,0,0, 1,1,1, 3,3, 4,4,4, 5,5, 6,6};
	double v1[] = {4,7,10,1,8,12,5,14,2,6,11,9,13,3,15};
	int rs1 = sizeof(r1)/sizeof(r1[0]);
	int cs1 = sizeof(c1)/sizeof(c1[0]);

        int r2[] =    {2,3,1,5,2,3,4,3,2,1,6,3,6,2,1};
	int c2[] =    {0,0,1,1,1,1,2,2,2,3,4,5,5,6,6};
	double v2[] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};
	int rs2 = sizeof(r2)/sizeof(r2[0]);
	int cs2 = sizeof(c2)/sizeof(c2[0]);

        int r3[] =    {1,2,0,4,1,2,3,2,1,0,5,2,6,1,0};
	int c3[] =    {0,0,1,1,1,1,2,2,2,3,4,5,5,6,6};
	double v3[] = {15,14,13,12,11,10,9,8,7,6,5,4,3,2,1};
	int rs3 = sizeof(r3)/sizeof(r3[0]);
	int cs3 = sizeof(c3)/sizeof(c3[0]);

	int m1, n1, m2, n2, m3, n3;
	if (errarr (r1,&m1,rs1)) { printf ("Invalid r1 with negative indices\n"); return 1; } 
	if (errarr (c1,&n1,cs1)) { printf ("Invalid c1 with negative indices\n"); return 1; } 
	if (errarr (r2,&m2,rs2)) { printf("Invalid r2 with negative indices\n"); return 1; }
	if (errarr (c1,&n2,cs2)) { printf ("Invalid c2 with negative indices\n"); return 1; } 
	if (errarr (r2,&m3,rs3)) { printf("Invalid r3 with negative indices\n"); return 1; }
	if (errarr (c1,&n3,cs3)) { printf ("Invalid c3 with negative indices\n"); return 1; } 

	if (!(rs1==cs1 && rs2==cs2 && rs3==cs3)) { printf ("arrays don't have same size\n"); return 1; }
	if (!(m1==m2==m3 && n1==n2==n3)) { printf ("arrays don't have same num rows or cols\n"); return 1; }
	printf ("all input arrays have same everything\n");

	jac_stor = alloc_jac (m1,n1);

	add_jac (jac_stor,Gy,r1,c1,v1,rs1);
	mGy = acc_jac (jac_stor,Gy);
	print (mGy);
	set_jac (jac_stor,Gy,r2,c2,v2,rs2);
	print (mGy);
	set_jac (jac_stor,Gy,r3,c3,v3,rs3);
	print (mGy);

	free_jac (jac_stor);
	return 0;
}


/*sample matrices*/
/*	int r1[] =    {1,2,3, 0,2,4, 1,5, 0,1,3, 2,4, 0,5};
	int c1[] =    {0,0,0, 1,1,1, 3,3, 4,4,4, 5,5, 6,6};
	double v1[] = {4,7,10,1,8,12,5,14,2,6,11,9,13,3,15};
	int size1 = sizeof(r1)/sizeof(r1[0]);	
        int r2[] =    {2,3,1,5,2,3,4,3,2,1,6,3,6,2,1};
	int c2[] =    {0,0,1,1,1,1,2,2,2,3,4,5,5,6,6};
	double v2[] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};
	int size2 = sizeof(r2)/sizeof(r2[0]);
	int r[] = {0, 1, 2, 0, 1, 2};
	int c[] = {0, 0, 1, 2, 2, 2};
	double v[] = {1, 4, 5, 2, 3, 6};
	int size = sizeof(r)/sizeof(r[0]);
*/
