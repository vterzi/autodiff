#define _PROC _TYPE_UNARY_OP(new)
pure function _PROC(val, grad &
#if _DERIV_ID == _GRADGRAD
    , gradgrad, upper &
#elif _DERIV_ID == _DIVGRAD
    , divgrad &
#endif
) result(r)
    _ELEM_TYPE, intent(in) :: val, grad(:)
#if _DERIV_ID == _GRADGRAD
    _ELEM_TYPE, intent(in) :: gradgrad(:, :)
    logical, intent(in) :: upper
#elif _DERIV_ID == _DIVGRAD
    _ELEM_TYPE, intent(in) :: divgrad
#endif
    type(_NAME) :: r

#if _DERIV_ID == _GRADGRAD
    integer :: n, n1, n2, i, lo, up, up_
#endif

    r%v = val
    r%g = grad
#if _DERIV_ID == _GRADGRAD
    n = size(grad)
    n1 = size(gradgrad, 1)
    n2 = size(gradgrad, 2)
    allocate(r%gg(n * (n + 1) / 2))
    if (upper) then
        do i = 1, n
            lo = up + 1
            up = up + i
            if (i <= n2) then
                if (i <= n1) then
                    r%gg(lo:up) = gradgrad(:i, i)
                else
                    up_ = up + n1 - i
                    r%gg(lo:up_) = gradgrad(:n1, i)
                    up_ = up_ + 1
                    r%gg(up_:up) = 0
                end if
            else
                r%gg(lo:up) = 0
            end if
        end do
    else
        do i = 1, n
            lo = up + 1
            up = up + i
            if (i <= n1) then
                if (i <= n2) then
                    r%gg(lo:up) = gradgrad(i, :i)
                else
                    up_ = up + n2 - i
                    r%gg(lo:up_) = gradgrad(i, :n2)
                    up_ = up_ + 1
                    r%gg(up_:up) = 0
                end if
            else
                r%gg(lo:up) = 0
            end if
        end do
    end if
#elif _DERIV_ID == _DIVGRAD
    r%dg = divgrad
#endif
end function _PROC
#undef _PROC


#define _PROC _TYPE_UNARY_OP(val)
pure function _PROC(x) result(val)
    class(_NAME), intent(in) :: x
    _ELEM_TYPE :: val

    val = x%v
end function _PROC
#undef _PROC


#define _PROC _TYPE_UNARY_OP(grad)
pure function _PROC(x) result(grad)
    class(_NAME), intent(in) :: x
    _ELEM_TYPE :: grad(size(x%g))

    grad = x%g
end function _PROC
#undef _PROC


#if _DERIV_ID == _GRADGRAD
#  define _PROC _TYPE_UNARY_OP(gradgrad)
pure function _PROC(x) result(gradgrad)
    class(_NAME), intent(in) :: x
    _ELEM_TYPE :: gradgrad(size(x%g), size(x%g))

    integer :: n, i, j, lo, up

    n = size(x%g)
    up = 0
    do i = 1, n
        lo = up + 1
        up = up + i
        gradgrad(:i, i) = x%gg(lo:up)
    end do
    do i = 2, n
        do j = 1, i - 1
            gradgrad(i, j) = gradgrad(j, i)
        end do
    end do
end function _PROC
#  undef _PROC
#endif


#if _DERIV_ID > _GRAD
#  define _PROC _TYPE_UNARY_OP(divgrad)
pure function _PROC(x) result(divgrad)
    class(_NAME), intent(in) :: x
    _ELEM_TYPE :: divgrad

#  if _DERIV_ID == _GRADGRAD
    integer :: i, j
#  endif

#  if _DERIV_ID == _GRADGRAD
    divgrad = 0
    j = 0
    do i = 1, size(x%g)
        j = j + i
        divgrad = divgrad + x%gg(j)
    end do
#  elif _DERIV_ID == _DIVGRAD
    divgrad = x%dg
#  endif
end function _PROC
#  undef _PROC
#endif

! -----------------------------------------------------------------------------

#define _PROC _TYPE_BINARY_OP(eq)
elemental function _PROC(x, y) result(r)
    class(_NAME), intent(in) :: x, y
    logical :: r

    r = x%v == y%v .and. all(x%g == y%g)
#if _DERIV_ID == _GRADGRAD
    r = r .and. all(x%gg == y%gg)
#elif _DERIV_ID == _DIVGRAD
    r = r .and. x%dg == y%dg
#endif
end function _PROC
#undef _PROC


#define _PROC _TYPE_BINARY_OP(ne)
elemental function _PROC(x, y) result(r)
    class(_NAME), intent(in) :: x, y
    logical :: r

    r = x%v /= y%v .or. any(x%g /= y%g)
#if _DERIV_ID == _GRADGRAD
    r = r .or. any(x%gg /= y%gg)
#elif _DERIV_ID == _DIVGRAD
    r = r .or. x%dg /= y%dg
#endif
end function _PROC
#undef _PROC


#define _PROC _TYPE_UNARY_OP(pos)
elemental function _PROC(x) result(r)
    class(_NAME), intent(in) :: x
    type(_NAME) :: r

    r%v = x%v
    r%g = x%g
#if _DERIV_ID == _GRADGRAD
    r%gg = x%gg
#elif _DERIV_ID == _DIVGRAD
    r%dg = x%dg
#endif
end function _PROC
#undef _PROC


#define _PROC _TYPE_UNARY_OP(neg)
elemental function _PROC(x) result(r)
    class(_NAME), intent(in) :: x
    type(_NAME) :: r

    r%v = -x%v
    r%g = -x%g
#if _DERIV_ID == _GRADGRAD
    r%gg = -x%gg
#elif _DERIV_ID == _DIVGRAD
    r%dg = -x%dg
#endif
end function _PROC
#undef _PROC


#define _PROC _TYPE_BINARY_OP(add)
elemental function _PROC(x, y) result(r)
    class(_NAME), intent(in) :: x, y
    type(_NAME) :: r

    r%v = x%v + y%v
    r%g = x%g + y%g
#if _DERIV_ID == _GRADGRAD
    r%gg = x%gg + y%gg
#elif _DERIV_ID == _DIVGRAD
    r%dg = x%dg + y%dg
#endif
end function _PROC
#undef _PROC


#define _PROC _TYPE_BINARY_OP(sub)
elemental function _PROC(x, y) result(r)
    class(_NAME), intent(in) :: x, y
    type(_NAME) :: r

    r%v = x%v - y%v
    r%g = x%g - y%g
#if _DERIV_ID == _GRADGRAD
    r%gg = x%gg - y%gg
#elif _DERIV_ID == _DIVGRAD
    r%dg = x%dg - y%dg
#endif
end function _PROC
#undef _PROC


#define _PROC _TYPE_BINARY_OP(mul)
elemental function _PROC(x, y) result(r)
    class(_NAME), intent(in) :: x, y
    type(_NAME) :: r

#if _DERIV_ID == _GRADGRAD
    integer :: i, lo, up
#endif

    r%v = x%v * y%v
    r%g = x%g * y%v + x%v * y%g
#if _DERIV_ID == _GRADGRAD
    allocate(r%gg(min(size(x%gg), size(y%gg))))
    up = 0
    do i = 1, size(r%g)
        lo = up + 1
        up = up + i
        r%gg(lo:up) = ( &
            x%gg(lo:up) * y%v &
            + x%g(:i) * y%g(i) &
            + x%g(i) * y%g(:i) &
            + x%v * y%gg(lo:up) &
        )
    end do
#elif _DERIV_ID == _DIVGRAD
    r%dg = x%dg * y%v + 2 * dot_product(x%g, y%g) + x%v * y%dg
#endif
end function _PROC
#undef _PROC


#define _PROC _TYPE_BINARY_OP(div)
elemental function _PROC(x, y) result(r)
    class(_NAME), intent(in) :: x, y
    type(_NAME) :: r

#if _TYPE_ID != _INTEGER
    _ELEM_TYPE :: f1, f2
#  if _DERIV_ID == _GRADGRAD
    integer :: i, lo, up
#  endif

    f1 = 1 / y%v
    r%v = x%v * f1
    f2 = f1 * r%v
    r%g = f1 * x%g - f2 * y%g
#  if _DERIV_ID == _GRADGRAD
    allocate(r%gg(min(size(x%gg), size(y%gg))))
    up = 0
    do i = 1, size(r%g)
        lo = up + 1
        up = up + i
        r%gg(lo:up) = ( &
            f1 * x%gg(lo:up) &
            - f1 * y%g(i) * r%g(:i) &
            - f1 * r%g(i) * y%g(:i) &
            - f2 * y%gg(lo:up) &
        )
    end do
#  elif _DERIV_ID == _DIVGRAD
    r%dg = f1 * x%dg - 2 * f1 * dot_product(y%g, r%g) - f2 * y%dg
#  endif
#else
    r = real(x) / real(y)
#endif
end function _PROC
#undef _PROC


#define _PROC _TYPE_BINARY_OP(pow)
elemental function _PROC(x, y) result(r)
    class(_NAME), intent(in) :: x, y
    type(_NAME) :: r

#if _TYPE_ID != _INTEGER
    _ELEM_TYPE :: f, f1, f2
#  if _DERIV_ID > _GRAD
    _ELEM_TYPE :: f3, f4
#  endif
#  if _DERIV_ID == _GRADGRAD
    integer :: i, lo, up
#  endif

    r%v = x%v**y%v
    f = 1 / x%v
    f1 = y%v * f
    f2 = log(x%v)
#  if _DERIV_ID > _GRAD
    f3 = f1 * (f1 - f)
    f4 = f2**2
    f = (f1 * f2 + f)
#  endif
    f1 = f1 * r%v
    f2 = f2 * r%v
    r%g = f1 * x%g + f2 * y%g
#  if _DERIV_ID == _GRADGRAD
    f3 = f3 * r%v
    f4 = f4 * r%v
    f = f * r%v
    allocate(r%gg(min(size(x%gg), size(y%gg))))
    up = 0
    do i = 1, size(r%g)
        lo = up + 1
        up = up + i
        r%gg(lo:up) = ( &
            f1 * x%gg(lo:up) &
            + (f3 * x%g(i) + f * y%g(i)) * x%g(:i) &
            + (f * x%g(i) + f4 * y%g(i)) * y%g(:i) &
            + f2 * y%gg(lo:up) &
        )
    end do
#  elif _DERIV_ID == _DIVGRAD
    r%dg = ( &
        f1 * x%dg &
        + r%v * ( &
            f3 * dot_product(x%g, x%g) &
            + 2 * f * dot_product(x%g, y%g) &
            + f4 * dot_product(y%g, y%g) &
        ) &
        + f2 * y%dg &
    )
#  endif
#else
    r = real(x)**real(y)
#endif
end function _PROC
#undef _PROC

! -----------------------------------------------------------------------------

#define _PROC _CAT(I_cat_,_NAME)
elemental function _PROC(x, y) result(r)
    integer, intent(in) :: x
    class(_NAME), intent(in) :: y
    type(_NAME) :: r

    integer :: n, m, j
#if _DERIV_ID == _GRADGRAD
    integer :: i, lo, up, lo_, up_
#endif

    r%v = y%v
    n = size(y%g)
    m = max(n + x, 0)
#if _DERIV_ID == _GRADGRAD
    allocate(r%gg(m * (m + 1) / 2))
#endif
    if (m > n) then
        j = x
        allocate(r%g(m))
        r%g(:j) = 0
        r%g(j + 1 :) = y%g
#if _DERIV_ID == _GRADGRAD
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
#endif
    else if (m > 0) then
        j = -x
        r%g = y%g(j + 1 :)
#if _DERIV_ID == _GRADGRAD
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
#endif
    else
#if _DERIV_ID == _DIVGRAD
        r%dg = 0
#endif
    end if
end function _PROC
#undef _PROC


#define _PROC _CAT(_NAME,_cat_I)
elemental function _PROC(x, y) result(r)
    class(_NAME), intent(in) :: x
    integer, intent(in) :: y
    type(_NAME) :: r

    integer :: n, m
#if _DERIV_ID == _GRADGRAD
    integer :: n_, m_
#endif

    r%v = x%v
    n = size(x%g)
    m = max(n + y, 0)
#if _DERIV_ID == _GRADGRAD
    m_ = m * (m + 1) / 2
#endif
    if (m > n) then
        allocate(r%g(m))
        r%g(:n) = x%g
        r%g(n + 1 :) = 0
#if _DERIV_ID == _GRADGRAD
        allocate(r%gg(m_))
        n_ = size(x%gg)
        r%gg(:n_) = x%gg
        r%gg(n_ + 1 :) = 0
#endif
    else
        r%g = x%g(:m)
#if _DERIV_ID == _GRADGRAD
        r%gg = x%gg(:m_)
#elif _DERIV_ID == _DIVGRAD
        if (m == 0) r%dg = 0
#endif
    end if
end function _PROC
#undef _PROC

! -----------------------------------------------------------------------------

#if _TYPE_ID != _COMPLEX
#  define _PROC _TYPE_UNARY_OP(sign)
elemental function _PROC(a, b) result(r)
    class(_NAME), intent(in) :: a, b
    type(_NAME) :: r

    if (a%v == sign(a%v, b%v)) then
        r = a
    else
        r = -a
    end if
end function _PROC
#  undef _PROC
#endif


#if _TYPE_ID == _COMPLEX
#  define _PROC _TYPE_UNARY_OP(real)
elemental function _PROC(a) result(r)
    class(_NAME), intent(in) :: a
    type(_CAT3(_DERIV,R,_KIND_LABEL)) :: r

    r%v = real(a%v)
    r%g = real(a%g)
#  if _DERIV_ID == _GRADGRAD
    r%gg = real(a%gg)
#  elif _DERIV_ID == _DIVGRAD
    r%dg = real(a%dg)
#  endif
end function _PROC
#  undef _PROC


#  define _PROC _TYPE_UNARY_OP(aimag)
elemental function _PROC(z) result(r)
    class(_NAME), intent(in) :: z
    type(_CAT3(_DERIV,R,_KIND_LABEL)) :: r

    r%v = aimag(z%v)
    r%g = aimag(z%g)
#  if _DERIV_ID == _GRADGRAD
    r%gg = aimag(z%gg)
#  elif _DERIV_ID == _DIVGRAD
    r%dg = aimag(z%dg)
#  endif
end function _PROC
#  undef _PROC


#  define _PROC _TYPE_UNARY_OP(conjg)
elemental function _PROC(z) result(r)
    class(_NAME), intent(in) :: z
    type(_NAME) :: r

    r%v = conjg(z%v)
    r%g = conjg(z%g)
#  if _DERIV_ID == _GRADGRAD
    r%gg = conjg(z%gg)
#  elif _DERIV_ID == _DIVGRAD
    r%dg = conjg(z%dg)
#  endif
end function _PROC
#  undef _PROC
#endif


#define _PROC _TYPE_UNARY_OP(kind)
elemental function _PROC(x) result(r)
    class(_NAME), intent(in) :: x
    integer :: r

    r = kind(x%v)
end function _PROC
#undef _PROC


#define _PROC _TYPE_UNARY_OP(abs)
elemental function _PROC(a) result(r)
    class(_NAME), intent(in) :: a
    type(_NAME) :: r

#if _TYPE_ID == _COMPLEX
    r = sqrt(a * conjg(a))
#else
    if (a%v > 0) then
        r = a
    else if (a%v < 0) then
        r = -a
    else
        r%v = a%v
        r%g = 0 / r%v
#  if _DERIV_ID == _GRADGRAD
        r%gg = 0 / r%v
#  elif _DERIV_ID == _DIVGRAD
        r%dg = 0 / r%v
#  endif
    end if
#endif
end function _PROC
#undef _PROC


#if _TYPE_ID != _INTEGER
#  define _PROC _TYPE_UNARY_OP(sqrt)
elemental function _PROC(x) result(r)
    class(_NAME), intent(in) :: x
    type(_NAME) :: r

    _ELEM_TYPE :: f1
#  if _DERIV_ID > _GRAD
    _ELEM_TYPE :: f2
#  endif
#  if _DERIV_ID == _GRADGRAD
    integer :: i, lo, up
#  endif

    r%v = sqrt(x%v)
    f1 = 1 / (2 * r%v)
    r%g = f1 * x%g
#  if _DERIV_ID > _GRAD
    f2 = -2 * f1**2
#  endif
#  if _DERIV_ID == _GRADGRAD
    allocate(r%gg(size(x%gg)))
    up = 0
    do i = 1, size(r%g)
        lo = up + 1
        up = up + i
        r%gg(lo:up) = f1 * x%gg(lo:up) + f2 * r%g(i) * x%g(:i)
    end do
#  elif _DERIV_ID == _DIVGRAD
    r%dg = f1 * x%dg + f2 * dot_product(r%g, x%g)
#  endif
end function _PROC
#  undef _PROC


#  define _PROC _TYPE_UNARY_OP(exp)
elemental function _PROC(x) result(r)
    class(_NAME), intent(in) :: x
    type(_NAME) :: r

#  if _DERIV_ID == _GRADGRAD
    integer :: i, lo, up
#  endif

    r%v = exp(x%v)
    r%g = r%v * x%g
#  if _DERIV_ID == _GRADGRAD
    allocate(r%gg(size(x%gg)))
    up = 0
    do i = 1, size(r%g)
        lo = up + 1
        up = up + i
        r%gg(lo:up) = r%v * x%gg(lo:up) + r%g(i) * x%g(:i)
    end do
#  elif _DERIV_ID == _DIVGRAD
    r%dg = r%v * x%dg + dot_product(r%g, x%g)
#  endif
end function _PROC
#  undef _PROC


#  define _PROC _TYPE_UNARY_OP(log)
elemental function _PROC(x) result(r)
    class(_NAME), intent(in) :: x
    type(_NAME) :: r

    _ELEM_TYPE :: f
#  if _DERIV_ID == _GRADGRAD
    integer :: i, lo, up
#  endif

    r%v = log(x%v)
    f = 1 / x%v
    r%g = f * x%g
#  if _DERIV_ID == _GRADGRAD
    allocate(r%gg(size(x%gg)))
    up = 0
    do i = 1, size(r%g)
        lo = up + 1
        up = up + i
        r%gg(lo:up) = f * x%gg(lo:up) - r%g(i) * r%g(:i)
    end do
#  elif _DERIV_ID == _DIVGRAD
    r%dg = f * x%dg - dot_product(r%g, r%g)
#  endif
end function _PROC
#  undef _PROC


#  define _PROC _TYPE_UNARY_OP(sin)
elemental function _PROC(x) result(r)
    class(_NAME), intent(in) :: x
    type(_NAME) :: r

    _ELEM_TYPE :: f
#  if _DERIV_ID == _GRADGRAD
    integer :: i, lo, up
#  endif

    r%v = sin(x%v)
    f = cos(x%v)
    r%g = f * x%g
#  if _DERIV_ID == _GRADGRAD
    allocate(r%gg(size(x%gg)))
    up = 0
    do i = 1, size(r%g)
        lo = up + 1
        up = up + i
        r%gg(lo:up) = f * x%gg(lo:up) - r%v * x%g(i) * x%g(:i)
    end do
#  elif _DERIV_ID == _DIVGRAD
    r%dg = f * x%dg - r%v * dot_product(x%g, x%g)
#  endif
end function _PROC
#  undef _PROC


#  define _PROC _TYPE_UNARY_OP(cos)
elemental function _PROC(x) result(r)
    class(_NAME), intent(in) :: x
    type(_NAME) :: r

    _ELEM_TYPE :: f
#  if _DERIV_ID == _GRADGRAD
    integer :: i, lo, up
#  endif

    r%v = cos(x%v)
    f = -sin(x%v)
    r%g = f * x%g
#  if _DERIV_ID == _GRADGRAD
    allocate(r%gg(size(x%gg)))
    up = 0
    do i = 1, size(r%g)
        lo = up + 1
        up = up + i
        r%gg(lo:up) = f * x%gg(lo:up) - r%v * x%g(i) * x%g(:i)
    end do
#  elif _DERIV_ID == _DIVGRAD
    r%dg = f * x%dg - r%v * dot_product(x%g, x%g)
#  endif
end function _PROC
#  undef _PROC


#  define _PROC _TYPE_UNARY_OP(tan)
elemental function _PROC(x) result(r)
    class(_NAME), intent(in) :: x
    type(_NAME) :: r

    _ELEM_TYPE :: f1
#  if _DERIV_ID > _GRAD
    _ELEM_TYPE :: f2
#  endif
#  if _DERIV_ID == _GRADGRAD
    integer :: i, lo, up
#  endif

    r%v = tan(x%v)
    f1 = 1 + r%v**2
    r%g = f1 * x%g
#  if _DERIV_ID > _GRAD
    f2 = 2 * r%v
#  endif
#  if _DERIV_ID == _GRADGRAD
    allocate(r%gg(size(x%gg)))
    up = 0
    do i = 1, size(r%g)
        lo = up + 1
        up = up + i
        r%gg(lo:up) = f1 * x%gg(lo:up) + f2 * r%g(i) * x%g(:i)
    end do
#  elif _DERIV_ID == _DIVGRAD
    r%dg = f1 * x%dg + f2 * dot_product(r%g, x%g)
#  endif
end function _PROC
#  undef _PROC


#  define _PROC _TYPE_UNARY_OP(asin)
elemental function _PROC(x) result(r)
    class(_NAME), intent(in) :: x
    type(_NAME) :: r

    _ELEM_TYPE :: f1, f2
#  if _DERIV_ID == _GRADGRAD
    integer :: i, lo, up
#  endif

    r%v = asin(x%v)
    f2 = 1 / (1 - x%v**2)
    f1 = sqrt(f2)
    r%g = f1 * x%g
#  if _DERIV_ID > _GRAD
    f2 = f2 * x%v
#  endif
#  if _DERIV_ID == _GRADGRAD
    allocate(r%gg(size(x%gg)))
    up = 0
    do i = 1, size(r%g)
        lo = up + 1
        up = up + i
        r%gg(lo:up) = f1 * x%gg(lo:up) + f2 * r%g(i) * x%g(:i)
    end do
#  elif _DERIV_ID == _DIVGRAD
    r%dg = f1 * x%dg + f2 * dot_product(r%g, x%g)
#  endif
end function _PROC
#  undef _PROC


#  define _PROC _TYPE_UNARY_OP(acos)
elemental function _PROC(x) result(r)
    class(_NAME), intent(in) :: x
    type(_NAME) :: r

    _ELEM_TYPE :: f1, f2
#  if _DERIV_ID == _GRADGRAD
    integer :: i, lo, up
#  endif

    r%v = acos(x%v)
    f2 = 1 / (1 - x%v**2)
    f1 = -sqrt(f2)
    r%g = f1 * x%g
#  if _DERIV_ID > _GRAD
    f2 = f2 * x%v
#  endif
#  if _DERIV_ID == _GRADGRAD
    allocate(r%gg(size(x%gg)))
    up = 0
    do i = 1, size(r%g)
        lo = up + 1
        up = up + i
        r%gg(lo:up) = f1 * x%gg(lo:up) + f2 * r%g(i) * x%g(:i)
    end do
#  elif _DERIV_ID == _DIVGRAD
    r%dg = f1 * x%dg + f2 * dot_product(r%g, x%g)
#  endif
end function _PROC
#  undef _PROC


#  define _PROC _TYPE_UNARY_OP(atan)
elemental function _PROC(x) result(r)
    class(_NAME), intent(in) :: x
    type(_NAME) :: r

    _ELEM_TYPE :: f1
#  if _DERIV_ID > _GRAD
    _ELEM_TYPE :: f2
#  endif
#  if _DERIV_ID == _GRADGRAD
    integer :: i, lo, up
#  endif

    r%v = atan(x%v)
    f1 = 1 / (1 + x%v**2)
    r%g = f1 * x%g
#  if _DERIV_ID > _GRAD
    f2 = -2 * x%v
#  endif
#  if _DERIV_ID == _GRADGRAD
    allocate(r%gg(size(x%gg)))
    up = 0
    do i = 1, size(r%g)
        lo = up + 1
        up = up + i
        r%gg(lo:up) = f1 * x%gg(lo:up) + f2 * r%g(i) * r%g(:i)
    end do
#  elif _DERIV_ID == _DIVGRAD
    r%dg = f1 * x%dg + f2 * dot_product(r%g, r%g)
#  endif
end function _PROC
#  undef _PROC


#  define _PROC _TYPE_UNARY_OP(sinh)
elemental function _PROC(x) result(r)
    class(_NAME), intent(in) :: x
    type(_NAME) :: r

    _ELEM_TYPE :: f
#  if _DERIV_ID == _GRADGRAD
    integer :: i, lo, up
#  endif

    r%v = sinh(x%v)
    f = cosh(x%v)
    r%g = f * x%g
#  if _DERIV_ID == _GRADGRAD
    allocate(r%gg(size(x%gg)))
    up = 0
    do i = 1, size(r%g)
        lo = up + 1
        up = up + i
        r%gg(lo:up) = f * x%gg(lo:up) + r%v * x%g(i) * x%g(:i)
    end do
#  elif _DERIV_ID == _DIVGRAD
    r%dg = f * x%dg + r%v * dot_product(x%g, x%g)
#  endif
end function _PROC
#  undef _PROC


#  define _PROC _TYPE_UNARY_OP(cosh)
elemental function _PROC(x) result(r)
    class(_NAME), intent(in) :: x
    type(_NAME) :: r

    _ELEM_TYPE :: f
#  if _DERIV_ID == _GRADGRAD
    integer :: i, lo, up
#  endif

    r%v = cosh(x%v)
    f = sinh(x%v)
    r%g = f * x%g
#  if _DERIV_ID == _GRADGRAD
    allocate(r%gg(size(x%gg)))
    up = 0
    do i = 1, size(r%g)
        lo = up + 1
        up = up + i
        r%gg(lo:up) = f * x%gg(lo:up) + r%v * x%g(i) * x%g(:i)
    end do
#  elif _DERIV_ID == _DIVGRAD
    r%dg = f * x%dg + r%v * dot_product(x%g, x%g)
#  endif
end function _PROC
#  undef _PROC


#  define _PROC _TYPE_UNARY_OP(tanh)
elemental function _PROC(x) result(r)
    class(_NAME), intent(in) :: x
    type(_NAME) :: r

    _ELEM_TYPE :: f1
#  if _DERIV_ID > _GRAD
    _ELEM_TYPE :: f2
#  endif
#  if _DERIV_ID == _GRADGRAD
    integer :: i, lo, up
#  endif

    r%v = tanh(x%v)
    f1 = 1 - r%v**2
    r%g = f1 * x%g
#  if _DERIV_ID > _GRAD
    f2 = -2 * r%v
#  endif
#  if _DERIV_ID == _GRADGRAD
    allocate(r%gg(size(x%gg)))
    up = 0
    do i = 1, size(r%g)
        lo = up + 1
        up = up + i
        r%gg(lo:up) = f1 * x%gg(lo:up) + f2 * r%g(i) * x%g(:i)
    end do
#  elif _DERIV_ID == _DIVGRAD
    r%dg = f1 * x%dg + f2 * dot_product(r%g, x%g)
#  endif
end function _PROC
#  undef _PROC


#  define _PROC _TYPE_UNARY_OP(asinh)
elemental function _PROC(x) result(r)
    class(_NAME), intent(in) :: x
    type(_NAME) :: r

    _ELEM_TYPE :: f1, f2
#  if _DERIV_ID == _GRADGRAD
    integer :: i, lo, up
#  endif

    r%v = asinh(x%v)
    f2 = 1 / (1 + x%v**2)
    f1 = sqrt(f2)
    r%g = f1 * x%g
#  if _DERIV_ID > _GRAD
    f2 = -f2 * x%v
#  endif
#  if _DERIV_ID == _GRADGRAD
    allocate(r%gg(size(x%gg)))
    up = 0
    do i = 1, size(r%g)
        lo = up + 1
        up = up + i
        r%gg(lo:up) = f1 * x%gg(lo:up) + f2 * r%g(i) * x%g(:i)
    end do
#  elif _DERIV_ID == _DIVGRAD
    r%dg = f1 * x%dg + f2 * dot_product(r%g, x%g)
#  endif
end function _PROC
#  undef _PROC


#  define _PROC _TYPE_UNARY_OP(acosh)
elemental function _PROC(x) result(r)
    class(_NAME), intent(in) :: x
    type(_NAME) :: r

    _ELEM_TYPE :: f1, f2
#  if _DERIV_ID == _GRADGRAD
    integer :: i, lo, up
#  endif

    r%v = acosh(x%v)
    f2 = -1 / (1 - x%v**2)
    f1 = sqrt(f2)
    r%g = f1 * x%g
#  if _DERIV_ID > _GRAD
    f2 = -f2 * x%v
#  endif
#  if _DERIV_ID == _GRADGRAD
    allocate(r%gg(size(x%gg)))
    up = 0
    do i = 1, size(r%g)
        lo = up + 1
        up = up + i
        r%gg(lo:up) = f1 * x%gg(lo:up) + f2 * r%g(i) * x%g(:i)
    end do
#  elif _DERIV_ID == _DIVGRAD
    r%dg = f1 * x%dg + f2 * dot_product(r%g, x%g)
#  endif
end function _PROC
#  undef _PROC


#  define _PROC _TYPE_UNARY_OP(atanh)
elemental function _PROC(x) result(r)
    class(_NAME), intent(in) :: x
    type(_NAME) :: r

    _ELEM_TYPE :: f1
#  if _DERIV_ID > _GRAD
    _ELEM_TYPE :: f2
#  endif
#  if _DERIV_ID == _GRADGRAD
    integer :: i, lo, up
#  endif

    r%v = atanh(x%v)
    f1 = 1 / (1 - x%v**2)
    r%g = f1 * x%g
#  if _DERIV_ID > _GRAD
    f2 = 2 * x%v
#  endif
#  if _DERIV_ID == _GRADGRAD
    allocate(r%gg(size(x%gg)))
    up = 0
    do i = 1, size(r%g)
        lo = up + 1
        up = up + i
        r%gg(lo:up) = f1 * x%gg(lo:up) + f2 * r%g(i) * r%g(:i)
    end do
#  elif _DERIV_ID == _DIVGRAD
    r%dg = f1 * x%dg + f2 * dot_product(r%g, r%g)
#  endif
end function _PROC
#  undef _PROC
#endif


#if _TYPE_ID == _REAL
#  define _PROC _TYPE_UNARY_OP(atan2)
elemental function _PROC(y, x) result(r)
    class(_NAME), intent(in) :: y, x
    type(_NAME) :: r

    _ELEM_TYPE :: f, f1, f2
#  if _DERIV_ID > _GRAD
    _ELEM_TYPE :: f3, f4
#  endif
#  if _DERIV_ID == _GRADGRAD
    integer :: i, lo, up
#  endif

    r%v = atan2(y%v, x%v)
    f = 1 / (y%v**2 + x%v**2)
    f1 = x%v * f
    f2 = y%v * f
    r%g = f1 * y%g - f2 * x%g
#  if _DERIV_ID > _GRAD
    f3 = 2 * f1 * f2
    f4 = f1**2 - f2**2
#  endif
#  if _DERIV_ID == _GRADGRAD
    allocate(r%gg(min(size(y%gg), size(x%gg))))
    up = 0
    do i = 1, size(r%g)
        lo = up + 1
        up = up + i
        r%gg(lo:up) = ( &
            f1 * y%gg(lo:up) &
            + (f3 * y%g(i) + f4 * x%g(i)) * y%g(:i) &
            + (f4 * y%g(i) - f3 * x%g(i)) * x%g(:i) &
            - f2 * x%gg(lo:up) &
        )
    end do
#  elif _DERIV_ID == _DIVGRAD
    r%dg = ( &
        f1 * y%dg &
        + f3 * (dot_product(y%g, y%g) - dot_product(x%g, x%g)) &
        + 2 * f4 * dot_product(y%g, x%g) &
        - f2 * x%dg &
    )
#  endif
end function _PROC
#  undef _PROC


#  define _PROC _TYPE_UNARY_OP(hypot)
elemental function _PROC(x, y) result(r)
    class(_NAME), intent(in) :: x, y
    type(_NAME) :: r

    _ELEM_TYPE :: f
#  if _DERIV_ID == _GRADGRAD
    integer :: i, lo, up
#  endif

    r%v = hypot(x%v, y%v)
    f = 1 / r%v
    r%g = f * (x%v * x%g + y%v * y%g)
#  if _DERIV_ID == _GRADGRAD
    allocate(r%gg(min(size(x%gg), size(y%gg))))
    up = 0
    do i = 1, size(r%g)
        lo = up + 1
        up = up + i
        r%gg(lo:up) = f * ( &
            x%v * x%gg(lo:up) &
            + y%v * y%gg(lo:up) &
            + x%g(i) * x%g(:i) &
            + y%g(i) * y%g(:i) &
            - r%g(i) * r%g(:i) &
        )
    end do
#  elif _DERIV_ID == _DIVGRAD
    r%dg = f * ( &
        x%v * x%dg &
        + y%v * y%dg &
        + dot_product(x%g, x%g) &
        + dot_product(y%g, y%g) &
        - dot_product(r%g, r%g) &
    )
#  endif
end function _PROC
#  undef _PROC


#  define _PROC _TYPE_UNARY_OP(log10)
elemental function _PROC(x) result(r)
    class(_NAME), intent(in) :: x
    type(_NAME) :: r

    _ELEM_TYPE, parameter :: LOG_10 = log(_CONV(10))
    _ELEM_TYPE :: f
#  if _DERIV_ID == _GRADGRAD
    integer :: i, lo, up
#  endif

    r%v = log10(x%v)
    f = 1 / (x%v * LOG_10)
    r%g = f * x%g
#  if _DERIV_ID == _GRADGRAD
    allocate(r%gg(size(x%gg)))
    up = 0
    do i = 1, size(r%g)
        lo = up + 1
        up = up + i
        r%gg(lo:up) = f * x%gg(lo:up) - LOG_10 * r%g(i) * r%g(:i)
    end do
#  elif _DERIV_ID == _DIVGRAD
    r%dg = f * x%dg - LOG_10 * dot_product(r%g, r%g)
#  endif
end function _PROC
#  undef _PROC


#  define _PROC _TYPE_UNARY_OP(erf)
elemental function _PROC(x) result(r)
    class(_NAME), intent(in) :: x
    type(_NAME) :: r

    _ELEM_TYPE, parameter :: PI = acos(_CONV(-1))
    _ELEM_TYPE :: f1
#  if _DERIV_ID > _GRAD
    _ELEM_TYPE :: f2
#  endif
#  if _DERIV_ID == _GRADGRAD
    integer :: i, lo, up
#  endif

    r%v = erf(x%v)
    f1 = 2 * exp(-x%v**2) / sqrt(PI)
    r%g = f1 * x%g
#  if _DERIV_ID > _GRAD
    f2 = -2 * x%v
#  endif
#  if _DERIV_ID == _GRADGRAD
    allocate(r%gg(size(x%gg)))
    up = 0
    do i = 1, size(r%g)
        lo = up + 1
        up = up + i
        r%gg(lo:up) = f1 * x%gg(lo:up) + f2 * r%g(i) * x%g(:i)
    end do
#  elif _DERIV_ID == _DIVGRAD
    r%dg = f1 * x%dg + f2 * dot_product(r%g, x%g)
#  endif
end function _PROC
#  undef _PROC


#  define _PROC _TYPE_UNARY_OP(erfc)
elemental function _PROC(x) result(r)
    class(_NAME), intent(in) :: x
    type(_NAME) :: r

    _ELEM_TYPE, parameter :: PI = acos(_CONV(-1))
    _ELEM_TYPE :: f1
#  if _DERIV_ID > _GRAD
    _ELEM_TYPE :: f2
#  endif
#  if _DERIV_ID == _GRADGRAD
    integer :: i, lo, up
#  endif

    r%v = erfc(x%v)
    f1 = -2 * exp(-x%v**2) / sqrt(PI)
    r%g = f1 * x%g
#  if _DERIV_ID > _GRAD
    f2 = -2 * x%v
#  endif
#  if _DERIV_ID == _GRADGRAD
    allocate(r%gg(size(x%gg)))
    up = 0
    do i = 1, size(r%g)
        lo = up + 1
        up = up + i
        r%gg(lo:up) = f1 * x%gg(lo:up) + f2 * r%g(i) * x%g(:i)
    end do
#  elif _DERIV_ID == _DIVGRAD
    r%dg = f1 * x%dg + f2 * dot_product(r%g, x%g)
#  endif
end function _PROC
#  undef _PROC


#  define _PROC _TYPE_UNARY_OP(erfc_scaled)
elemental function _PROC(x) result(r)
    class(_NAME), intent(in) :: x
    type(_NAME) :: r

    _ELEM_TYPE, parameter :: PI = acos(_CONV(-1))
    _ELEM_TYPE :: f1
#  if _DERIV_ID > _GRAD
    _ELEM_TYPE :: f2
#  endif
#  if _DERIV_ID == _GRADGRAD
    integer :: i, lo, up
#  endif

    r%v = erfc_scaled(x%v)
    f1 = 2 * x%v * r%v - 2 / sqrt(PI)
    r%g = f1 * x%g
#  if _DERIV_ID > _GRAD
    f2 = 2 * (f1 * x%v + r%v)
#  endif
#  if _DERIV_ID == _GRADGRAD
    allocate(r%gg(size(x%gg)))
    up = 0
    do i = 1, size(r%g)
        lo = up + 1
        up = up + i
        r%gg(lo:up) = f1 * x%gg(lo:up) + f2 * x%g(i) * x%g(:i)
    end do
#  elif _DERIV_ID == _DIVGRAD
    r%dg = f1 * x%dg + f2 * dot_product(x%g, x%g)
#  endif
end function _PROC
#  undef _PROC
#endif
