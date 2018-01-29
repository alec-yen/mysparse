#include "cs.h"
#include "mysparse.h"

/*add_jac test*/

int main()
{
	cs** jac_stor;
	cs* mGy;
	int m = 7; int n = 7;

	int r1[] =    {1,2,3, 0,2,4, 1,6, 0,1,3, 2,4, 0,5};
	int c1[] =    {0,0,0, 1,1,1, 3,3, 4,4,4, 5,5, 6,6};
	double v1[] = {4,7,10,1,8,12,5,14,2,6,11,9,13,3,15};
	int size = sizeof(r1)/sizeof(r1[0]);

        int r2[] =    {2,3,1,5,2,3,4,3,2,1,6,3,6,2,1};
	int c2[] =    {0,0,1,1,1,1,2,2,2,3,4,5,5,6,6};
	double v2[] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};

        int r3[] =    {1,2,0,4,1,2,3,2,1,0,5,2,6,1,0};
	int c3[] =    {0,0,1,1,1,1,2,2,2,3,4,5,5,6,6};
	double v3[] = {15,14,13,12,11,10,9,8,7,6,5,4,3,2,1};


	jac_stor = alloc_jac (m,n);
	mGy = acc_jac (jac_stor,Gy);
	errprint_jac (add_jac (jac_stor,Gy,r1,c1,v1,size));
	print (mGy);
	errprint_jac (set_jac (jac_stor,Gy,r2,c2,v2,size));
	print (mGy);
	errprint_jac (set_jac (jac_stor,Gy,r3,c3,v3,size));
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
