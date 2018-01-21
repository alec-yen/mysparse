#include "cs.h"
#include "jacobian.h"

/*change one element at a time for COMPRESSED matrices, not TRIPLET*/
double acc(const cs *A, int r, int c);
void set(cs * A, int r, int c, double v);
void mod(cs *A, int r, int c, double v);
void del(cs *A, int r, int c);

/*print COMPRESSED matrices to console*/
void csc (const cs *A);
void print (const cs *A);

/*Jacobian of TRIPLET matrices*/
cs* add_jac (jac_mat s, int* r, int* c, double* v, int size);
cs* set_jac (jac_mat s, int* r, int* c, double* v, int size);
//cs* acc_jac (jac_mat s, int m, int n);

/*not used*/
cs * add(cs * A, int r, int c, double v);
cs * ucreate_full (int r[], int c[], double v[], int size);
