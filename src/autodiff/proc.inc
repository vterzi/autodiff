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

    r%val = val
    r%grad = grad
#if _DERIV_ID == _GRADGRAD
    n = size(grad)
    n1 = size(gradgrad, 1)
    n2 = size(gradgrad, 2)
    allocate(r%gradgrad(n * (n + 1) / 2))
    if (upper) then
        do i = 1, n
            lo = up + i
            up = up + 1
            if (i <= n2) then
                if (i <= n1) then
                    r%gradgrad(lo:up) = gradgrad(:i, i)
                else
                    up_ = up + n1 - i
                    r%gradgrad(lo:up_) = gradgrad(:n1, i)
                    up_ = up_ + 1
                    r%gradgrad(up_:up) = 0
                end if
            else
                r%gradgrad(lo:up) = 0
            end if
        end do
    else
        do i = 1, n
            lo = up + i
            up = up + 1
            if (i <= n1) then
                if (i <= n2) then
                    r%gradgrad(lo:up) = gradgrad(i, :i)
                else
                    up_ = up + n2 - i
                    r%gradgrad(lo:up_) = gradgrad(i, :n2)
                    up_ = up_ + 1
                    r%gradgrad(up_:up) = 0
                end if
            else
                r%gradgrad(lo:up) = 0
            end if
        end do
    end if
#elif _DERIV_ID == _DIVGRAD
    r%divgrad = divgrad
#endif
end function _PROC
#undef _PROC


#define _PROC _TYPE_UNARY_OP(get_val)
pure function _PROC(x) result(val)
    class(_NAME), intent(in) :: x
    _ELEM_TYPE :: val

    val = x%val
end function _PROC
#undef _PROC


#define _PROC _TYPE_UNARY_OP(get_grad)
pure function _PROC(x) result(grad)
    class(_NAME), intent(in) :: x
    _ELEM_TYPE :: grad(size(x%grad))

    grad = x%grad
end function _PROC
#undef _PROC


#if _DERIV_ID == _GRADGRAD
#  define _PROC _TYPE_UNARY_OP(get_gradgrad)
pure function _PROC(x) result(gradgrad)
    class(_NAME), intent(in) :: x
    _ELEM_TYPE :: gradgrad(size(x%grad), size(x%grad))

    integer :: n, i1, i2, lo, up

    n = size(x%grad)
    up = 0
    do i1 = 1, n
        lo = up + i1
        up = up + 1
        gradgrad(:i1, i1) = x%gradgrad(lo:up)
    end do
    do i1 = 2, n
        do i2 = 1, i1 - 1
            gradgrad(i1, i2) = gradgrad(i2, i1)
        end do
    end do
end function _PROC
#  undef _PROC
#endif


#if _DERIV_ID > _GRAD
#  define _PROC _TYPE_UNARY_OP(get_divgrad)
pure function _PROC(x) result(divgrad)
    class(_NAME), intent(in) :: x
    _ELEM_TYPE :: divgrad

#  if _DERIV_ID == _GRADGRAD
    integer :: i, idx
#  endif

#  if _DERIV_ID == _GRADGRAD
    divgrad = 0
    idx = 0
    do i = 1, size(x%grad)
        idx = idx + i
        divgrad = divgrad + x%gradgrad(idx)
    end do
#  elif _DERIV_ID == _DIVGRAD
    divgrad = x%divgrad
#  endif
end function _PROC
#  undef _PROC
#endif

! -----------------------------------------------------------------------------

#define _PROC _TYPE_BINARY_OP(eq)
elemental function _PROC(x, y) result(r)
    class(_NAME), intent(in) :: x, y
    logical :: r

    r = x%val == y%val .and. all(x%grad == y%grad)
#if _DERIV_ID == _GRADGRAD
    r = r .and. all(x%gradgrad == y%gradgrad)
#elif _DERIV_ID == _DIVGRAD
    r = r .and. x%divgrad == y%divgrad
#endif
end function _PROC
#undef _PROC


#define _PROC _TYPE_BINARY_OP(ne)
elemental function _PROC(x, y) result(r)
    class(_NAME), intent(in) :: x, y
    logical :: r

    r = x%val /= y%val .or. any(x%grad /= y%grad)
#if _DERIV_ID == _GRADGRAD
    r = r .or. any(x%gradgrad /= y%gradgrad)
#elif _DERIV_ID == _DIVGRAD
    r = r .or. x%divgrad /= y%divgrad
#endif
end function _PROC
#undef _PROC


#define _PROC _TYPE_UNARY_OP(pos)
elemental function _PROC(x) result(r)
    class(_NAME), intent(in) :: x
    type(_NAME) :: r

    r%val = x%val
    r%grad = x%grad
#if _DERIV_ID == _GRADGRAD
    r%gradgrad = x%gradgrad
#elif _DERIV_ID == _DIVGRAD
    r%divgrad = x%divgrad
#endif
end function _PROC
#undef _PROC


#define _PROC _TYPE_UNARY_OP(neg)
elemental function _PROC(x) result(r)
    class(_NAME), intent(in) :: x
    type(_NAME) :: r

    r%val = -x%val
    r%grad = -x%grad
#if _DERIV_ID == _GRADGRAD
    r%gradgrad = -x%gradgrad
#elif _DERIV_ID == _DIVGRAD
    r%divgrad = -x%divgrad
#endif
end function _PROC
#undef _PROC


#define _PROC _TYPE_BINARY_OP(add)
elemental function _PROC(x, y) result(r)
    class(_NAME), intent(in) :: x, y
    type(_NAME) :: r

    r%val = x%val + y%val
    r%grad = x%grad + y%grad
#if _DERIV_ID == _GRADGRAD
    r%gradgrad = x%gradgrad + y%gradgrad
#elif _DERIV_ID == _DIVGRAD
    r%divgrad = x%divgrad + y%divgrad
#endif
end function _PROC
#undef _PROC


#define _PROC _TYPE_BINARY_OP(sub)
elemental function _PROC(x, y) result(r)
    class(_NAME), intent(in) :: x, y
    type(_NAME) :: r

    r%val = x%val - y%val
    r%grad = x%grad - y%grad
#if _DERIV_ID == _GRADGRAD
    r%gradgrad = x%gradgrad - y%gradgrad
#elif _DERIV_ID == _DIVGRAD
    r%divgrad = x%divgrad - y%divgrad
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

    r%val = x%val * y%val
    r%grad = x%grad * y%val + x%val * y%grad
#if _DERIV_ID == _GRADGRAD
    allocate(r%gradgrad(min(size(x%gradgrad), size(y%gradgrad))))
    up = 0
    do i = 1, size(r%grad)
        lo = up + i
        up = up + 1
        r%gradgrad(lo:up) = ( &
            x%gradgrad(lo:up) * y%val &
            + x%grad(:i) * y%grad(i) &
            + x%grad(i) * y%grad(:i) &
            + x%val * y%gradgrad(lo:up) &
        )
    end do
#elif _DERIV_ID == _DIVGRAD
    r%divgrad = ( &
        x%divgrad * y%val &
        + 2 * dot_product(x%grad, y%grad) &
        + x%val * y%divgrad &
    )
#endif
end function _PROC
#undef _PROC


#define _PROC _TYPE_BINARY_OP(div)
elemental function _PROC(x, y) result(r)
    class(_NAME), intent(in) :: x, y
    type(_NAME) :: r

#if _TYPE_ID != _INTEGER
#  if _DERIV_ID == _GRADGRAD
    integer :: i, lo, up
    _ELEM_TYPE :: two_val
#  endif
    _ELEM_TYPE :: inv_val

    inv_val = 1 / y%val
    r%val = x%val * inv_val
    r%grad = (x%grad - r%val * y%grad) * inv_val
#  if _DERIV_ID == _GRADGRAD
    two_val = 2 * r%val
    allocate(r%gradgrad(min(size(x%gradgrad), size(y%gradgrad))))
    up = 0
    do i = 1, size(r%grad)
        lo = up + i
        up = up + 1
        r%gradgrad(lo:up) = inv_val * ( &
            x%gradgrad(lo:up) &
            + inv_val * ( &
                (two_val * y%grad(i) - x%grad(i)) * y%grad(:i) &
                - x%grad(:i) * y%grad(i) &
            ) &
            - r%val * y%gradgrad(lo:up) &
        )
    end do
#  elif _DERIV_ID == _DIVGRAD
    r%divgrad = inv_val * ( &
        x%divgrad &
        + 2 * inv_val * dot_product( &
            r%val * y%grad - x%grad, y%grad &
        ) &
        - r%val * y%divgrad &
    )
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
#  if _DERIV_ID == _GRADGRAD
    integer :: i, lo, up
#  endif
    _ELEM_TYPE :: inv_val, val_ratio, log_val
#  if _DERIV_ID > _GRAD
    _ELEM_TYPE :: temp1, temp2, temp3
#  endif

    r%val = x%val**y%val
    inv_val = 1 / x%val
    val_ratio = y%val * inv_val
    log_val = log(x%val)
#  if _DERIV_ID > _GRAD
    temp1 = val_ratio * (val_ratio - inv_val)
    temp2 = val_ratio * log_val + inv_val
    temp3 = log_val**2
#  endif
    val_ratio = val_ratio * r%val
    log_val = log_val * r%val
    r%grad = x%grad * val_ratio + log_val * y%grad
#  if _DERIV_ID == _GRADGRAD
    temp1 = temp1 * r%val
    temp2 = temp2 * r%val
    temp3 = temp3 * r%val
    allocate(r%gradgrad(min(size(x%gradgrad), size(y%gradgrad))))
    up = 0
    do i = 1, size(r%grad)
        lo = up + i
        up = up + 1
        r%gradgrad(lo:up) = ( &
            x%gradgrad(lo:up) * val_ratio &
            + x%grad(:i) * (x%grad(i) * temp1 + temp2 * y%grad(i)) &
            + (x%grad(i) * temp2 + temp3 * y%grad(i)) * y%grad(:i) &
            + log_val * y%gradgrad(lo:up) &
        )
    end do
#  elif _DERIV_ID == _DIVGRAD
    r%divgrad = ( &
        x%divgrad * val_ratio &
        + r%val * ( &
            temp1 * dot_product(x%grad, x%grad) &
            + 2 * temp2 * dot_product(x%grad, y%grad) &
            + temp3 * dot_product(y%grad, y%grad) &
        ) &
        + log_val * y%divgrad &
    )
#  endif
#else
    r = real(x)**real(y)
#endif
end function _PROC
#undef _PROC

! -----------------------------------------------------------------------------

#define _PROC _TYPE_UNARY_OP(kind)
elemental function _PROC(x) result(r)
    class(_NAME), intent(in) :: x
    integer :: r

    r = kind(x%val)
end function _PROC
#undef _PROC


#if _TYPE_ID != _COMPLEX
#  define _PROC _TYPE_UNARY_OP(sign)
elemental function _PROC(a, b) result(r)
    class(_NAME), intent(in) :: a, b
    type(_NAME) :: r

    if (a%val == sign(a%val, b%val)) then
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

    r%val = real(a%val)
    r%grad = real(a%grad)
#  if _DERIV_ID == _GRADGRAD
    r%gradgrad = real(a%gradgrad)
#  elif _DERIV_ID == _DIVGRAD
    r%divgrad = real(a%divgrad)
#  endif
end function _PROC
#  undef _PROC


#  define _PROC _TYPE_UNARY_OP(aimag)
elemental function _PROC(z) result(r)
    class(_NAME), intent(in) :: z
    type(_CAT3(_DERIV,R,_KIND_LABEL)) :: r

    r%val = aimag(z%val)
    r%grad = aimag(z%grad)
#  if _DERIV_ID == _GRADGRAD
    r%gradgrad = aimag(z%gradgrad)
#  elif _DERIV_ID == _DIVGRAD
    r%divgrad = aimag(z%divgrad)
#  endif
end function _PROC
#  undef _PROC


#  define _PROC _TYPE_UNARY_OP(conjg)
elemental function _PROC(z) result(r)
    class(_NAME), intent(in) :: z
    type(_NAME) :: r

    r%val = conjg(z%val)
    r%grad = conjg(z%grad)
#  if _DERIV_ID == _GRADGRAD
    r%gradgrad = conjg(z%gradgrad)
#  elif _DERIV_ID == _DIVGRAD
    r%divgrad = conjg(z%divgrad)
#  endif
end function _PROC
#  undef _PROC
#endif


#define _PROC _TYPE_UNARY_OP(abs)
elemental function _PROC(a) result(r)
    class(_NAME), intent(in) :: a
    type(_NAME) :: r

#if _TYPE_ID == _COMPLEX
    r = sqrt(a * conjg(a))
#else
    if (a%val > 0) then
        r = a
    else if (a%val < 0) then
        r = -a
    else
        r%val = a%val
        r%grad = 0 / r%val
#  if _DERIV_ID == _GRADGRAD
        r%gradgrad = 0 / r%val
#  elif _DERIV_ID == _DIVGRAD
        r%divgrad = 0 / r%val
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

    _ELEM_TYPE :: factor1
#  if _DERIV_ID > _GRAD
    _ELEM_TYPE :: factor2
#  endif
#  if _DERIV_ID == _GRADGRAD
    integer :: i, lo, up
#  endif

    r%val = sqrt(x%val)
    factor1 = 1 / (2 * r%val)
    r%grad = factor1 * x%grad
#  if _DERIV_ID > _GRAD
    factor2 = -2 * factor1**2
#  endif
#  if _DERIV_ID == _GRADGRAD
    allocate(r%gradgrad(size(x%gradgrad)))
    up = 0
    do i = 1, size(r%grad)
        lo = up + i
        up = up + 1
        r%gradgrad(lo:up) = ( &
            factor1 * x%gradgrad(lo:up) + factor2 * r%grad(i) * x%grad(:i) &
        )
    end do
#  elif _DERIV_ID == _DIVGRAD
    r%divgrad = factor1 * x%divgrad + factor2 * dot_product(r%grad, x%grad)
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

    r%val = exp(x%val)
    r%grad = r%val * x%grad
#  if _DERIV_ID == _GRADGRAD
    allocate(r%gradgrad(size(x%gradgrad)))
    up = 0
    do i = 1, size(r%grad)
        lo = up + i
        up = up + 1
        r%gradgrad(lo:up) = r%val * x%gradgrad(lo:up) + r%grad(i) * x%grad(:i)
    end do
#  elif _DERIV_ID == _DIVGRAD
    r%divgrad = r%val * x%divgrad + dot_product(r%grad, x%grad)
#  endif
end function _PROC
#  undef _PROC


#  define _PROC _TYPE_UNARY_OP(log)
elemental function _PROC(x) result(r)
    class(_NAME), intent(in) :: x
    type(_NAME) :: r

    _ELEM_TYPE :: factor
#  if _DERIV_ID == _GRADGRAD
    integer :: i, lo, up
#  endif

    r%val = log(x%val)
    factor = 1 / x%val
    r%grad = factor * x%grad
#  if _DERIV_ID == _GRADGRAD
    allocate(r%gradgrad(size(x%gradgrad)))
    up = 0
    do i = 1, size(r%grad)
        lo = up + i
        up = up + 1
        r%gradgrad(lo:up) = factor * x%gradgrad(lo:up) - r%grad(i) * r%grad(:i)
    end do
#  elif _DERIV_ID == _DIVGRAD
    r%divgrad = factor * x%divgrad - dot_product(r%grad, r%grad)
#  endif
end function _PROC
#  undef _PROC
#endif


#if _TYPE_ID == _REAL
#  define _PROC _TYPE_UNARY_OP(log10)
elemental function _PROC(x) result(r)
    class(_NAME), intent(in) :: x
    type(_NAME) :: r

    _ELEM_TYPE, parameter :: LOG_10 = log(_CONV(10))
    _ELEM_TYPE :: factor
#  if _DERIV_ID == _GRADGRAD
    integer :: i, lo, up
#  endif

    r%val = log10(x%val)
    factor = 1 / (x%val * LOG_10)
    r%grad = factor * x%grad
#  if _DERIV_ID == _GRADGRAD
    allocate(r%gradgrad(size(x%gradgrad)))
    up = 0
    do i = 1, size(r%grad)
        lo = up + i
        up = up + 1
        r%gradgrad(lo:up) = ( &
            factor * x%gradgrad(lo:up) - LOG_10 * r%grad(i) * r%grad(:i) &
        )
    end do
#  elif _DERIV_ID == _DIVGRAD
    r%divgrad = factor * x%divgrad - LOG_10 * dot_product(r%grad, r%grad)
#  endif
end function _PROC
#  undef _PROC


#  define _PROC _TYPE_UNARY_OP(erf)
elemental function _PROC(x) result(r)
    class(_NAME), intent(in) :: x
    type(_NAME) :: r

    _ELEM_TYPE, parameter :: PI = acos(_CONV(-1.0))
    _ELEM_TYPE :: factor1
#  if _DERIV_ID > _GRAD
    _ELEM_TYPE :: factor2
#  endif
#  if _DERIV_ID == _GRADGRAD
    integer :: i, lo, up
#  endif

    r%val = erf(x%val)
    factor1 = 2 * exp(-x%val**2) / sqrt(PI)
    r%grad = factor1 * x%grad
#  if _DERIV_ID > _GRAD
    factor2 = -2 * x%val
#  endif
#  if _DERIV_ID == _GRADGRAD
    allocate(r%gradgrad(size(x%gradgrad)))
    up = 0
    do i = 1, size(r%grad)
        lo = up + i
        up = up + 1
        r%gradgrad(lo:up) = ( &
            factor1 * x%gradgrad(lo:up) + factor2 * r%grad(i) * x%grad(:i) &
        )
    end do
#  elif _DERIV_ID == _DIVGRAD
    r%divgrad = factor1 * x%divgrad + factor2 * dot_product(r%grad, x%grad)
#  endif
end function _PROC
#  undef _PROC


#  define _PROC _TYPE_UNARY_OP(erfc)
elemental function _PROC(x) result(r)
    class(_NAME), intent(in) :: x
    type(_NAME) :: r

    _ELEM_TYPE, parameter :: PI = acos(_CONV(-1.0))
    _ELEM_TYPE :: factor1
#  if _DERIV_ID > _GRAD
    _ELEM_TYPE :: factor2
#  endif
#  if _DERIV_ID == _GRADGRAD
    integer :: i, lo, up
#  endif

    r%val = erfc(x%val)
    factor1 = -2 * exp(-x%val**2) / sqrt(PI)
    r%grad = factor1 * x%grad
#  if _DERIV_ID > _GRAD
    factor2 = -2 * x%val
#  endif
#  if _DERIV_ID == _GRADGRAD
    allocate(r%gradgrad(size(x%gradgrad)))
    up = 0
    do i = 1, size(r%grad)
        lo = up + i
        up = up + 1
        r%gradgrad(lo:up) = ( &
            factor1 * x%gradgrad(lo:up) + factor2 * r%grad(i) * x%grad(:i) &
        )
    end do
#  elif _DERIV_ID == _DIVGRAD
    r%divgrad = factor1 * x%divgrad + factor2 * dot_product(r%grad, x%grad)
#  endif
end function _PROC
#  undef _PROC


#  define _PROC _TYPE_UNARY_OP(erfc_scaled)
elemental function _PROC(x) result(r)
    class(_NAME), intent(in) :: x
    type(_NAME) :: r

    _ELEM_TYPE, parameter :: PI = acos(_CONV(-1.0))
    _ELEM_TYPE :: factor1
#  if _DERIV_ID > _GRAD
    _ELEM_TYPE :: factor2
#  endif
#  if _DERIV_ID == _GRADGRAD
    integer :: i, lo, up
#  endif

    r%val = erfc_scaled(x%val)
    factor1 = 2 * x%val * r%val - 2 / sqrt(PI)
    r%grad = factor1 * x%grad
#  if _DERIV_ID > _GRAD
    factor2 = 2 * (factor1 * x%val + r%val)
#  endif
#  if _DERIV_ID == _GRADGRAD
    allocate(r%gradgrad(size(x%gradgrad)))
    up = 0
    do i = 1, size(r%grad)
        lo = up + i
        up = up + 1
        r%gradgrad(lo:up) = ( &
            factor1 * x%gradgrad(lo:up) + factor2 * x%grad(i) * x%grad(:i) &
        )
    end do
#  elif _DERIV_ID == _DIVGRAD
    r%divgrad = factor1 * x%divgrad + factor2 * dot_product(x%grad, x%grad)
#  endif
end function _PROC
#  undef _PROC
#endif


#if _TYPE_ID != _INTEGER
#  define _PROC _TYPE_UNARY_OP(sin)
elemental function _PROC(x) result(r)
    class(_NAME), intent(in) :: x
    type(_NAME) :: r

    _ELEM_TYPE :: factor
#  if _DERIV_ID == _GRADGRAD
    integer :: i, lo, up
#  endif

    r%val = sin(x%val)
    factor = cos(x%val)
    r%grad = factor * x%grad
#  if _DERIV_ID == _GRADGRAD
    allocate(r%gradgrad(size(x%gradgrad)))
    up = 0
    do i = 1, size(r%grad)
        lo = up + i
        up = up + 1
        r%gradgrad(lo:up) = ( &
            factor * x%gradgrad(lo:up) - r%val * x%grad(i) * x%grad(:i) &
        )
    end do
#  elif _DERIV_ID == _DIVGRAD
    r%divgrad = factor * x%divgrad - r%val * dot_product(x%grad, x%grad)
#  endif
end function _PROC
#  undef _PROC


#  define _PROC _TYPE_UNARY_OP(cos)
elemental function _PROC(x) result(r)
    class(_NAME), intent(in) :: x
    type(_NAME) :: r

    _ELEM_TYPE :: factor
#  if _DERIV_ID == _GRADGRAD
    integer :: i, lo, up
#  endif

    r%val = cos(x%val)
    factor = -sin(x%val)
    r%grad = factor * x%grad
#  if _DERIV_ID == _GRADGRAD
    allocate(r%gradgrad(size(x%gradgrad)))
    up = 0
    do i = 1, size(r%grad)
        lo = up + i
        up = up + 1
        r%gradgrad(lo:up) = ( &
            factor * x%gradgrad(lo:up) - r%val * x%grad(i) * x%grad(:i) &
        )
    end do
#  elif _DERIV_ID == _DIVGRAD
    r%divgrad = factor * x%divgrad - r%val * dot_product(x%grad, x%grad)
#  endif
end function _PROC
#  undef _PROC


#  define _PROC _TYPE_UNARY_OP(tan)
elemental function _PROC(x) result(r)
    class(_NAME), intent(in) :: x
    type(_NAME) :: r

    _ELEM_TYPE :: factor1
#  if _DERIV_ID > _GRAD
    _ELEM_TYPE :: factor2
#  endif
#  if _DERIV_ID == _GRADGRAD
    integer :: i, lo, up
#  endif

    r%val = tan(x%val)
    factor1 = 1 + r%val**2
    r%grad = factor1 * x%grad
#  if _DERIV_ID > _GRAD
    factor2 = 2 * r%val
#  endif
#  if _DERIV_ID == _GRADGRAD
    allocate(r%gradgrad(size(x%gradgrad)))
    up = 0
    do i = 1, size(r%grad)
        lo = up + i
        up = up + 1
        r%gradgrad(lo:up) = ( &
            factor1 * x%gradgrad(lo:up) + factor2 * r%grad(i) * x%grad(:i) &
        )
    end do
#  elif _DERIV_ID == _DIVGRAD
    r%divgrad = factor1 * x%divgrad + factor2 * dot_product(r%grad, x%grad)
#  endif
end function _PROC
#  undef _PROC


#  define _PROC _TYPE_UNARY_OP(asin)
elemental function _PROC(x) result(r)
    class(_NAME), intent(in) :: x
    type(_NAME) :: r

    _ELEM_TYPE :: factor1, factor2
#  if _DERIV_ID == _GRADGRAD
    integer :: i, lo, up
#  endif

    r%val = asin(x%val)
    factor2 = 1 / (1 - x%val**2)
    factor1 = sqrt(factor2)
    r%grad = factor1 * x%grad
#  if _DERIV_ID > _GRAD
    factor2 = factor2 * x%val
#  endif
#  if _DERIV_ID == _GRADGRAD
    allocate(r%gradgrad(size(x%gradgrad)))
    up = 0
    do i = 1, size(r%grad)
        lo = up + i
        up = up + 1
        r%gradgrad(lo:up) = ( &
            factor1 * x%gradgrad(lo:up) + factor2 * r%grad(i) * x%grad(:i) &
        )
    end do
#  elif _DERIV_ID == _DIVGRAD
    r%divgrad = factor1 * x%divgrad + factor2 * dot_product(r%grad, x%grad)
#  endif
end function _PROC
#  undef _PROC


#  define _PROC _TYPE_UNARY_OP(acos)
elemental function _PROC(x) result(r)
    class(_NAME), intent(in) :: x
    type(_NAME) :: r

    _ELEM_TYPE :: factor1, factor2
#  if _DERIV_ID == _GRADGRAD
    integer :: i, lo, up
#  endif

    r%val = acos(x%val)
    factor2 = 1 / (1 - x%val**2)
    factor1 = -sqrt(factor2)
    r%grad = factor1 * x%grad
#  if _DERIV_ID > _GRAD
    factor2 = factor2 * x%val
#  endif
#  if _DERIV_ID == _GRADGRAD
    allocate(r%gradgrad(size(x%gradgrad)))
    up = 0
    do i = 1, size(r%grad)
        lo = up + i
        up = up + 1
        r%gradgrad(lo:up) = ( &
            factor1 * x%gradgrad(lo:up) + factor2 * r%grad(i) * x%grad(:i) &
        )
    end do
#  elif _DERIV_ID == _DIVGRAD
    r%divgrad = factor1 * x%divgrad + factor2 * dot_product(r%grad, x%grad)
#  endif
end function _PROC
#  undef _PROC


#  define _PROC _TYPE_UNARY_OP(atan)
elemental function _PROC(x) result(r)
    class(_NAME), intent(in) :: x
    type(_NAME) :: r

    _ELEM_TYPE :: factor1
#  if _DERIV_ID > _GRAD
    _ELEM_TYPE :: factor2
#  endif
#  if _DERIV_ID == _GRADGRAD
    integer :: i, lo, up
#  endif

    r%val = atan(x%val)
    factor1 = 1 / (1 + x%val**2)
    r%grad = factor1 * x%grad
#  if _DERIV_ID > _GRAD
    factor2 = -2 * x%val
#  endif
#  if _DERIV_ID == _GRADGRAD
    allocate(r%gradgrad(size(x%gradgrad)))
    up = 0
    do i = 1, size(r%grad)
        lo = up + i
        up = up + 1
        r%gradgrad(lo:up) = ( &
            factor1 * x%gradgrad(lo:up) + factor2 * r%grad(i) * r%grad(:i) &
        )
    end do
#  elif _DERIV_ID == _DIVGRAD
    r%divgrad = factor1 * x%divgrad + factor2 * dot_product(r%grad, r%grad)
#  endif
end function _PROC
#  undef _PROC


#  define _PROC _TYPE_UNARY_OP(sinh)
elemental function _PROC(x) result(r)
    class(_NAME), intent(in) :: x
    type(_NAME) :: r

    _ELEM_TYPE :: factor
#  if _DERIV_ID == _GRADGRAD
    integer :: i, lo, up
#  endif

    r%val = sinh(x%val)
    factor = cosh(x%val)
    r%grad = factor * x%grad
#  if _DERIV_ID == _GRADGRAD
    allocate(r%gradgrad(size(x%gradgrad)))
    up = 0
    do i = 1, size(r%grad)
        lo = up + i
        up = up + 1
        r%gradgrad(lo:up) = ( &
            factor * x%gradgrad(lo:up) + r%val * x%grad(i) * x%grad(:i) &
        )
    end do
#  elif _DERIV_ID == _DIVGRAD
    r%divgrad = factor * x%divgrad + r%val * dot_product(x%grad, x%grad)
#  endif
end function _PROC
#  undef _PROC


#  define _PROC _TYPE_UNARY_OP(cosh)
elemental function _PROC(x) result(r)
    class(_NAME), intent(in) :: x
    type(_NAME) :: r

    _ELEM_TYPE :: factor
#  if _DERIV_ID == _GRADGRAD
    integer :: i, lo, up
#  endif

    r%val = cosh(x%val)
    factor = sinh(x%val)
    r%grad = factor * x%grad
#  if _DERIV_ID == _GRADGRAD
    allocate(r%gradgrad(size(x%gradgrad)))
    up = 0
    do i = 1, size(r%grad)
        lo = up + i
        up = up + 1
        r%gradgrad(lo:up) = ( &
            factor * x%gradgrad(lo:up) + r%val * x%grad(i) * x%grad(:i) &
        )
    end do
#  elif _DERIV_ID == _DIVGRAD
    r%divgrad = factor * x%divgrad + r%val * dot_product(x%grad, x%grad)
#  endif
end function _PROC
#  undef _PROC


#  define _PROC _TYPE_UNARY_OP(tanh)
elemental function _PROC(x) result(r)
    class(_NAME), intent(in) :: x
    type(_NAME) :: r

    _ELEM_TYPE :: factor1
#  if _DERIV_ID > _GRAD
    _ELEM_TYPE :: factor2
#  endif
#  if _DERIV_ID == _GRADGRAD
    integer :: i, lo, up
#  endif

    r%val = tanh(x%val)
    factor1 = 1 - r%val**2
    r%grad = factor1 * x%grad
#  if _DERIV_ID > _GRAD
    factor2 = -2 * r%val
#  endif
#  if _DERIV_ID == _GRADGRAD
    allocate(r%gradgrad(size(x%gradgrad)))
    up = 0
    do i = 1, size(r%grad)
        lo = up + i
        up = up + 1
        r%gradgrad(lo:up) = ( &
            factor1 * x%gradgrad(lo:up) + factor2 * r%grad(i) * x%grad(:i) &
        )
    end do
#  elif _DERIV_ID == _DIVGRAD
    r%divgrad = factor1 * x%divgrad + factor2 * dot_product(r%grad, x%grad)
#  endif
end function _PROC
#  undef _PROC


#  define _PROC _TYPE_UNARY_OP(asinh)
elemental function _PROC(x) result(r)
    class(_NAME), intent(in) :: x
    type(_NAME) :: r

    _ELEM_TYPE :: factor1, factor2
#  if _DERIV_ID == _GRADGRAD
    integer :: i, lo, up
#  endif

    r%val = asinh(x%val)
    factor2 = 1 / (1 + x%val**2)
    factor1 = sqrt(factor2)
    r%grad = factor1 * x%grad
#  if _DERIV_ID > _GRAD
    factor2 = -factor2 * x%val
#  endif
#  if _DERIV_ID == _GRADGRAD
    allocate(r%gradgrad(size(x%gradgrad)))
    up = 0
    do i = 1, size(r%grad)
        lo = up + i
        up = up + 1
        r%gradgrad(lo:up) = ( &
            factor1 * x%gradgrad(lo:up) + factor2 * r%grad(i) * x%grad(:i) &
        )
    end do
#  elif _DERIV_ID == _DIVGRAD
    r%divgrad = factor1 * x%divgrad + factor2 * dot_product(r%grad, x%grad)
#  endif
end function _PROC
#  undef _PROC


#  define _PROC _TYPE_UNARY_OP(acosh)
elemental function _PROC(x) result(r)
    class(_NAME), intent(in) :: x
    type(_NAME) :: r

    _ELEM_TYPE :: factor1, factor2
#  if _DERIV_ID == _GRADGRAD
    integer :: i, lo, up
#  endif

    r%val = acosh(x%val)
    factor2 = -1 / (1 - x%val**2)
    factor1 = sqrt(factor2)
    r%grad = factor1 * x%grad
#  if _DERIV_ID > _GRAD
    factor2 = -factor2 * x%val
#  endif
#  if _DERIV_ID == _GRADGRAD
    allocate(r%gradgrad(size(x%gradgrad)))
    up = 0
    do i = 1, size(r%grad)
        lo = up + i
        up = up + 1
        r%gradgrad(lo:up) = ( &
            factor1 * x%gradgrad(lo:up) + factor2 * r%grad(i) * x%grad(:i) &
        )
    end do
#  elif _DERIV_ID == _DIVGRAD
    r%divgrad = factor1 * x%divgrad + factor2 * dot_product(r%grad, x%grad)
#  endif
end function _PROC
#  undef _PROC


#  define _PROC _TYPE_UNARY_OP(atanh)
elemental function _PROC(x) result(r)
    class(_NAME), intent(in) :: x
    type(_NAME) :: r

    _ELEM_TYPE :: factor1
#  if _DERIV_ID > _GRAD
    _ELEM_TYPE :: factor2
#  endif
#  if _DERIV_ID == _GRADGRAD
    integer :: i, lo, up
#  endif

    r%val = atanh(x%val)
    factor1 = 1 / (1 - x%val**2)
    r%grad = factor1 * x%grad
#  if _DERIV_ID > _GRAD
    factor2 = 2 * x%val
#  endif
#  if _DERIV_ID == _GRADGRAD
    allocate(r%gradgrad(size(x%gradgrad)))
    up = 0
    do i = 1, size(r%grad)
        lo = up + i
        up = up + 1
        r%gradgrad(lo:up) = ( &
            factor1 * x%gradgrad(lo:up) + factor2 * r%grad(i) * r%grad(:i) &
        )
    end do
#  elif _DERIV_ID == _DIVGRAD
    r%divgrad = factor1 * x%divgrad + factor2 * dot_product(r%grad, r%grad)
#  endif
end function _PROC
#  undef _PROC
#endif
