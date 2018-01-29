#include "cs.h"
#include "mysparse.h"

/*test randmat or sandbox*/

int main(int argc, char** argv)
{
	if (argc != 5)
	{
		printf ("Required Input: ./test2 <num_rows> <num_cols> <num_vals> <triplet>\n");
		return 1;
	}
	int m = atoi(argv[1]);
	int n = atoi(argv[2]);
	int nz = atoi(argv[3]);
	int triplet = atoi(argv[4]);
	cs* T = randmat (m,n,nz,triplet);
	if (!T) printf ("Invalid <num_rows> or <num_cols>\n");
	cs_spfree (T);
	//sandbox();
	return 0;
}
