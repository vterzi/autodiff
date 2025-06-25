#if ( \
    ((_DERIV_ID1 | _TYPE_ID1 | _KIND1) != (_DERIV_ID2 | _TYPE_ID2 | _KIND2)) \
    && ((_DERIV_ID1 != _VAL) || (_DERIV_ID2 != _VAL)) \
)
#  include _SUBFILE
#endif
