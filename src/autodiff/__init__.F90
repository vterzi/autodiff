#include "cat.inc"
#include "init.inc"

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
#include "iface_c.inc"

#define _OP aimag
#include "iface_c.inc"

#define _OP conjg
#include "iface_c.inc"

#define _OP abs
#include "iface_irc.inc"

#define _OP sqrt
#include "iface_rc.inc"

#define _OP exp
#include "iface_rc.inc"

#define _OP log
#include "iface_rc.inc"

#define _OP log10
#include "iface_r.inc"

#define _OP sin
#include "iface_rc.inc"

#define _OP cos
#include "iface_rc.inc"

#define _OP tan
#include "iface_rc.inc"

#define _OP asin
#include "iface_rc.inc"

#define _OP acos
#include "iface_rc.inc"

#define _OP atan
#include "iface_rc.inc"

#define _OP sinh
#include "iface_rc.inc"

#define _OP cosh
#include "iface_rc.inc"

#define _OP tanh
#include "iface_rc.inc"

#define _OP asinh
#include "iface_rc.inc"

#define _OP acosh
#include "iface_rc.inc"

#define _OP atanh
#include "iface_rc.inc"

#undef _PROC
#undef _FILE

contains

#define _FILE "procs.inc"
#include "type-kinds.inc"

end module autodiff
