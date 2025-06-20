#define _NAME _CAT3(_DERIV,_TYPE_LABEL,_KIND_LABEL)
#define _UNARY(X) _CAT3(X,_,_NAME)
#define _BINARY(X) _CAT5(_NAME,_,X,_,_NAME)

module autodiff
    use, intrinsic :: ieee_arithmetic, only: ieee_value, IEEE_QUIET_NAN

    implicit none

    private

#define _FILE "type.inc"
#include "type-kinds.inc"

#define _PROC(X) _CAT5(_OP,_,_DERIV,_TYPE_LABEL,X)
#define _FILE "decl.inc"

#define _OP real
    public :: _OP
    interface _OP
#define _ID _COMPLEX
#include "derivs.inc"
    end interface _OP
#undef _OP

#define _OP aimag
    public :: _OP
    interface _OP
#define _ID _COMPLEX
#include "derivs.inc"
    end interface _OP
#undef _OP

#define _OP conjg
    public :: _OP
    interface _OP
#define _ID _COMPLEX
#include "derivs.inc"
    end interface _OP
#undef _OP

#define _OP abs
    public :: _OP
    interface _OP
#define _ID _INTEGER
#include "derivs.inc"
#define _ID _REAL
#include "derivs.inc"
#define _ID _COMPLEX
#include "derivs.inc"
    end interface _OP
#undef _OP

#define _OP sqrt
    public :: _OP
    interface _OP
#define _ID _REAL
#include "derivs.inc"
#define _ID _COMPLEX
#include "derivs.inc"
    end interface _OP
#undef _OP

#define _OP exp
    public :: _OP
    interface _OP
#define _ID _REAL
#include "derivs.inc"
#define _ID _COMPLEX
#include "derivs.inc"
    end interface _OP
#undef _OP

#define _OP log
    public :: _OP
    interface _OP
#define _ID _REAL
#include "derivs.inc"
#define _ID _COMPLEX
#include "derivs.inc"
    end interface _OP
#undef _OP

#define _OP log10
    public :: _OP
    interface _OP
#define _ID _REAL
#include "derivs.inc"
    end interface _OP
#undef _OP

#define _OP sin
    public :: _OP
    interface _OP
#define _ID _REAL
#include "derivs.inc"
#define _ID _COMPLEX
#include "derivs.inc"
    end interface _OP
#undef _OP

#define _OP cos
    public :: _OP
    interface _OP
#define _ID _REAL
#include "derivs.inc"
#define _ID _COMPLEX
#include "derivs.inc"
    end interface _OP
#undef _OP

#define _OP tan
    public :: _OP
    interface _OP
#define _ID _REAL
#include "derivs.inc"
#define _ID _COMPLEX
#include "derivs.inc"
    end interface _OP
#undef _OP

#undef _PROC
#undef _FILE

contains

#define _FILE "procs.inc"
#include "type-kinds.inc"

end module autodiff
