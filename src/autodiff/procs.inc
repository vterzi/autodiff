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

#if (_DERIV_ID1 == _GRADGRAD) && (_DERIV_ID2 != _GRADGRAD)
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


#define _PROC _TYPES_BINARY_OP(eq)
elemental function _PROC(x, y) result(r)
    _ARG_TYPE1, intent(in) :: x
    _ARG_TYPE2, intent(in) :: y
    logical :: r

#if _DERIV_ID1 == _DERIV_ID2
    r = x%v == y%v .and. all(x%g == y%g)
#  if _DERIV_ID0 == _GRADGRAD
    r = r .and. all(x%gg == y%gg)
#  elif _DERIV_ID0 == _DIVGRAD
    r = r .and. x%dg == y%dg
#  endif
#else
    r = .false.
#endif
end function _PROC
#undef _PROC


#define _PROC _TYPES_BINARY_OP(ne)
elemental function _PROC(x, y) result(r)
    _ARG_TYPE1, intent(in) :: x
    _ARG_TYPE2, intent(in) :: y
    logical :: r

#if _DERIV_ID1 == _DERIV_ID2
    r = x%v /= y%v .or. any(x%g /= y%g)
#  if _DERIV_ID0 == _GRADGRAD
    r = r .or. any(x%gg /= y%gg)
#  elif _DERIV_ID0 == _DIVGRAD
    r = r .or. x%dg /= y%dg
#  endif
#else
    r = .true.
#endif
end function _PROC
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
    r = x
    f = _CONV0(y)
    r%v = r%v * f
    r%g = r%g * f
#  if _DERIV_ID0 == _GRADGRAD
    r%gg = r%gg * f
#  elif _DERIV_ID0 == _DIVGRAD
    r%dg = r%dg * f
#  endif
#elif (_DERIV_ID1 == _VAL) && (_DERIV_ID2 != _VAL)
    f = _CONV0(x)
    r = y
    r%v = f * r%v
    r%g = f * r%g
#  if _DERIV_ID0 == _GRADGRAD
    r%gg = f * r%gg
#  elif _DERIV_ID0 == _DIVGRAD
    r%dg = f * r%dg
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
    r = x
    f = 1 / _CONV0(y)
    r%v = r%v * f
    r%g = r%g * f
#    if _DERIV_ID0 == _GRADGRAD
    r%gg = r%gg * f
#    elif _DERIV_ID0 == _DIVGRAD
    r%dg = r%dg * f
#    endif
#  elif (_DERIV_ID1 == _VAL) && (_DERIV_ID2 != _VAL)
    t = y
    f2 = 1 / t%v
    r%v = _CONV0(x) * f2
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
#    if _DERIV_ID0 == _GRADGRAD
    integer :: i, lo, up
#    endif
#  endif

#  if (_DERIV_ID1 != _VAL) && (_DERIV_ID2 == _VAL)
    t = x
    v = _CONV0(y)
    r%v = t%v**v
    f2 = v - 1
    f1 = v * t%v**f2
    r%g = f1 * t%g
#    if _DERIV_ID0 > _GRAD
    f2 = v * f2 * t%v**(v - 2)
#    endif
#    if _DERIV_ID0 == _GRADGRAD
    allocate(r%gg(size(t%gg)))
    up = 0
    do i = 1, size(r%g)
        lo = up + 1
        up = up + i
        r%gg(lo:up) = f1 * t%gg(lo:up) + f2 * t%g(i) * t%g(:i)
    end do
#    elif _DERIV_ID0 == _DIVGRAD
    r%dg = f1 * t%dg + f2 * dot_product(t%g, t%g)
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


#define _PROC _TYPES_BINARY_OP(dot_product)
pure function _PROC(vector_a, vector_b) result(r)
    _ARG_TYPE1, intent(in) :: vector_a(:)
    _ARG_TYPE2, intent(in) :: vector_b(:)
    _RES_TYPE :: r

    integer :: m, n, j
#if (_DERIV_ID1 == _VAL) || (_DERIV_ID2 == _VAL)
    _ELEM_TYPE0 :: f
#elif _DERIV_ID0 == _GRADGRAD
    integer :: i, lo, up
#endif
#if _DERIV_ID1 != _VAL
    _RES_TYPE :: x
#endif
#if _DERIV_ID2 != _VAL
    _RES_TYPE :: y
#endif

    m = min(size(vector_a), size(vector_b))
    r%v = 0
    n = merge(huge(n), 0, m > 0)
    do j = 1, m
#if (_DERIV_ID1 != _VAL) && (_DERIV_ID2 == _VAL)
        n = min(n, size(vector_a(j)%g))
#elif (_DERIV_ID1 == _VAL) && (_DERIV_ID2 != _VAL)
        n = min(n, size(vector_b(j)%g))
#else
        n = min(n, size(vector_a(j)%g), size(vector_b(j)%g))
#endif
    end do
    allocate(r%g(n))
    r%g = 0
#if _DERIV_ID0 == _GRADGRAD
    allocate(r%gg(n * (n + 1) / 2))
    r%gg = 0
#elif _DERIV_ID0 == _DIVGRAD
    r%dg = 0
#endif
    do j = 1, m
#if (_DERIV_ID1 != _VAL) && (_DERIV_ID2 == _VAL)
#  if _TYPE_ID1 == _COMPLEX
        x = conjg(vector_a(j))
#  else
        x = vector_a(j)
#  endif
        f = _CONV0(vector_b(j))
        r%v = r%v + x%v * f
        r%g = r%g + x%g * f
#  if _DERIV_ID0 == _GRADGRAD
        r%gg = r%gg + x%gg * f
#  elif _DERIV_ID0 == _DIVGRAD
        r%dg = r%dg + x%dg * f
#  endif
#elif (_DERIV_ID1 == _VAL) && (_DERIV_ID2 != _VAL)
#  if _TYPE_ID1 == _COMPLEX
        f = _CONV0(conjg(vector_a(j)))
#  else
        f = _CONV0(vector_a(j))
#  endif
        y = vector_b(j)
        r%v = r%v + f * y%v
        r%g = r%g + f * y%g
#  if _DERIV_ID0 == _GRADGRAD
        r%gg = r%gg + f * y%gg
#  elif _DERIV_ID0 == _DIVGRAD
        r%dg = r%dg + f * y%dg
#  endif
#else
#  if _TYPE_ID1 == _COMPLEX
        x = conjg(vector_a(j))
#  else
        x = vector_a(j)
#  endif
        y = vector_b(j)
        r%v = r%v + x%v * y%v
        r%g = r%g + x%g * y%v + x%v * y%g
#  if _DERIV_ID0 == _GRADGRAD
        up = 0
        do i = 1, n
            lo = up + 1
            up = up + i
            r%gg(lo:up) = r%gg(lo:up) + ( &
                x%gg(lo:up) * y%v &
                + x%g(:i) * y%g(i) &
                + x%g(i) * y%g(:i) &
                + x%v * y%gg(lo:up) &
            )
        end do
#  elif _DERIV_ID0 == _DIVGRAD
        r%dg = r%dg + x%dg * y%v + 2 * dot_product(x%g, y%g) + x%v * y%dg
#  endif
#endif
    end do
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
