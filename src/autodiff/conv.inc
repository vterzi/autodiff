#define _PROC _CAT4(_TYPE_CONV2,_KIND_LABEL2,_,_NAME1)
elemental function _PROC(a, kind) result(r)
    class(_NAME1), intent(in) :: a
#if ( \
    (_KIND2 == _DEFAULT_KIND2) && ( \
        (_TYPE_ID2 == _INTEGER) \
        || ((_TYPE_ID2 == _REAL) && (_TYPE_ID1 != _COMPLEX)) \
    ) \
)
    _ELEM_TYPE2, intent(in), optional :: kind
#else
    _ELEM_TYPE2, intent(in) :: kind
#endif
    type(_CAT(_DERIV1,_LABEL2)) :: r

    r = a
end function _PROC
#undef _PROC
