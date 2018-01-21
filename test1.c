#include "cs.h"
#include "mysparse.h"


/*add_jac test*/
int main()
{
	int m = 6;
	int n = 7;
	jac_storage[0] = cs_spalloc (m,n,m*n,1,1);
	jac_storage[1] = cs_spalloc (m,n,m*n,1,1);
	jac_storage[2] = cs_spalloc (m,n,m*n,1,1);
	jac_storage[3] = cs_spalloc (m,n,m*n,1,1);
	jac_storage[4] = cs_spalloc (m,n,m*n,1,1);
	jac_storage[5] = cs_spalloc (m,n,m*n,1,1);
	jac_storage[6] = cs_spalloc (m,n,m*n,1,1);
	jac_storage[7] = cs_spalloc (m,n,m*n,1,1);

	jac_mat s = Gy;
	int r[] = {1,2,3,0,2,4,1,5,0,1,3,2,4,0,5};
	int c[] = {0,0,0,1,1,1,3,3,4,4,4,5,5,6,6};
	double v[] = {4,7,10,1,8,12,5,14,2,6,11,9,13,3,15};
	int size = sizeof(r)/sizeof(r[0]);

	cs* T = add_jac (s,r,c,v,size);
//	cs* T = ucreate_full (r,c,v,size);
	cs_print (T,0);
//	cs_spfree (T);

	cs_spfree (jac_storage[0]);
	cs_spfree (jac_storage[1]);
	cs_spfree (jac_storage[2]);
	cs_spfree (jac_storage[3]);
	cs_spfree (jac_storage[4]);
	cs_spfree (jac_storage[5]);
	cs_spfree (jac_storage[6]);
	cs_spfree (jac_storage[7]);

}

/*print test*/
/*int main()
{
	cs *T, *C;
	int size;
	int r[] = {1,2,3,0,2,4,1,5,0,1,3,2,4,0,5};
	int c[] = {0,0,0,1,1,1,3,3,4,4,4,5,5,6,6};
	double v[] = {4,7,10,1,8,12,5,14,2,6,11,9,13,3,15};
		

	size = sizeof(r)/sizeof(r[0]);
	T = ucreate_full (r,c,v,size);
	C = cs_compress (T);
	print (C);
	set (C,2,4,16);
	print (C);
	set (C,4,6,17);
	print (C);
	set (C,2,2,18);
	print (C);

	//C = add (C,2,4,16);
	//C = add (C,4,6,17);
	//C = add (C,2,2,18);	
	
	cs_spfree (T);
	cs_spfree (C);

}*/

/*sample matrices*/
/*      int r[] = {0, 1, 2, 0, 1, 2};
	int c[] = {0, 0, 1, 2, 2, 2};
	double v[] = {1, 4, 5, 2, 3, 6};	
*/
