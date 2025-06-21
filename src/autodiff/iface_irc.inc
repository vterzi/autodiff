public :: _OP
interface _OP
#define _ID _INTEGER
#include "derivs.inc"
#define _ID _REAL
#include "derivs.inc"
#define _ID _COMPLEX
#include "derivs.inc"
end interface _OP
#undef _OP
