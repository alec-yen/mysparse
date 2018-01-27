#include "cs.h"
#include "mysparse.h"

/*add_jac test*/

int main()
{

	int m = 7;
	int n = 7;
	cs** jac_stor,**jac_stor2;
	cs* mGy, *mGx, *T;


	int r1[] =    {1,2,3,0,2,4,1,5,0,1,3,2,4,0,5};
	int c1[] =    {0,0,0,1,1,1,3,3,4,4,4,5,5,6,6};
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

	jac_stor = alloc_jac (m,n);
	jac_stor2 = alloc_jac (m,n);
	add_jac (jac_stor,Gy,r1,c1,v1,size1);
	mGy = acc_jac (jac_stor,Gy);
//	add_jac (jac_stor,Gx,r2,c2,v2,size2);
//	mGx = acc_jac (jac_stor,Gx);	

	print (mGy);
	set_jac (jac_stor,Gy,r2,c2,v2,size2);
	print (mGy);
	free_jac (jac_stor);
	free_jac (jac_stor2);
}


/*sample matrices*/
/*      int r[] =    {0, 1, 2, 0, 1, 2};
	int c[] =    {0, 0, 1, 2, 2, 2};
	double v[] = {1, 4, 5, 2, 3, 6};	
*/
