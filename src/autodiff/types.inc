#ifdef _HP
#  define _ID _REAL+_HP
#  include "subtypes.inc"
#  define _ID _COMPLEX+_HP
#  include "subtypes.inc"
#endif
#ifdef _SP
#  define _ID _REAL+_SP
#  include "subtypes.inc"
#  define _ID _COMPLEX+_SP
#  include "subtypes.inc"
#endif
#ifdef _DP
#  define _ID _REAL+_DP
#  include "subtypes.inc"
#  define _ID _COMPLEX+_DP
#  include "subtypes.inc"
#endif
#ifdef _XDP
#  define _ID _REAL+_XDP
#  include "subtypes.inc"
#  define _ID _COMPLEX+_XDP
#  include "subtypes.inc"
#endif
#ifdef _QP
#  define _ID _REAL+_QP
#  include "subtypes.inc"
#  define _ID _COMPLEX+_QP
#  include "subtypes.inc"
#endif

#undef _FILE
