type, public :: _NAME
    _ELEM_TYPE :: val
    _ELEM_TYPE, allocatable :: grad(:)
#if defined(_GRADGRAD)
    _ELEM_TYPE, allocatable :: gradgrad(:)
#elif defined(_DIVGRAD)
    _ELEM_TYPE :: divgrad
#endif
contains
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
