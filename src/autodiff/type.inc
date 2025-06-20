type, public :: _NAME
    _ELEM_TYPE :: val
    _ELEM_TYPE, allocatable :: grad(:)
#if defined(_GRADGRAD)
    _ELEM_TYPE, allocatable :: gradgrad(:)
#elif defined(_DIVGRAD)
    _ELEM_TYPE :: divgrad
#endif
contains
#define _PROC _BINARY(eq)
    procedure, private :: _PROC
    generic :: operator(==) => _PROC
#undef _PROC
#define _PROC _BINARY(ne)
    procedure, private :: _PROC
    generic :: operator(/=) => _PROC
#undef _PROC
#define _PROC _UNARY(pos)
    procedure, private :: _PROC
    generic :: operator(+) => _PROC
#undef _PROC
#define _PROC _UNARY(neg)
    procedure, private :: _PROC
    generic :: operator(-) => _PROC
#undef _PROC
#define _PROC _BINARY(add)
    procedure, private :: _PROC
    generic :: operator(+) => _PROC
#undef _PROC
#define _PROC _BINARY(sub)
    procedure, private :: _PROC
    generic :: operator(-) => _PROC
#undef _PROC
#define _PROC _BINARY(mul)
    procedure, private :: _PROC
    generic :: operator(*) => _PROC
#undef _PROC
#if _CLASS_ID == _CLASS_P
#  define _PROC _BINARY(div)
    procedure, private :: _PROC
    generic :: operator(/) => _PROC
#  undef _PROC
#  define _PROC _BINARY(pow)
    procedure, private :: _PROC
    generic :: operator(**) => _PROC
#  undef _PROC
#endif
end type _NAME
