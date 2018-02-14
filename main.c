#include "cs.h"
#include "mysparse.h"


int main()
{

/*PREDEFINED MATRICES*/
/*	int r1[] =    {1,2,3, 0,2,4, 1,5, 0,1,3, 2,4, 0,5};
	int c1[] =    {0,0,0, 1,1,1, 3,3, 4,4,4, 5,5, 6,6};
	double v1[] = {4,7,10,1,8,12,5,14,2,6,11,9,13,3,15};
	int size1 = sizeof(r1)/sizeof(r1[0]);
        int r2[] =    {1,2,1,1,5};
	int c2[] =    {0,1,3,4,6};
	double v2[] = {100,100,100,100,100};
	int size2 = sizeof(r2)/sizeof(r2[0]);
	int m=7,n=7;
*/

/*ADD_JAC AND SET_JAC TESTING*/
/*
	cs** jac_stor = alloc_jac (m,n);
	cs* mGy = acc_jac (jac_stor,Gy);

	print (mGy);
	add_jac (jac_stor,Gy,r1,c1,v1,size1);
	mGy = acc_jac (jac_stor,Gy);
	print (mGy);
	set_jac (jac_stor,Gy,r2,c2,v2,size2);
	mGy = acc_jac (jac_stor,Gy);
	print (mGy);

	free_jac (jac_stor);
*/


/*PREDEFINED MATRIX ADDING*/
/*	cs* A = fcreate (m,n,r1,c1,v1,size1);
	cs* B = fcreate (m,n,r2,c2,v2,size2);
	array (A);
	array (B);
	if (!diffshape (A,B)) mod (A,B);
	print (A);
	cs_spfree (A);
	cs_spfree (B);
*/


/*COMPARISON OF ADDING METHODS*/
//	Method 1: mod2 or add2 w/ randmat
	cs* A = randmat (10000,10000,0.001);
	if (!(diffshape (A,A))) mod (A,A);
	cs_spfree (A);

//	Method 2: cs_add w/ randmat
/*	cs* A = randmat (10000,10000,0.001);
	cs* B = cs_add (A,A,1,1);
	cs_spfree (B);
	cs_spfree (A);
*/
//	Method 3: mod w/ randmat
/*	cs* A = randmat (10000,10000,0.001);
	mod (A,A); 
	cs_spfree (A);
*/	

	return 0;
}


/*sample matrices*/
/*
	int r1[] =    {1,2,3, 0,2,4, 1,5, 0,1,3, 2,4, 0,5};
	int c1[] =    {0,0,0, 1,1,1, 3,3, 4,4,4, 5,5, 6,6};
	double v1[] = {4,7,10,1,8,12,5,14,2,6,11,9,13,3,15};
	int size1 = sizeof(r1)/sizeof(r1[0]);
        int r2[] =    {1,2,1,1};
	int c2[] =    {0,1,3,4};
	double v2[] = {100,100,100,100};
	int size2 = sizeof(r2)/sizeof(r2[0]);


	int r1[] =    {1,2,3, 0,2,4, 1,5, 0,1,3, 2,4, 0,5};
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
