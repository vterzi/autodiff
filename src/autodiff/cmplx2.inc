#define _PROC _CAT4(cmplx,_KIND_LABEL2,_,_NAME1)
elemental function _PROC(x, y, kind) result(r)
    class(_NAME1), intent(in) :: x
#if _KIND2 == _DEFAULT_KIND2
    class(_NAME1), intent(in), optional :: y
    _ELEM_TYPE2, intent(in), optional :: kind
#else
    class(_NAME1), intent(in) :: y
    _ELEM_TYPE2, intent(in) :: kind
#endif
    type(_CAT(_DERIV1,_LABEL2)) :: r

    r%v = cmplx(x%v, y%v, _KIND2)
    r%g = cmplx(x%g, y%g, _KIND2)
#if _DERIV1 == _GRADGRAD
    r%gg = cmplx(x%gg, y%gg, _KIND2)
#elif _DERIV1 == _DIVGRAD
    r%dg = cmplx(x%dg, y%dg, _KIND2)
#endif
end function _PROC
#undef _PROC
