#if ( \
    (defined(_TYPE_IDS1) && defined(_TYPE_IDS2)) \
    && !(defined(_TYPE_ID1) && defined(_TYPE_ID2)) \
)
#  define _TYPE_IDS _TYPE_IDS2
#  define _TYPE_ID2 _TYPE_ID
#  define _TYPE2 _TYPE
#  define _TYPE_CONV2 _TYPE_CONV
#  define _TYPE_LABEL2 _TYPE_LABEL
#  if _TYPE_IDS1 & _INTEGER
#    define _TYPE_ID1 _INTEGER
#    define _TYPE1 integer
#    define _TYPE_CONV1 int
#    define _TYPE_LABEL1 I
#    include "types.inc"
#    undef _TYPE_ID1
#    undef _TYPE1
#    undef _TYPE_CONV1
#    undef _TYPE_LABEL1
#  endif
#  if _TYPE_IDS1 & _REAL
#    define _TYPE_ID1 _REAL
#    define _TYPE1 real
#    define _TYPE_CONV1 real
#    define _TYPE_LABEL1 R
#    include "types.inc"
#    undef _TYPE_ID1
#    undef _TYPE1
#    undef _TYPE_CONV1
#    undef _TYPE_LABEL1
#  endif
#  if _TYPE_IDS1 & _COMPLEX
#    define _TYPE_ID1 _COMPLEX
#    define _TYPE1 complex
#    define _TYPE_CONV1 cmplx
#    define _TYPE_LABEL1 C
#    include "types.inc"
#    undef _TYPE_ID1
#    undef _TYPE1
#    undef _TYPE_CONV1
#    undef _TYPE_LABEL1
#  endif
#  undef _TYPE_IDS
#  undef _TYPE_ID2
#  undef _TYPE2
#  undef _TYPE_CONV2
#  undef _TYPE_LABEL2
#elif defined(_TYPE_IDS)
#  if _TYPE_IDS & _INTEGER
#    define _TYPE_ID _INTEGER
#    define _TYPE integer
#    define _TYPE_CONV int
#    define _TYPE_LABEL I
#    include "kinds.inc"
#    undef _TYPE_ID
#    undef _TYPE
#    undef _TYPE_CONV
#    undef _TYPE_LABEL
#  endif
#  if _TYPE_IDS & _REAL
#    define _TYPE_ID _REAL
#    define _TYPE real
#    define _TYPE_CONV real
#    define _TYPE_LABEL R
#    include "kinds.inc"
#    undef _TYPE_ID
#    undef _TYPE
#    undef _TYPE_CONV
#    undef _TYPE_LABEL
#  endif
#  if _TYPE_IDS & _COMPLEX
#    define _TYPE_ID _COMPLEX
#    define _TYPE complex
#    define _TYPE_CONV cmplx
#    define _TYPE_LABEL C
#    include "kinds.inc"
#    undef _TYPE_ID
#    undef _TYPE
#    undef _TYPE_CONV
#    undef _TYPE_LABEL
#  endif
#endif
