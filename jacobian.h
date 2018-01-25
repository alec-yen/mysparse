#include "cs.h"

typedef enum { Fx,Fy,Gx,Gy,Fx0,Fy0,Gx0,Gy0}  jac_name;

static cs* jac_storage[8]; //never used

