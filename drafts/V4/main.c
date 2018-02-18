#include "mysparse.h"


/*TESTING RESULTS*/
/*
(1) new diffshape+mod
for 10,000x10,000 w/ 99,953 elements, looped inside the inner for loops a total of 199,906+299,859 = 499,765
average time: 0.086
for 10,000x10,000 w/ 199,836 elements, looped inside the inner for loops a total of 399,672+599,508 = 999,180
average time: 0.155

(2) his cs_add
for 10,000x10,000 w/ 99,953 elements, looped inside the inner for loops a total of 299,859
average time: 0.085
for 10,000x10,000 w/ 199,836 elements, looped inside the inner for loops a total of 599,508
average time: 0.159

(3) old diffshape2+mod2
for 10,000x10,000 w/ 99,953 elements, looped inside the inner for loops a total of 598,592*2 = 1,197,184
average time: 0.087
for 10,000x10,000 w/ 199,836 elements, looped inside the inner for loops a total of 2,192,637*2 = 4,385,274
average time: 0.160
*/


int main(int argc, char ** argv)
{

if (argc != 3) { printf ("ERROR: incorrect number of command line arguments\n"); return -1; }
int a = atoi (argv[1]);
int b = atoi (argv[2]);

//frandmat ("m3.txt",10000,10000,.003);

/*COMPARISON OF ADDING METHODS*/
	if (a == 1)
	{
		FILE * fp = fopen ("m3.txt", "r");
		cs* T = cs_load (fp);
		fclose (fp);
		cs* A = cs_compress (T);
		cs_spfree (T);
		
		if (b == 1) //Method 1: mod (new) w/ randmat
		{
			if (!(diffshape(A,A))) { mod(A,A); printf ("new mod %d elements\n",A->nzmax); }
			cs_spfree (A);
		}
		else if (b == 2) //Method 2: cs_add w/ randmat
		{
			cs* B = addcs (A,A,1,1);
			printf ("cs_add %d elements\n",B->nzmax);
			cs_spfree (B);
			cs_spfree (A);
		}
		else if (b == 3) //Method 3: mod2 (old) w/ randmat
		{
			if (!(diffshape2(A,A))) { mod2(A,A); printf ("old mod %d elements\n",A->nzmax); }
			cs_spfree (A);
		}
		else { printf ("ERROR: wrong command line argument\n"); cs_spfree (A); return -1; }
//		for (int i=0;i<A->nzmax;i++) { if (A->x[i] != 2) printf ("ERROR: incorrect sum\n"); }
		return 0;
	}

/*ADD_JAC AND SET_JAC TESTING*/
	else if (a == 2)
	{
		/*predefined matrices*/
		int r1[] =    {3,7,3,6,9,2,0,0,2};
		int c1[] =    {6,5,5,2,1,7,9,6,6};
		double v1[] = {1,1,1,1,1,1,1,1,1};
		int size1 = sizeof(r1)/sizeof(r1[0]);
	  	int r2[] =    {3,7,3,6,9,2,0,0,2};
		int c2[] =    {6,5,5,2,1,7,9,6,6};
		double v2[] = {1,1,1,1,1,1,1,1,1};
		int size2 = sizeof(r2)/sizeof(r2[0]);
		int m=10,n=10;

		if (b == 1) /*jac.c function testing*/
		{
			cs** jac_stor = alloc_jac (m,n);
			cs* mGy,*mGx;
			set_jac (jac_stor,Gy,r1,c1,v1,size1);
			add_jac (jac_stor,Gy,r2,c2,v2,size2);
			set_jac (jac_stor,Gx,r2,c2,v2,size2);

			mGy = acc_jac (jac_stor,Gy);
			mGx = acc_jac (jac_stor,Gx);
			print (mGy);
			print (mGx);
			free_jac (jac_stor);
		}
		else if (b == 2) /*matrix creation testing*/
		{
			cs* A = fcreate (m,n,r1,c1,v1,size1);
			cs* B = fcreate (m,n,r2,c2,v2,size2);
			A = add2 (A,B);
			print (A);
			cs_spfree (A);
			cs_spfree (B);
		}
		else { printf ("ERROR: wrong command line argument\n"); return -1; }
	}
	else { printf ("ERROR: wrong command line argument\n"); return -1; }
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
