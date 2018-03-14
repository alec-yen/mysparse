#include "cs.h"

typedef enum 	{ Fx,Fy,Gx,Gy,Fx0,Fy0,Gx0,Gy0} jac_name;	/*names of Jacobian matrices*/
typedef struct { cs* jac_matrix; int m; int n; } jac;		/*Jacobian struct*/

/*jac.c functions*/
int add_jac  	(jac ** jac_stor, jac_name s, 			/*adds r,c,v arrays to Jacobian matrix*/
		int * r, int * c, double * v, int size);
int set_jac  	(jac ** jac_stor, jac_name s,			/*sets r,c,v arrays to Jacobian matrix*/
		int * r, int * c, double * v, int size);
jac** alloc_jac	(int m, int n);					/*allocate array of pointers to jac structs*/
int free_jac 	(jac ** jac_stor);				/*free array of pointers to jac structs*/

/*add.c + set.c public functions*/
cs* add  (cs * A, cs * B, int * flag);		/*adds matrices, sets flag=1 if requires mem alloc*/
cs* set  (cs * A, cs * B, int * flag);		/*sets matrices, sets flag=1 if requires mem alloc*/


/*---------------------------------------------------------------------------------------------------------------*/


/*randmat.c + test.c functions*/
cs* randmat(int m, int n, double sparsity, int seed);			/*create random matrix*/
int frandmat(char* f, int m, int n, double sparsity, int seed);		/*write random matrix to file*/
int test(int a, double start, double end, double increment, double m);	/*test adding matrices*/

/*print.c functions*/
int array (const cs * A); 			/*prints three 1D arrays of matrix*/
int print (const cs * A); 			/*prints matrix in readable form*/


/*public for testing purposes*/
cs* add2 (cs * A, cs * B);					/*same as add w/o diff param*/
cs* set2 (cs * A, cs * B);					/*same as set w/o diff param*/
int nd_add (cs *A, cs *B);					/*adds matrices if no diff index*/
int diff_a (cs * A, cs * B);					/*returns 1 if diff index, 0 otherwise*/
cs* acc_jac (jac ** jac_stor, jac_name s);			/*returns jac Fx,Fy,etc.*/

