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

<<<<<<< HEAD
/*Jacobian, returns TRIPLET matrices*/
cs * add_jac (jac_name s, int* r, int* c, double* v, int size);
cs * set_jac (jac_name s, int* r, int* c, double* v, int size);
cs * alloc_jac (jac_name s, int m, int n);
=======
/*Jacobian of TRIPLET matrices*/
cs* add_jac (jac_mat s, int* r, int* c, double* v, int size);
cs* set_jac (jac_mat s, int* r, int* c, double* v, int size);
//cs* acc_jac (jac_mat s, int m, int n);
>>>>>>> f0505432fb85798042bf71556faa924301592bb5

/*not used*/
cs * add(cs * A, int r, int c, double v);
cs * ucreate_full (int r[], int c[], double v[], int size);
