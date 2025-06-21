type, public :: _NAME
    private
    _ELEM_TYPE :: val
    _ELEM_TYPE, allocatable :: grad(:)
#if defined(_GRADGRAD)
    _ELEM_TYPE, allocatable :: gradgrad(:)
#elif defined(_DIVGRAD)
    _ELEM_TYPE :: divgrad
#endif
contains
#define _PROC(X) procedure :: X => _TYPE_UNARY_OP(X)
    _PROC(get_val)
#undef _PROC
#define _PROC(X) procedure :: X => _TYPE_UNARY_OP(X)
    _PROC(get_grad)
#undef _PROC
#if defined(_GRADGRAD)
#  define _PROC(X) procedure :: X => _TYPE_UNARY_OP(X)
    _PROC(get_gradgrad)
#  undef _PROC
#endif
#if defined(_GRADGRAD) || defined(_DIVGRAD)
#  define _PROC(X) procedure :: X => _TYPE_UNARY_OP(X)
    _PROC(get_divgrad)
#  undef _PROC
#endif
#define _PROC _TYPE_BINARY_OP(eq)
#define _OP operator(==)
#include "type_generic.inc"
#define _PROC _TYPE_BINARY_OP(ne)
#define _OP operator(/=)
#include "type_generic.inc"
#define _PROC _TYPE_UNARY_OP(pos)
#define _OP operator(+)
#include "type_generic.inc"
#define _PROC _TYPE_UNARY_OP(neg)
#define _OP operator(-)
#include "type_generic.inc"
#define _PROC _TYPE_BINARY_OP(add)
#define _OP operator(+)
#include "type_generic.inc"
#define _PROC _TYPE_BINARY_OP(sub)
#define _OP operator(-)
#include "type_generic.inc"
#define _PROC _TYPE_BINARY_OP(mul)
#define _OP operator(*)
#include "type_generic.inc"
#if (_TYPE_ID == _REAL) || (_TYPE_ID == _COMPLEX)
#  define _PROC _TYPE_BINARY_OP(div)
#  define _OP operator(/)
#  include "type_generic.inc"
#  define _PROC _TYPE_BINARY_OP(pow)
#  define _OP operator(**)
#  include "type_generic.inc"
#endif
end type _NAME

interface _NAME
    module procedure :: _TYPE_UNARY_OP(new)
end interface _NAME
