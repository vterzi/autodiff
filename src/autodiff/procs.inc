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
elemental subroutine _PROC(arg1, arg2)
    _ARG_TYPE1, intent(inout) :: arg1
    _ARG_TYPE2, intent(in) :: arg2

#if _DERIV_ID1 == _GRADGRAD
    integer :: n
#endif

#if (_DERIV_ID1 != _VAL) && (_DERIV_ID2 == _VAL)
    arg1%val = _CONV1(arg2)
    if (allocated(arg1%grad)) deallocate(arg1%grad)
    allocate(arg1%grad(0))
#elif (_DERIV_ID1 == _VAL) && (_DERIV_ID2 != _VAL)
    arg1 = _CONV1(arg2%val)
#else
    arg1%val = _CONV1(arg2%val)
    arg1%grad = _CONV1(arg2%grad)
#endif
#if (_DERIV_ID1 == _GRADGRAD) && (_DERIV_ID2 == _GRADGRAD)
    arg1%gradgrad = _CONV1(arg2%gradgrad)
#elif (_DERIV_ID1 == _DIVGRAD) && (_DERIV_ID2 == _DIVGRAD)
    arg1%divgrad = _CONV1(arg2%divgrad)
#elif (_DERIV_ID1 == _DIVGRAD) && (_DERIV_ID2 == _GRADGRAD)
    arg1%divgrad = _CONV1(arg2%get_divgrad())
#elif _DERIV_ID1 == _GRADGRAD
    if (allocated(arg1%gradgrad)) deallocate(arg1%gradgrad)
    n = size(arg1%grad)
    allocate(arg1%gradgrad(n * (n + 1) / 2))
    arg1%gradgrad = 0
#elif _DERIV_ID1 == _DIVGRAD
    arg1%divgrad = 0
#endif
end subroutine _PROC
#undef _PROC


#define _PROC _TYPES_BINARY_OP(add)
elemental function _PROC(arg1, arg2) result(res)
    _ARG_TYPE1, intent(in) :: arg1
    _ARG_TYPE2, intent(in) :: arg2
    _RES_TYPE :: res

#if (_DERIV_ID1 != _VAL) && (_DERIV_ID2 != _VAL)
    _RES_TYPE :: temp
#endif

#if (_DERIV_ID1 != _VAL) && (_DERIV_ID2 == _VAL)
    res = arg1
    res%val = res%val + _CONV0(arg2)
#elif (_DERIV_ID1 == _VAL) && (_DERIV_ID2 != _VAL)
    res = arg2
    res%val = _CONV0(arg1) + res%val
#else
    res = arg1
    temp = arg2
    res = res + temp
#endif
end function _PROC
#undef _PROC


#define _PROC _TYPES_BINARY_OP(sub)
elemental function _PROC(arg1, arg2) result(res)
    _ARG_TYPE1, intent(in) :: arg1
    _ARG_TYPE2, intent(in) :: arg2
    _RES_TYPE :: res

#if (_DERIV_ID1 != _VAL) && (_DERIV_ID2 != _VAL)
    _RES_TYPE :: temp
#endif

#if (_DERIV_ID1 != _VAL) && (_DERIV_ID2 == _VAL)
    res = arg1
    res%val = res%val - _CONV0(arg2)
#elif (_DERIV_ID1 == _VAL) && (_DERIV_ID2 != _VAL)
    res = arg2
    res%val = _CONV0(arg1) - res%val
#else
    res = arg1
    temp = arg2
    res = res - temp
#endif
end function _PROC
#undef _PROC


#define _PROC _TYPES_BINARY_OP(mul)
elemental function _PROC(arg1, arg2) result(res)
    _ARG_TYPE1, intent(in) :: arg1
    _ARG_TYPE2, intent(in) :: arg2
    _RES_TYPE :: res

#if (_DERIV_ID1 != _VAL) && (_DERIV_ID2 != _VAL)
    _RES_TYPE :: temp
#else
    _ELEM_TYPE0 :: temp
#endif

#if (_DERIV_ID1 != _VAL) && (_DERIV_ID2 == _VAL)
    res = arg1
    temp = _CONV0(arg2)
    res%val = res%val * temp
    res%grad = res%grad * temp
#  if _DERIV_ID0 == _GRADGRAD
    res%gradgrad = res%gradgrad * temp
#  elif _DERIV_ID0 == _DIVGRAD
    res%divgrad = res%divgrad * temp
#  endif
#elif (_DERIV_ID1 == _VAL) && (_DERIV_ID2 != _VAL)
    temp = _CONV0(arg1)
    res = arg2
    res%val = temp * res%val
    res%grad = temp * res%grad
#  if _DERIV_ID0 == _GRADGRAD
    res%gradgrad = temp * res%gradgrad
#  elif _DERIV_ID0 == _DIVGRAD
    res%divgrad = temp * res%divgrad
#  endif
#else
    res = arg1
    temp = arg2
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
