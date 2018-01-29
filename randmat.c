#include "cs.h"
#include "mysparse.h"
#include <time.h>
#include <stdlib.h>

/*generates either compressed or triplet random matrix*/

int MAX_VALUE = 100;

cs* randmat (int m,int n,int nz,int triplet)
{
	if (errsize(m,n)) return NULL;
	srand(time(NULL));
	cs *T = create (m,n,triplet);
	for (int k=0;k<nz;k++)
	{
		int r = rand()%m;
		int c = rand()%n;
		double v = rand()%MAX_VALUE + 1;
		add (T,r,c,v);
	}
//	if (m < 30 && n < 30) print (T);
	return T;
}
	
/* Warnings at 10000 by 100000 matrices
 Warning: set address range perms: large range [0x5604040, 0x1d37c440) (undefined)
==3364== Warning: set address range perms: large range [0x1d37d040, 0x350f5440) (undefined)
==3364== Warning: set address range perms: large range [0x395d8040, 0x690c8840) (undefined)
==3364== Warning: set address range perms: large range [0x5604028, 0x1d37c458) (noaccess)
==3364== Warning: set address range perms: large range [0x1d37d028, 0x350f5458) (noaccess)
==3364== Warning: set address range perms: large range [0x395d8028, 0x690c8858) (noaccess)
*/
