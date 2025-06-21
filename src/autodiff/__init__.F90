#define _PASTE(X) X
#define _CAT(A,B) _PASTE(A)B
#define _CAT3(A,B,C) _CAT(_CAT(A,B),C)
#define _CAT4(A,B,C,D) _CAT(_CAT3(A,B,C),D)
#define _CAT5(A,B,C,D,E) _CAT(_CAT4(A,B,C,D),E)

#define _INTEGER (1 << (_KIND_BITS))
#define _REAL (1 << (_KIND_BITS + 1))
#define _COMPLEX (1 << (_KIND_BITS + 2))

#define _VAL (1 << (_KIND_BITS + 3))
#define _GRAD (1 << (_KIND_BITS + 4))
#define _GRADGRAD (1 << (_KIND_BITS + 5))
#define _DIVGRAD (1 << (_KIND_BITS + 6))

#define _ELEM_TYPE _TYPE(_KIND)
#define _ELEM_TYPE1 _TYPE1(_KIND1)
#define _ELEM_TYPE2 _TYPE1(_KIND2)
#define _CONV(X) _TYPE_CONV(X, kind=_KIND)
#define _CONV1(X) _TYPE_CONV1(X, kind=_KIND1)
#define _CONV2(X) _TYPE_CONV2(X, kind=_KIND2)
#define _LABEL _CAT(_TYPE_LABEL,_KIND_LABEL)
#define _LABEL1 _CAT(_TYPE_LABEL1,_KIND_LABEL1)
#define _LABEL2 _CAT(_TYPE_LABEL2,_KIND_LABEL2)
#define _NAME _CAT(_DERIV,_LABEL)
#define _NAME1 _CAT(_DERIV1,_LABEL1)
#define _NAME2 _CAT(_DERIV2,_LABEL2)
#define _TYPE_UNARY_OP(X) _CAT3(X,_,_NAME)
#define _TYPE_BINARY_OP(X) _CAT5(_NAME,_,X,_,_NAME)
#define _LT_TYPE_BINARY_OP(X) _CAT5(_NAME1,_,X,_,_LABEL2)
#define _RT_TYPE_BINARY_OP(X) _CAT5(_LABEL1,_,X,_,_NAME2)
#define _TYPES_BINARY_OP(X) _CAT5(_NAME1,_,X,_,_NAME2)

module autodiff
    use, intrinsic :: ieee_arithmetic, only: ieee_value, IEEE_QUIET_NAN

    implicit none

    private

#define _FILE "type.inc"
#define _TYPE_IDS (_INTEGER | _REAL | _COMPLEX)
#include "derivs.inc"
#undef _TYPE_IDS
#undef _FILE

#define _PROC _TYPE_UNARY_OP(_OP)
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

#define _PROC _TYPES_BINARY_OP(_OP_NAME)
#define _FILE "mod_procs_decl.inc"

#define _OP assignment(=)
#define _OP_NAME assign
    public :: _OP
    interface _OP
#define _TYPE_IDS1 (_INTEGER | _REAL | _COMPLEX)
#define _TYPE_IDS2 (_INTEGER | _REAL | _COMPLEX)
#include "derivs.inc"
#undef _TYPE_IDS1
#undef _TYPE_IDS2
    end interface _OP
#undef _OP
#undef _OP_NAME

#undef _PROC
#undef _FILE

contains

#define _FILE "proc.inc"
#define _TYPE_IDS (_INTEGER | _REAL | _COMPLEX)
#include "derivs.inc"
#undef _TYPE_IDS
#undef _FILE

#define _FILE "procs.inc"
#define _TYPE_IDS1 (_INTEGER | _REAL | _COMPLEX)
#define _TYPE_IDS2 (_INTEGER | _REAL | _COMPLEX)
#include "derivs.inc"
#undef _TYPE_IDS1
#undef _TYPE_IDS2
#undef _FILE

end module autodiff
