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
#define _TYPES_BINARY_OP(X) _CAT5(_NAME1,_,X,_,_NAME2)

module autodiff
    implicit none

    private

#define _FILE "type.inc"
#define _DERIV_IDS (_GRAD | _GRADGRAD | _DIVGRAD)
#define _TYPE_IDS (_INTEGER | _REAL | _COMPLEX)
#include "derivs.inc"
#undef _TYPE_IDS
#undef _DERIV_IDS
#undef _FILE


    public :: operator(//)
#define _FILE "decl.inc"
#define _DERIV_IDS (_GRAD | _GRADGRAD | _DIVGRAD)
#define _TYPE_IDS (_INTEGER | _REAL | _COMPLEX)
#define _PROC _CAT(I_cat_,_NAME)
#define _OP operator(//)
#define _NO_PUBLIC
#include "iface.inc"
#undef _PROC
#define _PROC _CAT(_NAME,_cat_I)
#define _OP operator(//)
#define _NO_PUBLIC
#include "iface.inc"
#undef _PROC
#undef _TYPE_IDS
#undef _DERIV_IDS
#undef _FILE


#define _PROC _TYPE_UNARY_OP(_OP)
#define _FILE "decl.inc"
#define _DERIV_IDS (_GRAD | _GRADGRAD | _DIVGRAD)

#define _TYPE_IDS (_INTEGER | _REAL)
#define _OP sign
#include "iface.inc"
#undef _TYPE_IDS

#define _TYPE_IDS (_COMPLEX)
#define _OP real
#define _NO_PUBLIC
#include "iface.inc"
#define _OP aimag
#include "iface.inc"
#define _OP conjg
#include "iface.inc"
#undef _TYPE_IDS

#define _TYPE_IDS (_INTEGER | _REAL | _COMPLEX)
#define _OP kind
#include "iface.inc"
#define _OP abs
#include "iface.inc"
#undef _TYPE_IDS

#define _TYPE_IDS (_REAL | _COMPLEX)
#define _OP sqrt
#include "iface.inc"
#define _OP exp
#include "iface.inc"
#define _OP log
#include "iface.inc"
#define _OP sin
#include "iface.inc"
#define _OP cos
#include "iface.inc"
#define _OP tan
#include "iface.inc"
#define _OP asin
#include "iface.inc"
#define _OP acos
#include "iface.inc"
#define _OP atan
#include "iface.inc"
#define _OP sinh
#include "iface.inc"
#define _OP cosh
#include "iface.inc"
#define _OP tanh
#include "iface.inc"
#define _OP asinh
#include "iface.inc"
#define _OP acosh
#include "iface.inc"
#define _OP atanh
#include "iface.inc"
#undef _TYPE_IDS

#define _TYPE_IDS (_REAL)
#define _OP atan2
#include "iface.inc"
#define _OP hypot
#include "iface.inc"
#define _OP log10
#include "iface.inc"
#define _OP erf
#include "iface.inc"
#define _OP erfc
#include "iface.inc"
#define _OP erfc_scaled
#include "iface.inc"
#undef _TYPE_IDS

#undef _DERIV_IDS
#undef _FILE
#undef _PROC


#define _PROC _CAT4(_OP,_KIND_LABEL2,_,_NAME1)
#define _FILE "decl.inc"
#define _DERIV_IDS1 (_GRAD | _GRADGRAD | _DIVGRAD)
#define _TYPE_IDS1 (_INTEGER | _REAL | _COMPLEX)
#define _DERIV_IDS2 (_VAL)

#define _TYPE_IDS2 (_INTEGER)
#define _OP int
#include "iface.inc"
#undef _TYPE_IDS2

#define _TYPE_IDS2 (_REAL)
#define _OP real
#include "iface.inc"
#undef _TYPE_IDS2

#define _TYPE_IDS2 (_COMPLEX)
#define _OP cmplx
#include "iface.inc"
#undef _TYPE_IDS2

#undef _DERIV_IDS2
#undef _TYPE_IDS1
#undef _DERIV_IDS1
#undef _FILE
#undef _PROC


#define _PROC _TYPES_BINARY_OP(_OP_NAME)
#define _SUBFILE "decl.inc"
#define _FILE "check.inc"
#define _DERIV_IDS1 (_VAL | _GRAD | _GRADGRAD | _DIVGRAD)
#define _TYPE_IDS1 (_INTEGER | _REAL | _COMPLEX)
#define _DERIV_IDS2 (_VAL | _GRAD | _GRADGRAD | _DIVGRAD)
#define _TYPE_IDS2 (_INTEGER | _REAL | _COMPLEX)
#define _OP assignment(=)
#define _OP_NAME assign
#include "iface.inc"
#define _OP operator(==)
#define _OP_NAME eq
#include "iface.inc"
#define _OP operator(/=)
#define _OP_NAME ne
#include "iface.inc"
#define _OP operator(+)
#define _OP_NAME add
#include "iface.inc"
#define _OP operator(-)
#define _OP_NAME sub
#include "iface.inc"
#define _OP operator(*)
#define _OP_NAME mul
#include "iface.inc"
#define _OP operator(/)
#define _OP_NAME div
#include "iface.inc"
#define _OP operator(**)
#define _OP_NAME pow
#include "iface.inc"
#undef _TYPE_IDS2
#undef _DERIV_IDS2
#undef _TYPE_IDS1
#undef _DERIV_IDS1
#undef _FILE
#undef _SUBFILE
#undef _PROC

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
#define _TYPE_IDS1 (_INTEGER | _REAL | _COMPLEX)
#define _DERIV_IDS2 (_VAL)
#define _TYPE_IDS2 (_INTEGER | _REAL)
#include "derivs.inc"
#undef _TYPE_IDS2
#undef _DERIV_IDS2
#undef _TYPE_IDS1
#undef _DERIV_IDS1
#undef _FILE

#define _FILE "cmplx.inc"
#define _DERIV_IDS1 (_GRAD | _GRADGRAD | _DIVGRAD)
#define _TYPE_IDS1 (_COMPLEX)
#define _DERIV_IDS2 (_VAL)
#define _TYPE_IDS2 (_COMPLEX)
#include "derivs.inc"
#undef _TYPE_IDS2
#undef _DERIV_IDS2
#undef _TYPE_IDS1
#undef _DERIV_IDS1
#undef _FILE

#define _FILE "cmplx2.inc"
#define _DERIV_IDS1 (_GRAD | _GRADGRAD | _DIVGRAD)
#define _TYPE_IDS1 (_INTEGER | _REAL)
#define _DERIV_IDS2 (_VAL)
#define _TYPE_IDS2 (_COMPLEX)
#include "derivs.inc"
#undef _TYPE_IDS2
#undef _DERIV_IDS2
#undef _TYPE_IDS1
#undef _DERIV_IDS1
#undef _FILE

#define _SUBFILE "procs.inc"
#define _FILE "check.inc"
#define _DERIV_IDS1 (_VAL | _GRAD | _GRADGRAD | _DIVGRAD)
#define _TYPE_IDS1 (_INTEGER | _REAL | _COMPLEX)
#define _DERIV_IDS2 (_VAL | _GRAD | _GRADGRAD | _DIVGRAD)
#define _TYPE_IDS2 (_INTEGER | _REAL | _COMPLEX)
#include "derivs.inc"
#undef _TYPE_IDS2
#undef _DERIV_IDS2
#undef _TYPE_IDS1
#undef _DERIV_IDS1
#undef _FILE
#undef _SUBFILE

end module autodiff
