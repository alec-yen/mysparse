#include "cs.h"
#include "mysparse.h"

/*add testing*/

int main()
{
	int m = 7; int n = 7;

	int r1[] =    {0,0,1,1,2,2};
	int c1[] =    {0,2,2,0,1,2};
	double v1[] = {1,2,3,4,5,6};
	int size1 = sizeof(r1)/sizeof(r1[0]);
	int r2[] =    {0,2,0,2};
	int c2[] =    {0,1,2,2};
	double v2[] = {7,9,10,12};
	int size2 = sizeof(r2)/sizeof(r2[0]);

	cs* T1 = ucreate_full (r1,c1,v1,size1);
	cs* C1 = cs_compress (T1);
	cs* T2 = ucreate_full (r2,c2,v2,size2);
	cs* C2 = cs_compress (T2);
	cs* S;

	cs_spfree (T1);
	cs_spfree (T2);

	print (C1);
	print (C2);	
	S = add (C1,C2);
	print (S);

	
	cs_spfree (C1);
	cs_spfree (C2);
	if (!S) cs_spfree (S);
	return 0;
}


/*sample matrices*/
/*	int r1[] =    {0,0,1,1,2,2};
	int c1[] =    {0,2,2,0,1,2};
	double v1[] = {1,2,3,4,5,6};
	int size1 = sizeof(r1)/sizeof(r1[0]);
	int r2[] =    {0,2,0,2};
	int c2[] =    {0,1,2,2};
	double v2[] = {7,9,10,12};
	int size2 = sizeof(r2)/sizeof(r2[0]);
*/

/*
	int r1[] =    {1,2,3, 0,2,4, 1,5, 0,1,3, 2,4, 0,5};
	int c1[] =    {0,0,0, 1,1,1, 3,3, 4,4,4, 5,5, 6,6};
	double v1[] = {4,7,10,1,8,12,5,14,2,6,11,9,13,3,15};
	int size1 = sizeof(r1)/sizeof(r1[0]);
        int r2[] =    {1,2,1,1};
	int c2[] =    {0,1,3,4};
	double v2[] = {333,444,555,666};
	int size2 = sizeof(r2)/sizeof(r2[0]);
*/

/*	int r1[] =    {1,2,3, 0,2,4, 1,5, 0,1,3, 2,4, 0,5};
	int c1[] =    {0,0,0, 1,1,1, 3,3, 4,4,4, 5,5, 6,6};
	double v1[] = {4,7,10,1,8,12,5,14,2,6,11,9,13,3,15};
	int size1 = sizeof(r1)/sizeof(r1[0]);
        int r2[] =    {2,3,1,5,2,3,4,3,2,1,6,3,6,2,1};
	int c2[] =    {0,0,1,1,1,1,2,2,2,3,4,5,5,6,6};
	double v2[] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};
	int size2 = sizeof(r2)/sizeof(r2[0]);
        int r3[] =    {1,2,0,4,1,2,3,2,1,0,5,2,6,1,0};
	int c3[] =    {0,0,1,1,1,1,2,2,2,3,4,5,5,6,6};
	double v3[] = {15,14,13,12,11,10,9,8,7,6,5,4,3,2,1};
*/
