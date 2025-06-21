#define _DERIV Grad
#include "types.inc"
#undef _DERIV
#define _GRADGRAD
#define _DERIV Gradgrad
#include "types.inc"
#undef _GRADGRAD
#undef _DERIV
#define _DIVGRAD
#define _DERIV Divgrad
#include "types.inc"
#undef _DIVGRAD
#undef _DERIV
#undef _TYPE_ID
