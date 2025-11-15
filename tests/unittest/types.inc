#if defined(_TYPE_IDS)
#  if _TYPE_IDS & _LOGICAL
#    define _TYPE_ID _LOGICAL
#    define _TYPE logical
#    define _TYPE_LABEL L
#    include "kinds.inc"
#    undef _TYPE_ID
#    undef _TYPE
#    undef _TYPE_LABEL
#  endif
#  if _TYPE_IDS & _INTEGER
#    define _TYPE_ID _INTEGER
#    define _TYPE integer
#    define _TYPE_LABEL I
#    include "kinds.inc"
#    undef _TYPE_ID
#    undef _TYPE
#    undef _TYPE_LABEL
#  endif
#  if _TYPE_IDS & _REAL
#    define _TYPE_ID _REAL
#    define _TYPE real
#    define _TYPE_LABEL R
#    include "kinds.inc"
#    undef _TYPE_ID
#    undef _TYPE
#    undef _TYPE_LABEL
#  endif
#  if _TYPE_IDS & _COMPLEX
#    define _TYPE_ID _COMPLEX
#    define _TYPE complex
#    define _TYPE_LABEL C
#    include "kinds.inc"
#    undef _TYPE_ID
#    undef _TYPE
#    undef _TYPE_LABEL
#  endif
#endif
