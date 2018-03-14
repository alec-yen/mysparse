#include "cs.h"

/*add.c + set.c public functions*/
cs* add  (cs * A, cs * B, int * flag);		/*adds matrices, sets flag=1 if diff index*/
cs* add2 (cs * A, cs * B);
cs* set  (cs * A, cs * B, int * flag);		/*sets matrices, sets flag=1 if diff index*/
cs* set2 (cs * A, cs * B);

/*randmat.c + test.c functions*/
cs* randmat(int m, int n, double sparsity, int seed);			/*create random matrix*/
int frandmat(char* f, int m, int n, double sparsity, int seed);		/*write random matrix to file*/
int test(int a, double start, double end, double increment, double m);	/*test adding matrices*/

/*print.c functions*/
int array (const cs * A); 			/*prints three arrays of matrix*/
int print (const cs * A); 			/*prints matrix in readable form*/

/*jac.c struct*/
typedef enum 	{ Fx,Fy,Gx,Gy,Fx0,Fy0,Gx0,Gy0} jac_name;	/*names of Jacobian matrices*/
typedef struct { cs* jac_matrix; int m; int n; } jac;

/*jac.c functions*/
cs* acc_jac   	(jac ** jac_stor, jac_name s);			/*returns Jacobian matrix given name s*/
int add_jac  	(jac ** jac_stor, jac_name s, 			/*adds r,c,v arrays to empty Jacobian matrix*/
		int * r, int * c, double * v, int size);
int set_jac  	(jac ** jac_stor, jac_name s,			/*sets r,c,v arrays to full Jacobian matrix*/
		int * r, int * c, double * v, int size);
jac** alloc_jac	(int m, int n);					/*allocate csc Jacobian matrices*/
int free_jac 	(jac ** jac_stor);				/*free Jacobian matrices*/

/*public for testing*/
int nd_add (cs *A, cs *B);			/*adds matrices if no different*/
int diff_a (cs * A, cs * B);			/*checking function for add*/
cs * fcreate (int m, int n, int* i, int* j, double* x, int size, int trip); 	/*returns filled matrix*/


/*--------------------------------NOT USED--------------------------------------------------*/

/*add_his.c functions (for efficiency testing purposes)*/
CS_INT scattercs (const cs *A, CS_INT j, CS_ENTRY beta, CS_INT *w, CS_ENTRY *x, CS_INT mark,
    cs *C, CS_INT nz, int* count);
cs *addcs (const cs *A, const cs *B, CS_ENTRY alpha, CS_ENTRY beta);
