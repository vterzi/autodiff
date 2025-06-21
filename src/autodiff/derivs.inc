#if ( \
    (defined(_TYPE_IDS1) && defined(_TYPE_IDS2)) \
    && !(defined(_DERIV_ID1) && defined(_DERIV_ID2)) \
)
#  define _DERIV_ID2 _DERIV_ID
#  define _DERIV2 _DERIV
#  define _DERIV_ID1 _GRAD
#  define _DERIV1 Grad
#  include "derivs.inc"
#  undef _DERIV_ID1
#  undef _DERIV1
#  define _DERIV_ID1 _GRADGRAD
#  define _DERIV1 Gradgrad
#  include "derivs.inc"
#  undef _DERIV_ID1
#  undef _DERIV1
#  define _DERIV_ID1 _DIVGRAD
#  define _DERIV1 Divgrad
#  include "derivs.inc"
#  undef _DERIV_ID1
#  undef _DERIV1
#  undef _DERIV_ID2
#  undef _DERIV2
#elif defined(_TYPE_IDS) || (defined(_DERIV_ID1) && defined(_DERIV_ID2))
#  define _DERIV_ID _GRAD
#  define _DERIV Grad
#  include "types.inc"
#  undef _DERIV_ID
#  undef _DERIV
#  define _DERIV_ID _GRADGRAD
#  define _DERIV Gradgrad
#  include "types.inc"
#  undef _DERIV_ID
#  undef _DERIV
#  define _DERIV_ID _DIVGRAD
#  define _DERIV Divgrad
#  include "types.inc"
#  undef _DERIV_ID
#  undef _DERIV
#endif
