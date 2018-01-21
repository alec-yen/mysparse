#include "cs.h"

typedef enum { Fx,Fy,Gx,Gy,Fx0,Fy0,Gx0,Gy0}  jac_mat;

static cs* jac_storage[8];

