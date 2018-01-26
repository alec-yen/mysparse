#include "cs.h"
#include "mysparse.h"

/*add_jac test*/
int main()
{

	int m = 6;
	int n = 7;
	cs** jac_stor;
	cs* mGy, *mGx;


	int r1[] = {1,2,3,0,2,4,1,5,0,1,3,2,4,0,5};
	int c1[] = {0,0,0,1,1,1,3,3,4,4,4,5,5,6,6};
	double v1[] = {4,7,10,1,8,12,5,14,2,6,11,9,13,3,15};
	int size1 = sizeof(r1)/sizeof(r1[0]);

	mGy = ucreate_full(r1,c1,v1,size1);
	print (mGy);
	if (!set(mGy,2,2,1)) printf ("Good\n");
	//errbound (mGy, 1,1);
	cs_spfree (mGy);

/*        int r2[] = {0, 1, 2, 0, 1, 2};
	int c2[] = {0, 0, 1, 2, 2, 2};
	double v2[] = {1, 4, 5, 2, 3, 6};
	int size2 = sizeof(r2)/sizeof(r2[0]);

	jac_stor = alloc_jac (m,n);
	add_jac (jac_stor,Gy,r1,c1,v1,size1);
	mGy = acc_jac (jac_stor,Gy);
	add_jac (jac_stor,Gx,r2,c2,v2,size2);
	mGx = acc_jac (jac_stor,Gx);
	print (mGy);
	print (mGx);
	free_jac (jac_stor);
*/
}


/*sample matrices*/
/*      int r[] = {0, 1, 2, 0, 1, 2};
	int c[] = {0, 0, 1, 2, 2, 2};
	double v[] = {1, 4, 5, 2, 3, 6};	
*/
