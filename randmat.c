#include "cs.h"
#include "mysparse.h"
#include <time.h>
#include <stdlib.h>

/*test sandbox and random matrix generator*/

/*int NUM_VALS = 1000;
int NUM_ROWS = 1000;
int NUM_COLS = 1000;
int TRIPLET = 0;
*/
int MAX_VALUE = 100;

void randmat(int NUM_VALS,int NUM_ROWS, int NUM_COLS, int TRIPLET)
{
	srand(time(NULL));
	cs *T = create (NUM_ROWS,NUM_COLS,TRIPLET);
	for (int k=0;k<NUM_VALS;k++)
	{
		int r = rand()%NUM_ROWS;
		int c = rand()%NUM_COLS;
		double v = rand()%MAX_VALUE + 1;
		add (T,r,c,v);
	}
	if (NUM_ROWS < 30 && NUM_COLS < 30) print (T);
	cs_spfree (T);
}
	
/* Warnings at 10000 by 100000 matrices
 Warning: set address range perms: large range [0x5604040, 0x1d37c440) (undefined)
==3364== Warning: set address range perms: large range [0x1d37d040, 0x350f5440) (undefined)
==3364== Warning: set address range perms: large range [0x395d8040, 0x690c8840) (undefined)
==3364== Warning: set address range perms: large range [0x5604028, 0x1d37c458) (noaccess)
==3364== Warning: set address range perms: large range [0x1d37d028, 0x350f5458) (noaccess)
==3364== Warning: set address range perms: large range [0x395d8028, 0x690c8858) (noaccess)
*/
