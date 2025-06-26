#define _PROC _CAT4(cmplx,_KIND_LABEL2,_,_NAME1)
elemental function _PROC(x, kind) result(r)
    class(_NAME1), intent(in) :: x
#if _KIND2 == _DEFAULT_KIND2
    _ELEM_TYPE2, intent(in), optional :: kind
#else
    _ELEM_TYPE2, intent(in) :: kind
#endif
    type(_CAT(_DERIV1,_LABEL2)) :: r

    r = x
end function _PROC
#undef _PROC
