#if _TYPE_ID == _INTEGER
#  define _TYPE integer
#  define _TYPE_LABEL I
#  include "k_kinds.inc"
#elif _TYPE_ID == _REAL
#  define _TYPE real
#  define _TYPE_LABEL R
#  include "p_kinds.inc"
#elif _TYPE_ID == _COMPLEX
#  define _TYPE complex
#  define _TYPE_LABEL C
#  include "p_kinds.inc"
#endif
#undef _TYPE
#undef _TYPE_LABEL
