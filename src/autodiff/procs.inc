#if !((_DERIV_ID1 == _VAL) && (_DERIV_ID2 == _VAL)) && !( \
    (_DERIV_ID1 == _DERIV_ID2) \
    && (_TYPE_ID1 == _TYPE_ID2) \
    && (_KIND_ID1 == _KIND_ID2) \
)

#  define _PROC _TYPES_BINARY_OP(assign)
#  if (_DERIV_ID1 != _VAL) && (_DERIV_ID2 != _VAL)
elemental subroutine _PROC(this, that)
    class(_NAME1), intent(inout) :: this
    class(_NAME2), intent(in) :: that

#    if _DERIV_ID1 == _GRADGRAD
    integer :: n
#    endif

    this%val = _CONV1(that%val)
    this%grad = _CONV1(that%grad)
#    if (_DERIV_ID1 == _GRADGRAD) && (_DERIV_ID2 == _GRADGRAD)
    this%gradgrad = _CONV1(that%gradgrad)
#    elif (_DERIV_ID1 == _DIVGRAD) && (_DERIV_ID2 == _DIVGRAD)
    this%divgrad = _CONV1(that%divgrad)
#    elif (_DERIV_ID1 == _DIVGRAD) && (_DERIV_ID2 == _GRADGRAD)
    this%divgrad = _CONV1(that%get_divgrad())
#    elif _DERIV_ID1 == _GRADGRAD
    if (allocated(this%gradgrad)) deallocate(this%gradgrad)
    n = size(this%grad)
    allocate(this%gradgrad(n * (n + 1) / 2))
    this%gradgrad = 0
#    elif _DERIV_ID1 == _DIVGRAD
    this%divgrad = 0
#    endif
end subroutine _PROC
#  elif (_DERIV_ID1 == _VAL) && (_DERIV_ID2 != _VAL)
elemental subroutine _PROC(this, that)
    _ELEM_TYPE1, intent(inout) :: this
    class(_NAME2), intent(in) :: that

    this = _CONV1(that%val)
end subroutine _PROC
#  elif (_DERIV_ID1 != _VAL) && (_DERIV_ID2 == _VAL)
elemental subroutine _PROC(this, that)
    class(_NAME1), intent(inout) :: this
    _ELEM_TYPE2, intent(in) :: that

    this%val = _CONV1(that)
    allocate(this%grad(0))
#    if _DERIV_ID1 == _GRADGRAD
    allocate(this%gradgrad(0))
#    elif _DERIV_ID1 == _DIVGRAD
    this%divgrad = 0
#    endif
end subroutine _PROC
#  endif
#  undef _PROC

#endif
