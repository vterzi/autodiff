public :: _OP
interface _OP
#if _TYPE_IDS & _INTEGER
#  define _TYPE_ID _INTEGER
#  include "derivs.inc"
#endif
#if _TYPE_IDS & _REAL
#  define _TYPE_ID _REAL
#  include "derivs.inc"
#endif
#if _TYPE_IDS & _COMPLEX
#  define _TYPE_ID _COMPLEX
#  include "derivs.inc"
#endif
end interface _OP
#undef _OP
#undef _TYPE_IDS
