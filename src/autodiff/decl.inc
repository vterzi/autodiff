#if defined(_GRADGRAD)
#  define _PREFIX Gradgrad
#elif defined(_DIVGRAD)
#  define _PREFIX Divgrad
#else
#  define _PREFIX Grad
#endif

#define _NAME _CAT3(_PREFIX,_TYPE_LABEL,_KIND_LABEL)
#define _UNARY(X) _CAT3(X,_,_NAME)
#define _BINARY(X) _CAT5(_NAME,_,X,_,_NAME)


type, public :: _NAME
    _ELEM_TYPE :: val
    _ELEM_TYPE, allocatable :: grad(:)
#if defined(_GRADGRAD)
    _ELEM_TYPE, allocatable :: gradgrad(:)
#elif defined(_DIVGRAD)
    _ELEM_TYPE :: divgrad
#endif
contains
#define _PROC _BINARY(assign)
    procedure, private :: _PROC
    generic :: assignment(=) => _PROC
#undef _PROC
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
#define _PROC _BINARY(div)
    procedure, private :: _PROC
    generic :: operator(/) => _PROC
#undef _PROC
#define _PROC _BINARY(pow)
    procedure, private :: _PROC
    generic :: operator(**) => _PROC
#undef _PROC
end type _NAME


#undef _PREFIX
#undef _NAME
#undef _UNARY
#undef _BINARY

#undef _GRADGRAD
#undef _DIVGRAD
