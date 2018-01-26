#include "cs.h"

/*change one element at a time for COMPRESSED matrices*/
double acc(const cs * A, int r, int c); /*returns 0,double,infinity*/
int set(cs * A, int r, int c, double v); /*returns 0,1,2,3,4*/
int mod(cs * A, int r, int c, double v); /*returns 0,2,3,4*/
int del(cs * A, int r, int c); /*returns 0,2,3,4*/

/*print COMPRESSED or TRIPLET matrices to console*/
int array (const cs * A); /*returns 0,1*/
int print (const cs * A); /*returns 0,1*/

/*Jacobian, returns TRIPLET matrices*/
typedef enum { Fx,Fy,Gx,Gy,Fx0,Fy0,Gx0,Gy0}  jac_name;
cs* acc_jac (cs** jac_stor, jac_name s);
void add_jac (cs** jac_stor, jac_name s, int* r, int* c, double* v, int size);
void set_jac (cs** jac_stor, jac_name s, int* r, int* c, double* v, int size);
cs ** alloc_jac (int m, int n);
void free_jac (cs** jac_stor);

/*error check*/
int errbound (const cs * A, int r, int c); /*returns 0,1*/
void sandbox ();

/*not used*/
cs * add(cs * A, int r, int c, double v);
cs * ucreate_full (int r[], int c[], double v[], int size);
