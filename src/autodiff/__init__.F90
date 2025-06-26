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
#define _ELEM_TYPE2 _TYPE2(_KIND2)
#define _ELEM_TYPE0 _TYPE0(_KIND0)
#define _CONV(X) _TYPE_CONV(X, kind=_KIND)
#define _CONV1(X) _TYPE_CONV1(X, kind=_KIND1)
#define _CONV2(X) _TYPE_CONV2(X, kind=_KIND2)
#define _CONV0(X) _TYPE_CONV0(X, kind=_KIND0)
#define _LABEL _CAT(_TYPE_LABEL,_KIND_LABEL)
#define _LABEL1 _CAT(_TYPE_LABEL1,_KIND_LABEL1)
#define _LABEL2 _CAT(_TYPE_LABEL2,_KIND_LABEL2)
#define _LABEL0 _CAT(_TYPE_LABEL0,_KIND_LABEL0)
#define _NAME _CAT(_DERIV,_LABEL)
#define _NAME1 _CAT(_DERIV1,_LABEL1)
#define _NAME2 _CAT(_DERIV2,_LABEL2)
#define _NAME0 _CAT(_DERIV0,_LABEL0)
#define _TYPE_UNARY_OP(X) _CAT3(X,_,_NAME)
#define _TYPE_BINARY_OP(X) _CAT5(_NAME,_,X,_,_NAME)
#define _LT_TYPE_BINARY_OP(X) _CAT5(_NAME1,_,X,_,_LABEL2)
#define _RT_TYPE_BINARY_OP(X) _CAT5(_LABEL1,_,X,_,_NAME2)
#define _TYPES_BINARY_OP(X) _CAT5(_NAME1,_,X,_,_NAME2)

module autodiff
    implicit none

    private

#define _DERIV_IDS (_GRAD | _GRADGRAD | _DIVGRAD)

#define _FILE "type.inc"
#define _TYPE_IDS (_INTEGER | _REAL | _COMPLEX)
#include "derivs.inc"
#undef _TYPE_IDS
#undef _FILE

#define _PROC _TYPE_UNARY_OP(_OP)
#define _FILE "mod_proc_decl.inc"
#define _OP kind
#define _TYPE_IDS (_INTEGER | _REAL | _COMPLEX)
#include "iface.inc"
#define _OP sign
#define _TYPE_IDS (_INTEGER | _REAL)
#include "iface.inc"
#define _OP real
#define _TYPE_IDS (_COMPLEX)
#define _NO_PUBLIC
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
#define _OP erf
#define _TYPE_IDS (_REAL)
#include "iface.inc"
#define _OP erfc
#define _TYPE_IDS (_REAL)
#include "iface.inc"
#define _OP erfc_scaled
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
#define _OP atan2
#define _TYPE_IDS (_REAL)
#include "iface.inc"
#undef _PROC
#undef _FILE

#undef _DERIV_IDS


#define _DERIV_IDS1 (_GRAD | _GRADGRAD | _DIVGRAD)
#define _DERIV_IDS2 (_VAL)

#define _FILE "mod_proc_decl.inc"
#define _PROC _CAT4(_OP,_KIND_LABEL2,_,_NAME1)
#define _OP int
#define _TYPE_IDS1 (_INTEGER | _REAL | _COMPLEX)
#define _TYPE_IDS2 (_INTEGER)
#include "ifaces.inc"
#define _OP real
#define _TYPE_IDS1 (_INTEGER | _REAL | _COMPLEX)
#define _TYPE_IDS2 (_REAL)
#include "ifaces.inc"
#define _OP cmplx
#define _TYPE_IDS1 (_INTEGER | _REAL | _COMPLEX)
#define _TYPE_IDS2 (_COMPLEX)
#include "ifaces.inc"
#undef _FILE
#undef _PROC

#undef _DERIV_IDS1
#undef _DERIV_IDS2


#define _DERIV_IDS1 (_VAL | _GRAD | _GRADGRAD | _DIVGRAD)
#define _DERIV_IDS2 (_VAL | _GRAD | _GRADGRAD | _DIVGRAD)

#define _PROC _TYPES_BINARY_OP(_OP_NAME)
#define _FILE "check.inc"
#define _SUBFILE "mod_proc_decl.inc"
#define _OP assignment(=)
#define _OP_NAME assign
#define _TYPE_IDS1 (_INTEGER | _REAL | _COMPLEX)
#define _TYPE_IDS2 (_INTEGER | _REAL | _COMPLEX)
#include "ifaces.inc"
#define _OP operator(+)
#define _OP_NAME add
#define _TYPE_IDS1 (_INTEGER | _REAL | _COMPLEX)
#define _TYPE_IDS2 (_INTEGER | _REAL | _COMPLEX)
#include "ifaces.inc"
#define _OP operator(-)
#define _OP_NAME sub
#define _TYPE_IDS1 (_INTEGER | _REAL | _COMPLEX)
#define _TYPE_IDS2 (_INTEGER | _REAL | _COMPLEX)
#include "ifaces.inc"
#define _OP operator(*)
#define _OP_NAME mul
#define _TYPE_IDS1 (_INTEGER | _REAL | _COMPLEX)
#define _TYPE_IDS2 (_INTEGER | _REAL | _COMPLEX)
#include "ifaces.inc"
#define _OP operator(/)
#define _OP_NAME div
#define _TYPE_IDS1 (_INTEGER | _REAL | _COMPLEX)
#define _TYPE_IDS2 (_INTEGER | _REAL | _COMPLEX)
#include "ifaces.inc"
#define _OP operator(**)
#define _OP_NAME div
#define _TYPE_IDS1 (_INTEGER | _REAL | _COMPLEX)
#define _TYPE_IDS2 (_INTEGER | _REAL | _COMPLEX)
#include "ifaces.inc"
#undef _PROC
#undef _FILE
#undef _SUBFILE

#undef _DERIV_IDS1
#undef _DERIV_IDS2

contains

#define _FILE "proc.inc"
#define _DERIV_IDS (_GRAD | _GRADGRAD | _DIVGRAD)
#define _TYPE_IDS (_INTEGER | _REAL | _COMPLEX)
#include "derivs.inc"
#undef _TYPE_IDS
#undef _DERIV_IDS
#undef _FILE

#define _FILE "conv.inc"
#define _DERIV_IDS1 (_GRAD | _GRADGRAD | _DIVGRAD)
#define _DERIV_IDS2 (_VAL)
#define _TYPE_IDS1 (_INTEGER | _REAL | _COMPLEX)
#define _TYPE_IDS2 (_INTEGER | _REAL)
#include "derivs.inc"
#undef _DERIV_IDS1
#undef _DERIV_IDS2
#undef _TYPE_IDS1
#undef _TYPE_IDS2
#undef _FILE

#define _FILE "cmplx.inc"
#define _DERIV_IDS1 (_GRAD | _GRADGRAD | _DIVGRAD)
#define _DERIV_IDS2 (_VAL)
#define _TYPE_IDS1 (_COMPLEX)
#define _TYPE_IDS2 (_COMPLEX)
#include "derivs.inc"
#undef _DERIV_IDS1
#undef _DERIV_IDS2
#undef _TYPE_IDS1
#undef _TYPE_IDS2
#undef _FILE

#define _FILE "cmplx2.inc"
#define _DERIV_IDS1 (_GRAD | _GRADGRAD | _DIVGRAD)
#define _DERIV_IDS2 (_VAL)
#define _TYPE_IDS1 (_INTEGER | _REAL)
#define _TYPE_IDS2 (_COMPLEX)
#include "derivs.inc"
#undef _DERIV_IDS1
#undef _DERIV_IDS2
#undef _TYPE_IDS1
#undef _TYPE_IDS2
#undef _FILE

#define _FILE "check.inc"
#define _SUBFILE "procs.inc"
#define _DERIV_IDS1 (_VAL | _GRAD | _GRADGRAD | _DIVGRAD)
#define _DERIV_IDS2 (_VAL | _GRAD | _GRADGRAD | _DIVGRAD)
#define _TYPE_IDS1 (_INTEGER | _REAL | _COMPLEX)
#define _TYPE_IDS2 (_INTEGER | _REAL | _COMPLEX)
#include "derivs.inc"
#undef _DERIV_IDS1
#undef _DERIV_IDS2
#undef _TYPE_IDS1
#undef _TYPE_IDS2
#undef _FILE
#undef _SUBFILE

end module autodiff
