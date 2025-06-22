#if !((_DERIV_ID1 == _VAL) && (_DERIV_ID2 == _VAL)) && !( \
    (_DERIV_ID1 == _DERIV_ID2) \
    && (_TYPE_ID1 == _TYPE_ID2) \
    && (_KIND_ID1 == _KIND_ID2) \
)
#  include "mod_proc_decl.inc"
#endif
