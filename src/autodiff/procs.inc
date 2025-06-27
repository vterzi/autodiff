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
elemental subroutine _PROC(v, expr)
    _ARG_TYPE1, intent(inout) :: v
    _ARG_TYPE2, intent(in) :: expr

#if _DERIV_ID1 == _GRADGRAD
    integer :: n
#endif

#if (_DERIV_ID1 != _VAL) && (_DERIV_ID2 == _VAL)
    v%val = _CONV1(expr)
    if (allocated(v%grad)) deallocate(v%grad)
    allocate(v%grad(0))
#elif (_DERIV_ID1 == _VAL) && (_DERIV_ID2 != _VAL)
    v = _CONV1(expr%val)
#else
    v%val = _CONV1(expr%val)
    v%grad = _CONV1(expr%grad)
#endif
#if (_DERIV_ID1 == _GRADGRAD) && (_DERIV_ID2 == _GRADGRAD)
    v%gradgrad = _CONV1(expr%gradgrad)
#elif (_DERIV_ID1 == _DIVGRAD) && (_DERIV_ID2 == _DIVGRAD)
    v%divgrad = _CONV1(expr%divgrad)
#elif (_DERIV_ID1 == _DIVGRAD) && (_DERIV_ID2 == _GRADGRAD)
    v%divgrad = _CONV1(expr%get_divgrad())
#elif _DERIV_ID1 == _GRADGRAD
    if (allocated(v%gradgrad)) deallocate(v%gradgrad)
    n = size(v%grad)
    allocate(v%gradgrad(n * (n + 1) / 2))
    v%gradgrad = 0
#elif _DERIV_ID1 == _DIVGRAD
    v%divgrad = 0
#endif
end subroutine _PROC
#undef _PROC


#define _PROC _TYPES_BINARY_OP(add)
elemental function _PROC(x, y) result(r)
    _ARG_TYPE1, intent(in) :: x
    _ARG_TYPE2, intent(in) :: y
    _RES_TYPE :: r

#if (_DERIV_ID1 != _VAL) && (_DERIV_ID2 != _VAL)
    _RES_TYPE :: t
#endif

#if (_DERIV_ID1 != _VAL) && (_DERIV_ID2 == _VAL)
    r = x
    r%val = r%val + _CONV0(y)
#elif (_DERIV_ID1 == _VAL) && (_DERIV_ID2 != _VAL)
    r = y
    r%val = _CONV0(x) + r%val
#else
    r = x
    t = y
    r = r + t
#endif
end function _PROC
#undef _PROC


#define _PROC _TYPES_BINARY_OP(sub)
elemental function _PROC(x, y) result(r)
    _ARG_TYPE1, intent(in) :: x
    _ARG_TYPE2, intent(in) :: y
    _RES_TYPE :: r

#if (_DERIV_ID1 != _VAL) && (_DERIV_ID2 != _VAL)
    _RES_TYPE :: t
#endif

#if (_DERIV_ID1 != _VAL) && (_DERIV_ID2 == _VAL)
    r = x
    r%val = r%val - _CONV0(y)
#elif (_DERIV_ID1 == _VAL) && (_DERIV_ID2 != _VAL)
    r = y
    r%val = _CONV0(x) - r%val
#else
    r = x
    t = y
    r = r - t
#endif
end function _PROC
#undef _PROC


#define _PROC _TYPES_BINARY_OP(mul)
elemental function _PROC(x, y) result(r)
    _ARG_TYPE1, intent(in) :: x
    _ARG_TYPE2, intent(in) :: y
    _RES_TYPE :: r

#if (_DERIV_ID1 == _VAL) || (_DERIV_ID2 == _VAL)
    _ELEM_TYPE0 :: val
#else
    _RES_TYPE :: t
#endif

#if (_DERIV_ID1 != _VAL) && (_DERIV_ID2 == _VAL)
    val = _CONV0(y)
    r%val = x%val * val
    r%grad = x%grad * val
#  if _DERIV_ID0 == _GRADGRAD
    r%gradgrad = x%gradgrad * val
#  elif _DERIV_ID0 == _DIVGRAD
    r%divgrad = x%divgrad * val
#  endif
#elif (_DERIV_ID1 == _VAL) && (_DERIV_ID2 != _VAL)
    val = _CONV0(x)
    r%val = val * y%val
    r%grad = val * y%grad
#  if _DERIV_ID0 == _GRADGRAD
    r%gradgrad = val * y%gradgrad
#  elif _DERIV_ID0 == _DIVGRAD
    r%divgrad = val * y%divgrad
#  endif
#else
    r = x
    t = y
    r = r * t
#endif
end function _PROC
#undef _PROC


#define _PROC _TYPES_BINARY_OP(div)
elemental function _PROC(x, y) result(r)
    _ARG_TYPE1, intent(in) :: x
    _ARG_TYPE2, intent(in) :: y
    _RES_TYPE :: r

#if _TYPE_ID0 != _INTEGER
#  if (_DERIV_ID1 != _VAL) && (_DERIV_ID2 == _VAL)
    _ELEM_TYPE0 :: inv_val
#  endif
#  if _DERIV_ID2 != _VAL
    _RES_TYPE :: t
#    if _DERIV_ID1 == _VAL
    _ELEM_TYPE0 :: factor1, factor2
#      if _DERIV_ID0 == _GRADGRAD
    integer :: i, lo, up
#      endif
#    endif
#  endif

#  if (_DERIV_ID1 != _VAL) && (_DERIV_ID2 == _VAL)
    inv_val = 1 / _CONV0(y)
    r%val = x%val * inv_val
    r%grad = x%grad * inv_val
#    if _DERIV_ID0 == _GRADGRAD
    r%gradgrad = x%gradgrad * inv_val
#    elif _DERIV_ID0 == _DIVGRAD
    r%divgrad = x%divgrad * inv_val
#    endif
#  elif (_DERIV_ID1 == _VAL) && (_DERIV_ID2 != _VAL)
    t = y
    factor2 = 1 / t%val
    r%val = x * factor2
    factor1 = -factor2 * r%val
    r%grad = factor1 * t%grad
#    if _DERIV_ID0 > _GRAD
    factor2 = -2 * factor2
#    endif
#    if _DERIV_ID0 == _GRADGRAD
    allocate(r%gradgrad(size(t%gradgrad)))
    up = 0
    do i = 1, size(r%grad)
        lo = up + 1
        up = up + i
        r%gradgrad(lo:up) = ( &
            factor1 * t%gradgrad(lo:up) + factor2 * r%grad(i) * t%grad(:i) &
        )
    end do
#    elif _DERIV_ID0 == _DIVGRAD
    r%divgrad = factor1 * t%divgrad + factor2 * dot_product(r%grad, t%grad)
#    endif
#  else
    r = x
    t = y
    r = r / t
#  endif
#else
    r = real(x) / real(y)
#endif
end function _PROC
#undef _PROC


#define _PROC _TYPES_BINARY_OP(pow)
elemental function _PROC(x, y) result(r)
    _ARG_TYPE1, intent(in) :: x
    _ARG_TYPE2, intent(in) :: y
    _RES_TYPE :: r

#if _TYPE_ID0 != _INTEGER
    _RES_TYPE :: t
#  if (_DERIV_ID1 == _VAL) || (_DERIV_ID2 == _VAL)
    _ELEM_TYPE0 :: val, factor1, factor2
#    if (_DERIV_ID1 != _VAL)
    _ELEM_TYPE0 :: inv_val
#    endif
#    if _DERIV_ID0 == _GRADGRAD
    integer :: i, lo, up
#    endif
#  endif

#  if (_DERIV_ID1 != _VAL) && (_DERIV_ID2 == _VAL)
    t = x
    val = _CONV0(y)
    r%val = t%val**val
    inv_val = 1 / t%val
    factor2 = val * inv_val
    factor1 = factor2 * r%val
    r%grad = factor1 * t%grad
#    if _DERIV_ID0 > _GRAD
    factor2 = factor2 - inv_val
#    endif
#    if _DERIV_ID0 == _GRADGRAD
    allocate(r%gradgrad(size(t%gradgrad)))
    up = 0
    do i = 1, size(r%grad)
        lo = up + 1
        up = up + i
        r%gradgrad(lo:up) = ( &
            factor1 * t%gradgrad(lo:up) + factor2 * r%grad(i) * t%grad(:i) &
        )
    end do
#    elif _DERIV_ID0 == _DIVGRAD
    r%divgrad = factor1 * t%divgrad + factor2 * dot_product(r%grad, t%grad)
#    endif
#  elif (_DERIV_ID1 == _VAL) && (_DERIV_ID2 != _VAL)
    val = _CONV0(x)
    t = y
    r%val = val**t%val
    factor2 = log(val)
    factor1 = factor2 * r%val
    r%grad = factor1 * t%grad
#    if _DERIV_ID0 == _GRADGRAD
    allocate(r%gradgrad(size(t%gradgrad)))
    up = 0
    do i = 1, size(r%grad)
        lo = up + 1
        up = up + i
        r%gradgrad(lo:up) = ( &
            factor1 * t%gradgrad(lo:up) + factor2 * r%grad(i) * t%grad(:i) &
        )
    end do
#    elif _DERIV_ID0 == _DIVGRAD
    r%divgrad = factor1 * t%divgrad + factor2 * dot_product(r%grad, t%grad)
#    endif
#  else
    r = x
    t = y
    r = r**t
#  endif
#else
    r = real(x)**real(y)
#endif
end function _PROC
#undef _PROC


#if (_DERIV_ID1 | _TYPE_ID1) == (_VAL | _INTEGER)
#  define _PROC _TYPES_BINARY_OP(cat)
elemental function _PROC(x, y) result(r)
    _ARG_TYPE1, intent(in) :: x
    _ARG_TYPE2, intent(in) :: y
    type(_NAME2) :: r

    integer :: n, m, j
#  if _DERIV_ID0 == _GRADGRAD
    integer :: i, lo, up, lo_, up_
#  endif

    r%val = y%val
    n = size(y%grad)
    m = max(n + x, 0)
#  if _DERIV_ID0 == _GRADGRAD
    allocate(r%gradgrad(m * (m + 1) / 2))
#  endif
    if (m > n) then
        j = x
        allocate(r%grad(m))
        r%grad(:j) = 0
        r%grad(j + 1 :) = y%grad
#  if _DERIV_ID0 == _GRADGRAD
        up = j * (j + 1) / 2
        up_ = 0
        r%gradgrad(:up) = 0
        do i = 1, n
            up = up + j
            lo = up + 1
            up = up + i
            lo_ = up_ + 1
            up_ = up_ + i
            r%gradgrad(lo - j : lo - 1) = 0
            r%gradgrad(lo:up) = y%gradgrad(lo_:up_)
        end do
#  endif
    else if (m > 0) then
        j = -x
        r%grad = y%grad(j + 1 :)
#  if _DERIV_ID0 == _GRADGRAD
        up = j * (j + 1) / 2
        up_ = 0
        do i = 1, m
            up = up + j
            lo = up + 1
            up = up + i
            lo_ = up_ + 1
            up_ = up_ + i
            r%gradgrad(lo_:up_) = y%gradgrad(lo:up)
        end do
#  endif
    else
#  if _DERIV_ID0 == _DIVGRAD
        r%divgrad = 0
#  endif
    end if
end function _PROC
#  undef _PROC

#elif (_DERIV_ID2 | _TYPE_ID2) == (_VAL | _INTEGER)

#  define _PROC _TYPES_BINARY_OP(cat)
elemental function _PROC(x, y) result(r)
    _ARG_TYPE1, intent(in) :: x
    _ARG_TYPE2, intent(in) :: y
    type(_NAME1) :: r

    integer :: n, m
#  if _DERIV_ID0 == _GRADGRAD
    integer :: n_, m_
#  endif

    r%val = x%val
    n = size(x%grad)
    m = max(n + y, 0)
#  if _DERIV_ID0 == _GRADGRAD
    m_ = m * (m + 1) / 2
#  endif
    if (m > n) then
        allocate(r%grad(m))
        r%grad(:n) = x%grad
        r%grad(n + 1 :) = 0
#  if _DERIV_ID0 == _GRADGRAD
        allocate(r%gradgrad(m_))
        n_ = size(x%gradgrad)
        r%gradgrad(:n_) = x%gradgrad
        r%gradgrad(n_ + 1 :) = 0
#  endif
    else
        r%grad = x%grad(:m)
#  if _DERIV_ID0 == _GRADGRAD
        r%gradgrad = x%gradgrad(:m_)
#  elif _DERIV_ID0 == _DIVGRAD
        if (m == 0) r%divgrad = 0
#  endif
    end if
end function _PROC
#  undef _PROC
#endif


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
