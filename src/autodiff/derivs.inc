#if ( \
    (defined(_DERIV_IDS1) && defined(_DERIV_IDS2)) \
    && !(defined(_DERIV_ID1) && defined(_DERIV_ID2)) \
)
#  define _DERIV_IDS _DERIV_IDS2
#  define _DERIV_ID2 _DERIV_ID
#  define _DERIV2 _DERIV
#  if _DERIV_IDS1 & _VAL
#    define _DERIV_ID1 _VAL
#    define _DERIV1
#    include "derivs.inc"
#    undef _DERIV_ID1
#    undef _DERIV1
#  endif
#  if _DERIV_IDS1 & _GRAD
#    define _DERIV_ID1 _GRAD
#    define _DERIV1 Grad
#    include "derivs.inc"
#    undef _DERIV_ID1
#    undef _DERIV1
#  endif
#  if _DERIV_IDS1 & _GRADGRAD
#    define _DERIV_ID1 _GRADGRAD
#    define _DERIV1 Gradgrad
#    include "derivs.inc"
#    undef _DERIV_ID1
#    undef _DERIV1
#  endif
#  if _DERIV_IDS1 & _DIVGRAD
#    define _DERIV_ID1 _DIVGRAD
#    define _DERIV1 Divgrad
#    include "derivs.inc"
#    undef _DERIV_ID1
#    undef _DERIV1
#  endif
#  undef _DERIV_IDS
#  undef _DERIV_ID2
#  undef _DERIV2
#elif defined(_DERIV_IDS)
#  if _DERIV_IDS & _VAL
#    define _DERIV_ID _VAL
#    define _DERIV
#    include "types.inc"
#    undef _DERIV_ID
#    undef _DERIV
#  endif
#  if _DERIV_IDS & _GRAD
#    define _DERIV_ID _GRAD
#    define _DERIV Grad
#    include "types.inc"
#    undef _DERIV_ID
#    undef _DERIV
#  endif
#  if _DERIV_IDS & _GRADGRAD
#    define _DERIV_ID _GRADGRAD
#    define _DERIV Gradgrad
#    include "types.inc"
#    undef _DERIV_ID
#    undef _DERIV
#  endif
#  if _DERIV_IDS & _DIVGRAD
#    define _DERIV_ID _DIVGRAD
#    define _DERIV Divgrad
#    include "types.inc"
#    undef _DERIV_ID
#    undef _DERIV
#  endif
#endif
