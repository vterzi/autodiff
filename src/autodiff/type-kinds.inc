#ifdef _K1
#  define _ID (_INTEGER | _K1)
#  include "derivs.inc"
#endif
#ifdef _K2
#  define _ID (_INTEGER | _K2)
#  include "derivs.inc"
#endif
#ifdef _K4
#  define _ID (_INTEGER | _K4)
#  include "derivs.inc"
#endif
#ifdef _K8
#  define _ID (_INTEGER | _K8)
#  include "derivs.inc"
#endif
#ifdef _K16
#  define _ID (_INTEGER | _K16)
#  include "derivs.inc"
#endif

#ifdef _HP
#  define _ID (_REAL | _HP)
#  include "derivs.inc"
#  define _ID (_COMPLEX | _HP)
#  include "derivs.inc"
#endif
#ifdef _SP
#  define _ID (_REAL | _SP)
#  include "derivs.inc"
#  define _ID (_COMPLEX | _SP)
#  include "derivs.inc"
#endif
#ifdef _DP
#  define _ID (_REAL | _DP)
#  include "derivs.inc"
#  define _ID (_COMPLEX | _DP)
#  include "derivs.inc"
#endif
#ifdef _XDP
#  define _ID (_REAL | _XDP)
#  include "derivs.inc"
#  define _ID (_COMPLEX | _XDP)
#  include "derivs.inc"
#endif
#ifdef _QP
#  define _ID (_REAL | _QP)
#  include "derivs.inc"
#  define _ID (_COMPLEX | _QP)
#  include "derivs.inc"
#endif

#undef _FILE
