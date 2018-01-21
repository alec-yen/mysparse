#include "cs.h"
#include "mysparse.h"


/*add_jac test*/
int main()
{
	jac_mat Thisiswrong;
	int r[] = {1,2,3,0,2,4,1,5,0,1,3,2,4,0,5};
	int c[] = {0,0,0,1,1,1,3,3,4,4,4,5,5,6,6};
	double v[] = {4,7,10,1,8,12,5,14,2,6,11,9,13,3,15};
	int size = sizeof(r)/sizeof(r[0]);

	cs* T = add_jac (Fx,r,c,v,size);
	cs_print (T,0);
	cs_spfree (T);
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
