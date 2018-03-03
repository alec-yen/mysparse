#include "cs.h"

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
