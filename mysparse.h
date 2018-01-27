#include "cs.h"

/*error codes*/
/*0 = success
  1 = invalid value of zero (add) / fail (arr,print)
  2 = existing value (add) / no value (mod,del)
  3 = invalid index, outside bounds
  4 = invalid matrix */

/*change one element at a time for COMPRESSED or TRIPLET matrices*/
double acc (const cs * A, int r, int c); /*does not follow error codes, returns 0 or double value*/
int add (cs * A, int r, int c, double v); /*returns 0,1,2,3,4*/
int mod (cs * A, int r, int c, double v); /*returns 0,2,3,4*/
int del (cs * A, int r, int c); /*returns 0,2,3,4*/

/*creation and deletion of COMPRESSED or TRIPLET*/
cs * create (int m, int n, int triplet);
int clear (cs * A); /*return 0,1*/

/*print COMPRESSED or TRIPLET matrices to console*/
int array (const cs * A); /*returns 0,1*/
int print (const cs * A); /*returns 0,1*/

/*Jacobian, returns TRIPLET matrices*/
typedef enum { Fx,Fy,Gx,Gy,Fx0,Fy0,Gx0,Gy0} jac_name;
cs* acc_jac   (cs ** jac_stor, jac_name s);
int add_jac  (cs ** jac_stor, jac_name s, int * r, int * c, double * v, int size);
int set_jac  (cs ** jac_stor, jac_name s, int * r, int * c, double * v, int size);
cs ** alloc_jac (int m, int n);
int free_jac (cs ** jac_stor);

/*error check*/
int errbound (const cs * A, int r, int c); /*returns 0,1*/
void sandbox ();

/*not used*/
cs * add2(cs * A, int r, int c, double v);
cs * ucreate_full (int r[], int c[], double v[], int size);
