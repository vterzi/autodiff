#if _TYPE_IDS & _INTEGER
#  define _TYPE_ID _INTEGER
#  define _TYPE integer
#  define _TYPE_LABEL I
#  include "k_kinds.inc"
#  undef _TYPE_ID
#  undef _TYPE
#  undef _TYPE_LABEL
#endif
#if _TYPE_IDS & _REAL
#  define _TYPE_ID _REAL
#  define _TYPE real
#  define _TYPE_LABEL R
#  include "p_kinds.inc"
#  undef _TYPE_ID
#  undef _TYPE
#  undef _TYPE_LABEL
#endif
#if _TYPE_IDS & _COMPLEX
#  define _TYPE_ID _COMPLEX
#  define _TYPE complex
#  define _TYPE_LABEL C
#  include "p_kinds.inc"
#  undef _TYPE_ID
#  undef _TYPE
#  undef _TYPE_LABEL
#endif
