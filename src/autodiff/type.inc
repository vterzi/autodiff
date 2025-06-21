type, public :: _NAME
    _ELEM_TYPE :: val
    _ELEM_TYPE, allocatable :: grad(:)
#if defined(_GRADGRAD)
    _ELEM_TYPE, allocatable :: gradgrad(:)
#elif defined(_DIVGRAD)
    _ELEM_TYPE :: divgrad
#endif
contains
#define _PROC _BINARY_TYPE_OP(eq)
#define _OP operator(==)
#include "type_generic.inc"
#define _PROC _BINARY_TYPE_OP(ne)
#define _OP operator(/=)
#include "type_generic.inc"
#define _PROC _UNARY_TYPE_OP(pos)
#define _OP operator(+)
#include "type_generic.inc"
#define _PROC _UNARY_TYPE_OP(neg)
#define _OP operator(-)
#include "type_generic.inc"
#define _PROC _BINARY_TYPE_OP(add)
#define _OP operator(+)
#include "type_generic.inc"
#define _PROC _BINARY_TYPE_OP(sub)
#define _OP operator(-)
#include "type_generic.inc"
#define _PROC _BINARY_TYPE_OP(mul)
#define _OP operator(*)
#include "type_generic.inc"
#if _CLASS_ID == _CLASS_P
#  define _PROC _BINARY_TYPE_OP(div)
#  define _OP operator(/)
#  include "type_generic.inc"
#  define _PROC _BINARY_TYPE_OP(pow)
#  define _OP operator(**)
#  include "type_generic.inc"
#endif
end type _NAME
