#include "cs.h"

/*error codes*/
/*0 = success
  1 = fail / invalid passed value of zero (a)
  2 = existing value (a) / no value (m,d)
  3 = invalid index, outside bounds (a,m,d)
  4 = invalid matrix (a,m,d) */

/*one at a time*/
int add (cs * A, int r, int c, double v); 	/*adds an element to matrix*/
int mod (cs * A, int r, int c, double v); 	/*modifies an element  of matrix*/
int del (cs * A, int r, int c); 		/*deletes an element of matrix*/

/*creation and deletion*/
cs * create (int m, int n, int triplet);	/*returns either compressed or triplet matrix*/
int clear (cs * A);				/*deletes all elements of matrix*/

/*access elements*/
double acc (const cs * A, int r, int c);	/*returns value found at index*/
int array (const cs * A); 			/*prints three arrays of matrix*/
int print (const cs * A); 			/*prints matrix in readable form*/

/*error check*/
int errbound (const cs * A, int r, int c);			/*check if r and c are within matrix bounds*/
void sandbox ();						/*testing of non-Jacobian functions*/
void randmat (int vals,int rows,int cols,int triplet);		/*testing of memory efficiency*/

/*Jacobian (TRIPLET only)*/
typedef enum 	{ Fx,Fy,Gx,Gy,Fx0,Fy0,Gx0,Gy0} jac_name;	/*names of Jacobian matrices*/
cs* acc_jac   	(cs ** jac_stor, jac_name s);			/*returns Jacobian matrix given name s*/
int add_jac  	(cs ** jac_stor, jac_name s, 			/*adds r,c,v arrays to empty Jacobian matrix*/
		int * r, int * c, double * v, int size);
int set_jac  	(cs ** jac_stor, jac_name s,			/*sets r,c,v arrays to full Jacobian matrix*/
		int * r, int * c, double * v, int size);
cs** alloc_jac 	(int m, int n);					/*allocate Jacobian matrices*/
int free_jac 	(cs ** jac_stor);				/*free Jacobian matrices*/


/*not used*/
cs * add2(cs * A, int r, int c, double v);			/*less efficient version of add above*/
cs * ucreate_full (int* r, int* c, double* v,int size);		/*returns triplet matrix with r,c,v arrays*/
