#include "cs.h"
#include "mysparse.h"

/*test randmat and sandbox*/

int main(int argc, char** argv)
{
	int vals = atoi(argv[1]);
	int rows = atoi(argv[2]);
	int cols = atoi(argv[3]);
	int triplet = atoi(argv[4]);
	randmat(vals,rows,cols,triplet);
	//sandbox();
	return 0;
}
