#include "cs.h"
#include "jacobian.h"

/*change one element at a time for COMPRESSED matrices*/
double acc(const cs * A, int r, int c);
void set(cs * A, int r, int c, double v); /*better version of add*/
void mod(cs * A, int r, int c, double v);
void del(cs * A, int r, int c);

/*print COMPRESSED or TRIPLET matrices to console*/
void csc (const cs * A);
void print (const cs * A);

/*Jacobian, returns TRIPLET matrices*/
cs * add_jac (jac_name s, int* r, int* c, double* v, int size);
cs * set_jac (jac_name s, int* r, int* c, double* v, int size);
cs * alloc_jac (jac_name s, int m, int n);

/*not used*/
cs * add(cs * A, int r, int c, double v);
cs * ucreate_full (int r[], int c[], double v[], int size);
