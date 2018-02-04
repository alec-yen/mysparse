#include "cs.h"

/*add functions*/
cs* add  (cs * A, cs * B);
int mod  (cs * A, cs * B);
int mod2 (cs * A, cs * B);
int errshape (cs * A, cs * B);

/*create, clear, access functions*/
cs * create (int m, int n, int triplet);	/*returns either compressed or triplet matrix*/
int clear (cs * A);				/*deletes all elements of matrix*/
double acc (const cs * A, int r, int c);	/*returns value found at index*/
int array (const cs * A); 			/*prints three arrays of matrix*/
int print (const cs * A); 			/*prints matrix in readable form*/

/*error check*/
int errbound (const cs * A, int r, int c);			/*check if r and c are within matrix bounds*/
int errsize (int m, int n);					/*check if m and n are positive*/
int errarr (cs* A, int* r, int* c, int size);			/*check if indices arrays fit inside matrix*/
void errprint_one (int k);					/*print error of one-at-a-time functions*/
void errprint_jac (int k);					/*print error of jacobian functions*/


/*Jacobian functions (WILL FIX THESE AND INCLUDE IN MAKEFILE)*/
/*0 = success
  1 = clear function fail (set) or no matrices to free (free)
  2 = add function fail (set, add)
  3 = invalid indices (set,add)*/
//typedef enum 	{ Fx,Fy,Gx,Gy,Fx0,Fy0,Gx0,Gy0} jac_name;	/*names of Jacobian matrices*/
//cs* acc_jac   	(cs ** jac_stor, jac_name s);			/*returns Jacobian matrix given name s*/
//int add_jac  	(cs ** jac_stor, jac_name s, 			/*adds r,c,v arrays to empty Jacobian matrix*/
//		int * r, int * c, double * v, int size);
//int set_jac  	(cs ** jac_stor, jac_name s,			/*sets r,c,v arrays to full Jacobian matrix*/
//		int * r, int * c, double * v, int size);
//cs** alloc_jac 	(int m, int n, int triplet);			/*allocate either triplet or compressed Jacobian matrices*/
//int free_jac 	(cs ** jac_stor);				/*free Jacobian matrices*/




/*not used*/
/*one-at-a-time functions*/
/*0 = success
  1 = invalid passed value of zero (a)
  2 = existing value (a) / no value (m,d)
  3 = invalid index, outside bounds (a,m,d)
  4 = invalid matrix (a,m,d) */
int addone (cs * A, int r, int c, double v); 	/*adds an element to matrix*/
int modone (cs * A, int r, int c, double v); 	/*modifies an element  of matrix*/
int delone (cs * A, int r, int c); 		/*deletes an element of matrix*/

cs * addone2(cs * A, int r, int c, double v);			/*less efficient version of add above*/
cs * ucreate_full (int* r, int* c, double* v,int size);		/*returns triplet matrix with r,c,v arrays*/
