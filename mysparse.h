#include "cs.h"

/*add.c functions*/
cs* add  (cs * A, cs * B, int * diff);		/*adds matrices together and sets diff to 1 if different shapes (for jac.c functions)*/
cs* add2 (cs * A, cs * B);			/*same as add - no diff parameter*/
int mod  (cs * A, cs * B);			/*adds matrices with same shape together*/
int mod2  (cs * A, cs * B);			/*less efficient version of mod*/
int diffshape (cs * A, cs * B);			/*check if matrices have different shape*/
int diffshape2 (cs * A, cs * B);		/*less efficient version of diffshape*/

/*create.c functions*/
cs * ecreate (int m, int n, int triplet);			/*returns empty matrix (compressed or uncompressed)*/
cs * fcreate (int m, int n, int* i, int* j, double* x, int size); /*returns filled compressed matrix*/
int clear (cs * A);						/*deletes all elements of matrix*/

/*print.c functions*/
double acc (const cs * A, int r, int c);	/*returns value found at index*/
int array (const cs * A); 			/*prints three arrays of matrix*/
int print (const cs * A); 			/*prints matrix in readable form*/

/*randmat.c functions*/
cs* randmat (int m, int n, double sparsity);

/*jac.c functions (only work with compressed)*/
/*0 = success
  1 = clear function fail (set) or no matrices to free (free)
  2 = add function fail (set, add)
  3 = invalid indices (set,add)*/
typedef enum 	{ Fx,Fy,Gx,Gy,Fx0,Fy0,Gx0,Gy0} jac_name;	/*names of Jacobian matrices*/
cs* acc_jac   	(cs ** jac_stor, jac_name s);			/*returns Jacobian matrix given name s*/
int add_jac  	(cs ** jac_stor, jac_name s, 			/*adds r,c,v arrays to empty Jacobian matrix*/
		int * r, int * c, double * v, int size);
int set_jac  	(cs ** jac_stor, jac_name s,			/*sets r,c,v arrays to full Jacobian matrix*/
		int * r, int * c, double * v, int size);
cs** alloc_jac 	(int m, int n);					/*allocate compressed Jacobian matrices*/
int free_jac 	(cs ** jac_stor);				/*free Jacobian matrices*/
int reassign_jac (cs ** jac_stor, jac_name s, cs* A);		/*frees original pointer and reassigns*/



/*--------------------------------NOT USED--------------------------------------------------*/

/*one-at-a-time functions*/
/*0 = success
  1 = invalid passed value of zero (a)
  2 = existing value (a) / no value (m,d)
  3 = invalid index, outside bounds (a,m,d)
  4 = invalid matrix (a,m,d) */
int addone (cs * A, int r, int c, double v); 	/*adds an element to matrix*/
int modone (cs * A, int r, int c, double v); 	/*modifies an element  of matrix*/
int delone (cs * A, int r, int c); 		/*deletes an element of matrix*/

/*error check*/
int errbound (const cs * A, int r, int c);			/*check if r and c are within matrix bounds*/
int errsize (int m, int n);					/*check if m and n are positive*/
int errarr (cs* A, int* r, int* c, int size);			/*check if indices arrays fit inside matrix*/
void errprint_one (int k);					/*print error of one-at-a-time functions*/
void errprint_jac (int k);					/*print error of jacobian functions*/

/*other*/
cs * addone2(cs * A, int r, int c, double v);			/*less efficient version of add above*/
cs * ucreate_full (int* r, int* c, double* v,int size);		/*returns triplet matrix with r,c,v arrays*/
