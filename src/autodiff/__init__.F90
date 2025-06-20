#define _NAME _CAT3(_DERIV,_TYPE_LABEL,_KIND_LABEL)
#define _UNARY(X) _CAT3(X,_,_NAME)
#define _BINARY(X) _CAT5(_NAME,_,X,_,_NAME)

module autodiff
    implicit none

    private

#define _FILE "decl.inc"
#include "types.inc"

contains

#define _FILE "def.inc"
#include "types.inc"

end module autodiff
