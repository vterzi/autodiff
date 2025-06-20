#define _NAME _CAT3(_DERIV,_TYPE_LABEL,_KIND_LABEL)
#define _UNARY(X) _CAT3(X,_,_NAME)
#define _BINARY(X) _CAT5(_NAME,_,X,_,_NAME)

module autodiff
    implicit none

    private

    ! logical, integer (K = kind)
#ifdef _K1
    integer, parameter :: K1 = _K1
#endif
#ifdef _K2
    integer, parameter :: K2 = _K2
#endif
#ifdef _K4
    integer, parameter :: K4 = _K4
#endif
#ifdef _K8
    integer, parameter :: K8 = _K8
#endif
#ifdef _K16
    integer, parameter :: K16 = _K16
#endif

    ! real, complex (P = precision)
#ifdef _HP
    ! half
    integer, parameter :: HP = _HP
#endif
#ifdef _SP
    ! single
    integer, parameter :: SP = _SP
#endif
#ifdef _DP
    ! double
    integer, parameter :: DP = _DP
#endif
#ifdef _XDP
    ! extended double
    integer, parameter :: XDP = _XDP
#endif
#ifdef _QP
    ! quadruple
    integer, parameter :: QP = _QP
#endif

    ! -------------------------------------------------------------------------

#define _FILE "decl.inc"
#include "types.inc"

contains

#define _FILE "def.inc"
#include "types.inc"

end module autodiff
