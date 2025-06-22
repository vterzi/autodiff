#if _DERIV_ID1 >= _DERIV_ID2
#  define _DERIV_ID0 _DERIV_ID1
#  define _DERIV0 _DERIV1
#else
#  define _DERIV_ID0 _DERIV_ID2
#  define _DERIV0 _DERIV2
#endif
#if _TYPE_ID1 >= _TYPE_ID2
#  define _TYPE_ID0 _TYPE_ID1
#  define _TYPE0 _TYPE1
#  define _TYPE_CONV0 _TYPE_CONV1
#  define _TYPE_LABEL0 _TYPE_LABEL1
#else
#  define _TYPE_ID0 _TYPE_ID2
#  define _TYPE0 _TYPE2
#  define _TYPE_CONV0 _TYPE_CONV2
#  define _TYPE_LABEL0 _TYPE_LABEL2
#endif
#if ( \
    ((_TYPE_ID1 != _INTEGER) && (_TYPE_ID2 == _INTEGER)) \
    || ( \
        (_KIND1 >= _KIND2) \
        && ((_TYPE_ID1 == _INTEGER) == (_TYPE_ID2 == _INTEGER)) \
    ) \
)
#  define _KIND0 _KIND1
#  define _KIND_LABEL0 _KIND_LABEL1
#else
#  define _KIND0 _KIND2
#  define _KIND_LABEL0 _KIND_LABEL2
#endif

#if _DERIV_ID1 != _VAL
#  define _ARG_TYPE1 type(_NAME1)
#else
#  define _ARG_TYPE1 _ELEM_TYPE1
#endif
#if _DERIV_ID2 != _VAL
#  define _ARG_TYPE2 type(_NAME2)
#else
#  define _ARG_TYPE2 _ELEM_TYPE2
#endif
#define _RES_TYPE type(_NAME0)


#define _PROC _TYPES_BINARY_OP(assign)
elemental subroutine _PROC(this, that)
    _ARG_TYPE1, intent(inout) :: this
    _ARG_TYPE2, intent(in) :: that

#if _DERIV_ID1 == _GRADGRAD
    integer :: n
#endif

#if (_DERIV_ID1 != _VAL) && (_DERIV_ID2 == _VAL)
    this%val = _CONV1(that)
    if (allocated(this%grad)) deallocate(this%grad)
    allocate(this%grad(0))
#elif (_DERIV_ID1 == _VAL) && (_DERIV_ID2 != _VAL)
    this = _CONV1(that%val)
#else
    this%val = _CONV1(that%val)
    this%grad = _CONV1(that%grad)
#endif
#if (_DERIV_ID1 == _GRADGRAD) && (_DERIV_ID2 == _GRADGRAD)
    this%gradgrad = _CONV1(that%gradgrad)
#elif (_DERIV_ID1 == _DIVGRAD) && (_DERIV_ID2 == _DIVGRAD)
    this%divgrad = _CONV1(that%divgrad)
#elif (_DERIV_ID1 == _DIVGRAD) && (_DERIV_ID2 == _GRADGRAD)
    this%divgrad = _CONV1(that%get_divgrad())
#elif _DERIV_ID1 == _GRADGRAD
    if (allocated(this%gradgrad)) deallocate(this%gradgrad)
    n = size(this%grad)
    allocate(this%gradgrad(n * (n + 1) / 2))
    this%gradgrad = 0
#elif _DERIV_ID1 == _DIVGRAD
    this%divgrad = 0
#endif
end subroutine _PROC
#undef _PROC


#define _PROC _TYPES_BINARY_OP(add)
elemental function _PROC(this, that) result(res)
    _ARG_TYPE1, intent(in) :: this
    _ARG_TYPE2, intent(in) :: that
    _RES_TYPE :: res

#if (_DERIV_ID1 != _VAL) && (_DERIV_ID2 != _VAL)
    _RES_TYPE :: temp
#endif

#if (_DERIV_ID1 != _VAL) && (_DERIV_ID2 == _VAL)
    res = this
    res%val = res%val + _CONV0(that)
#elif (_DERIV_ID1 == _VAL) && (_DERIV_ID2 != _VAL)
    res = that
    res%val = _CONV0(this) + res%val
#else
    res = this
    temp = that
    res = res + temp
#endif
end function _PROC
#undef _PROC


#define _PROC _TYPES_BINARY_OP(sub)
elemental function _PROC(this, that) result(res)
    _ARG_TYPE1, intent(in) :: this
    _ARG_TYPE2, intent(in) :: that
    _RES_TYPE :: res

#if (_DERIV_ID1 != _VAL) && (_DERIV_ID2 != _VAL)
    _RES_TYPE :: temp
#endif

#if (_DERIV_ID1 != _VAL) && (_DERIV_ID2 == _VAL)
    res = this
    res%val = res%val - _CONV0(that)
#elif (_DERIV_ID1 == _VAL) && (_DERIV_ID2 != _VAL)
    res = that
    res%val = _CONV0(this) - res%val
#else
    res = this
    temp = that
    res = res - temp
#endif
end function _PROC
#undef _PROC


#define _PROC _TYPES_BINARY_OP(mul)
elemental function _PROC(this, that) result(res)
    _ARG_TYPE1, intent(in) :: this
    _ARG_TYPE2, intent(in) :: that
    _RES_TYPE :: res

#if (_DERIV_ID1 != _VAL) && (_DERIV_ID2 != _VAL)
    _RES_TYPE :: temp
#else
    _ELEM_TYPE0 :: temp
#endif

#if (_DERIV_ID1 != _VAL) && (_DERIV_ID2 == _VAL)
    res = this
    temp = _CONV0(that)
    res%val = res%val * temp
    res%grad = res%grad * temp
#  if _DERIV_ID0 == _GRADGRAD
    res%gradgrad = res%gradgrad * temp
#  elif _DERIV_ID0 == _DIVGRAD
    res%divgrad = res%divgrad * temp
#  endif
#elif (_DERIV_ID1 == _VAL) && (_DERIV_ID2 != _VAL)
    temp = _CONV0(this)
    res = that
    res%val = temp * res%val
    res%grad = temp * res%grad
#  if _DERIV_ID0 == _GRADGRAD
    res%gradgrad = temp * res%gradgrad
#  elif _DERIV_ID0 == _DIVGRAD
    res%divgrad = temp * res%divgrad
#  endif
#else
    res = this
    temp = that
    res = res * temp
#endif
end function _PROC
#undef _PROC


#undef _DERIV_ID0
#undef _DERIV0
#undef _TYPE_ID0
#undef _TYPE0
#undef _TYPE_CONV0
#undef _TYPE_LABEL0
#undef _KIND0
#undef _KIND_LABEL0
#undef _ARG_TYPE1
#undef _ARG_TYPE2
#undef _RES_TYPE
