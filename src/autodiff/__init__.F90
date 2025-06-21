#define _PASTE(X) X
#define _CAT(A,B) _PASTE(A)B
#define _CAT3(A,B,C) _CAT(_CAT(A,B),C)
#define _CAT4(A,B,C,D) _CAT(_CAT3(A,B,C),D)
#define _CAT5(A,B,C,D,E) _CAT(_CAT4(A,B,C,D),E)
#define _CAT6(A,B,C,D,E,F) _CAT(_CAT5(A,B,C,D,E),F)
#define _CAT7(A,B,C,D,E,F,G) _CAT(_CAT6(A,B,C,D,E,F),G)
#define _CAT8(A,B,C,D,E,F,G,H) _CAT(_CAT7(A,B,C,D,E,F,G),H)
#define _CAT9(A,B,C,D,E,F,G,H,I) _CAT(_CAT8(A,B,C,D,E,F,G,H),I)

#define _INTEGER (1 << (_KIND_BITS))
#define _REAL (1 << (_KIND_BITS + 1))
#define _COMPLEX (1 << (_KIND_BITS + 2))

#define _ELEM_TYPE _TYPE(_KIND)
#define _NAME _CAT3(_DERIV,_TYPE_LABEL,_KIND_LABEL)
#define _TYPE_UNARY_OP(X) _CAT3(X,_,_NAME)
#define _TYPE_BINARY_OP(X) _CAT5(_NAME,_,X,_,_NAME)

module autodiff
    use, intrinsic :: ieee_arithmetic, only: ieee_value, IEEE_QUIET_NAN

    implicit none

    private

#define _FILE "type.inc"
#define _TYPE_ID _INTEGER
#include "derivs.inc"
#define _TYPE_ID _REAL
#include "derivs.inc"
#define _TYPE_ID _COMPLEX
#include "derivs.inc"
#undef _FILE

#define _PROC _CAT5(_OP,_,_DERIV,_TYPE_LABEL,_KIND_LABEL)
#define _FILE "mod_proc_decl.inc"
#define _OP real
#define _TYPE_IDS (_COMPLEX)
#include "iface.inc"
#define _OP aimag
#define _TYPE_IDS (_COMPLEX)
#include "iface.inc"
#define _OP conjg
#define _TYPE_IDS (_COMPLEX)
#include "iface.inc"
#define _OP abs
#define _TYPE_IDS (_INTEGER | _REAL | _COMPLEX)
#include "iface.inc"
#define _OP sqrt
#define _TYPE_IDS (_REAL | _COMPLEX)
#include "iface.inc"
#define _OP exp
#define _TYPE_IDS (_REAL | _COMPLEX)
#include "iface.inc"
#define _OP log
#define _TYPE_IDS (_REAL | _COMPLEX)
#include "iface.inc"
#define _OP log10
#define _TYPE_IDS (_REAL)
#include "iface.inc"
#define _OP sin
#define _TYPE_IDS (_REAL | _COMPLEX)
#include "iface.inc"
#define _OP cos
#define _TYPE_IDS (_REAL | _COMPLEX)
#include "iface.inc"
#define _OP tan
#define _TYPE_IDS (_REAL | _COMPLEX)
#include "iface.inc"
#define _OP asin
#define _TYPE_IDS (_REAL | _COMPLEX)
#include "iface.inc"
#define _OP acos
#define _TYPE_IDS (_REAL | _COMPLEX)
#include "iface.inc"
#define _OP atan
#define _TYPE_IDS (_REAL | _COMPLEX)
#include "iface.inc"
#define _OP sinh
#define _TYPE_IDS (_REAL | _COMPLEX)
#include "iface.inc"
#define _OP cosh
#define _TYPE_IDS (_REAL | _COMPLEX)
#include "iface.inc"
#define _OP tanh
#define _TYPE_IDS (_REAL | _COMPLEX)
#include "iface.inc"
#define _OP asinh
#define _TYPE_IDS (_REAL | _COMPLEX)
#include "iface.inc"
#define _OP acosh
#define _TYPE_IDS (_REAL | _COMPLEX)
#include "iface.inc"
#define _OP atanh
#define _TYPE_IDS (_REAL | _COMPLEX)
#include "iface.inc"
#undef _PROC
#undef _FILE

contains

#define _FILE "procs.inc"
#define _TYPE_ID _INTEGER
#include "derivs.inc"
#define _TYPE_ID _REAL
#include "derivs.inc"
#define _TYPE_ID _COMPLEX
#include "derivs.inc"
#undef _FILE

end module autodiff
