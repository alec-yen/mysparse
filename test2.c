#include "cs.h"
#include "mysparse.h"
#include <time.h>
#include <stdlib.h>

/*test sandbox and random matrix generator*/

int SIZE = 10000;
int NUM_ROWS = 1000;
int NUM_COLS = 1000;
int MAX_VALUE = 100;

int main()
{
	srand(time(NULL));
	cs *T = create (NUM_ROWS,NUM_COLS,0);
	for (int k=0;k<SIZE;k++)
	{
		int r = rand()%NUM_ROWS;
		int c = rand()%NUM_COLS;
		double v = rand()%MAX_VALUE + 1;
		add (T,r,c,v);
	}
	//print (T);
	cs_spfree (T);
	
/*	T = create (7,7,0);
	add (T,1,0,4);
	add (T,2,0,7);
	add (T,3,0,10);
	add (T,0,1,1);
	add (T,2,1,8);
	add (T,4,1,12);
	add (T,1,3,5);
	add (T,5,3,14);
	add (T,0,4,2);
	add (T,1,4,6);
	add (T,3,4,11);
	add (T,2,5,9);
	add (T,4,5,13);
	add (T,0,6,3);
	add (T,5,6,15);
	cs_spfree (T);
*/	//sandbox();
	return 0;
}
