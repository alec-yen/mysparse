#include "cs.h"

/*change one element at a time for COMPRESSED matrices*/
double acc(const cs * A, int r, int c);
void set(cs * A, int r, int c, double v); /*better version of add*/
void mod(cs * A, int r, int c, double v);
void del(cs * A, int r, int c);

/*print COMPRESSED or TRIPLET matrices to console*/
void csc (const cs * A);
void print (const cs * A);

/*Jacobian, returns TRIPLET matrices*/
typedef enum { Fx,Fy,Gx,Gy,Fx0,Fy0,Gx0,Gy0}  jac_name;
cs* acc_jac (cs** jac_stor, jac_name s);
void add_jac (cs** jac_stor, jac_name s, int* r, int* c, double* v, int size);
cs * set_jac (jac_name s, int* r, int* c, double* v, int size);
cs ** alloc_jac (int m, int n);
void free_jac (cs** jac_stor);

/*not used*/
cs * add(cs * A, int r, int c, double v);
cs * ucreate_full (int r[], int c[], double v[], int size);
