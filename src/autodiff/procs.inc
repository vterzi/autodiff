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
#if ((_TYPE_ID1 != _INTEGER) && (_TYPE_ID2 == _INTEGER)) || ( \
    (_KIND1 >= _KIND2) \
    && ((_TYPE_ID1 == _INTEGER) == (_TYPE_ID2 == _INTEGER)) \
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
    v%v = _CONV1(expr)
    if (allocated(v%g)) deallocate(v%g)
    allocate(v%g(0))
#elif (_DERIV_ID1 == _VAL) && (_DERIV_ID2 != _VAL)
    v = _CONV1(expr%v)
#else
    v%v = _CONV1(expr%v)
    v%g = _CONV1(expr%g)
#endif
#if (_DERIV_ID1 == _GRADGRAD) && (_DERIV_ID2 == _GRADGRAD)
    v%gg = _CONV1(expr%gg)
#elif (_DERIV_ID1 == _DIVGRAD) && (_DERIV_ID2 == _DIVGRAD)
    v%dg = _CONV1(expr%dg)
#elif (_DERIV_ID1 == _DIVGRAD) && (_DERIV_ID2 == _GRADGRAD)
    v%dg = _CONV1(expr%divgrad())
#elif _DERIV_ID1 == _GRADGRAD
    if (allocated(v%gg)) deallocate(v%gg)
    n = size(v%g)
    allocate(v%gg(n * (n + 1) / 2))
    v%gg = 0
#elif _DERIV_ID1 == _DIVGRAD
    v%dg = 0
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
    r%v = r%v + _CONV0(y)
#elif (_DERIV_ID1 == _VAL) && (_DERIV_ID2 != _VAL)
    r = y
    r%v = _CONV0(x) + r%v
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
    r%v = r%v - _CONV0(y)
#elif (_DERIV_ID1 == _VAL) && (_DERIV_ID2 != _VAL)
    r = y
    r%v = _CONV0(x) - r%v
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
    _ELEM_TYPE0 :: f
#else
    _RES_TYPE :: t
#endif

#if (_DERIV_ID1 != _VAL) && (_DERIV_ID2 == _VAL)
    f = _CONV0(y)
    r%v = x%v * f
    r%g = x%g * f
#  if _DERIV_ID0 == _GRADGRAD
    r%gg = x%gg * f
#  elif _DERIV_ID0 == _DIVGRAD
    r%dg = x%dg * f
#  endif
#elif (_DERIV_ID1 == _VAL) && (_DERIV_ID2 != _VAL)
    f = _CONV0(x)
    r%v = f * y%v
    r%g = f * y%g
#  if _DERIV_ID0 == _GRADGRAD
    r%gg = f * y%gg
#  elif _DERIV_ID0 == _DIVGRAD
    r%dg = f * y%dg
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
    _ELEM_TYPE0 :: f
#  endif
#  if _DERIV_ID2 != _VAL
    _RES_TYPE :: t
#    if _DERIV_ID1 == _VAL
    _ELEM_TYPE0 :: f1, f2
#      if _DERIV_ID0 == _GRADGRAD
    integer :: i, lo, up
#      endif
#    endif
#  endif

#  if (_DERIV_ID1 != _VAL) && (_DERIV_ID2 == _VAL)
    f = 1 / _CONV0(y)
    r%v = x%v * f
    r%g = x%g * f
#    if _DERIV_ID0 == _GRADGRAD
    r%gg = x%gg * f
#    elif _DERIV_ID0 == _DIVGRAD
    r%dg = x%dg * f
#    endif
#  elif (_DERIV_ID1 == _VAL) && (_DERIV_ID2 != _VAL)
    t = y
    f2 = 1 / t%v
    r%v = x * f2
    f1 = -f2 * r%v
    r%g = f1 * t%g
#    if _DERIV_ID0 > _GRAD
    f2 = -2 * f2
#    endif
#    if _DERIV_ID0 == _GRADGRAD
    allocate(r%gg(size(t%gg)))
    up = 0
    do i = 1, size(r%g)
        lo = up + 1
        up = up + i
        r%gg(lo:up) = f1 * t%gg(lo:up) + f2 * r%g(i) * t%g(:i)
    end do
#    elif _DERIV_ID0 == _DIVGRAD
    r%dg = f1 * t%dg + f2 * dot_product(r%g, t%g)
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
    _ELEM_TYPE0 :: v, f1, f2
#    if (_DERIV_ID1 != _VAL)
    _ELEM_TYPE0 :: f
#    endif
#    if _DERIV_ID0 == _GRADGRAD
    integer :: i, lo, up
#    endif
#  endif

#  if (_DERIV_ID1 != _VAL) && (_DERIV_ID2 == _VAL)
    t = x
    v = _CONV0(y)
    r%v = t%v**v
    f = 1 / t%v
    f2 = v * f
    f1 = f2 * r%v
    r%g = f1 * t%g
#    if _DERIV_ID0 > _GRAD
    f2 = f2 - f
#    endif
#    if _DERIV_ID0 == _GRADGRAD
    allocate(r%gg(size(t%gg)))
    up = 0
    do i = 1, size(r%g)
        lo = up + 1
        up = up + i
        r%gg(lo:up) = f1 * t%gg(lo:up) + f2 * r%g(i) * t%g(:i)
    end do
#    elif _DERIV_ID0 == _DIVGRAD
    r%dg = f1 * t%dg + f2 * dot_product(r%g, t%g)
#    endif
#  elif (_DERIV_ID1 == _VAL) && (_DERIV_ID2 != _VAL)
    v = _CONV0(x)
    t = y
    r%v = v**t%v
    f2 = log(v)
    f1 = f2 * r%v
    r%g = f1 * t%g
#    if _DERIV_ID0 == _GRADGRAD
    allocate(r%gg(size(t%gg)))
    up = 0
    do i = 1, size(r%g)
        lo = up + 1
        up = up + i
        r%gg(lo:up) = f1 * t%gg(lo:up) + f2 * r%g(i) * t%g(:i)
    end do
#    elif _DERIV_ID0 == _DIVGRAD
    r%dg = f1 * t%dg + f2 * dot_product(r%g, t%g)
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

    r%v = y%v
    n = size(y%g)
    m = max(n + x, 0)
#  if _DERIV_ID0 == _GRADGRAD
    allocate(r%gg(m * (m + 1) / 2))
#  endif
    if (m > n) then
        j = x
        allocate(r%g(m))
        r%g(:j) = 0
        r%g(j + 1 :) = y%g
#  if _DERIV_ID0 == _GRADGRAD
        up = j * (j + 1) / 2
        up_ = 0
        r%gg(:up) = 0
        do i = 1, n
            up = up + j
            lo = up + 1
            up = up + i
            lo_ = up_ + 1
            up_ = up_ + i
            r%gg(lo - j : lo - 1) = 0
            r%gg(lo:up) = y%gg(lo_:up_)
        end do
#  endif
    else if (m > 0) then
        j = -x
        r%g = y%g(j + 1 :)
#  if _DERIV_ID0 == _GRADGRAD
        up = j * (j + 1) / 2
        up_ = 0
        do i = 1, m
            up = up + j
            lo = up + 1
            up = up + i
            lo_ = up_ + 1
            up_ = up_ + i
            r%gg(lo_:up_) = y%gg(lo:up)
        end do
#  endif
    else
#  if _DERIV_ID0 == _DIVGRAD
        r%dg = 0
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

    r%v = x%v
    n = size(x%g)
    m = max(n + y, 0)
#  if _DERIV_ID0 == _GRADGRAD
    m_ = m * (m + 1) / 2
#  endif
    if (m > n) then
        allocate(r%g(m))
        r%g(:n) = x%g
        r%g(n + 1 :) = 0
#  if _DERIV_ID0 == _GRADGRAD
        allocate(r%gg(m_))
        n_ = size(x%gg)
        r%gg(:n_) = x%gg
        r%gg(n_ + 1 :) = 0
#  endif
    else
        r%g = x%g(:m)
#  if _DERIV_ID0 == _GRADGRAD
        r%gg = x%gg(:m_)
#  elif _DERIV_ID0 == _DIVGRAD
        if (m == 0) r%dg = 0
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
