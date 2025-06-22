#if !((_DERIV_ID1 == _VAL) && (_DERIV_ID2 == _VAL)) && !( \
    (_DERIV_ID1 == _DERIV_ID2) \
    && (_TYPE_ID1 == _TYPE_ID2) \
    && (_KIND1 == _KIND2) \
)
#  include _SUBFILE
#endif
