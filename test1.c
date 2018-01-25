#include "cs.h"
#include "mysparse.h"


/*add_jac test*/
int main()
{
	int m = 6;
	int n = 7;

	jac_name s = Gy;

	/*necessary lines each time*/
	int r[] = {1,2,3,0,2,4,1,5,0,1,3,2,4,0,5};
	int c[] = {0,0,0,1,1,1,3,3,4,4,4,5,5,6,6};
	double v[] = {4,7,10,1,8,12,5,14,2,6,11,9,13,3,15};
	int size = sizeof(r)/sizeof(r[0]);

	cs* T = add_jac (s,r,c,v,size);
//	cs* T = ucreate_full (r,c,v,size);
	cs_print (T,0);
	if (!(cs_entry (T,2,1,16))) {printf ("error\n"); };
	cs_print (T,0);
	cs_spfree (T);



}


/*sample matrices*/
/*      int r[] = {0, 1, 2, 0, 1, 2};
	int c[] = {0, 0, 1, 2, 2, 2};
	double v[] = {1, 4, 5, 2, 3, 6};	
*/
