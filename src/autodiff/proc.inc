#define _PROC _TYPE_UNARY_OP(new)
pure function _PROC(val, grad &
#if _DERIV_ID == _GRADGRAD
    , gradgrad, upper &
#elif _DERIV_ID == _DIVGRAD
    , divgrad &
#endif
) result(this)
    _ELEM_TYPE, intent(in) :: val, grad(:)
#if _DERIV_ID == _GRADGRAD
    _ELEM_TYPE, intent(in) :: gradgrad(:, :)
    logical, intent(in) :: upper
#elif _DERIV_ID == _DIVGRAD
    _ELEM_TYPE, intent(in) :: divgrad
#endif
    type(_NAME) :: this

#if _DERIV_ID == _GRADGRAD
    integer :: n, n1, n2, i, lo, up, up_
#endif

    this%val = val
    this%grad = grad
#if _DERIV_ID == _GRADGRAD
    n = size(grad)
    n1 = size(gradgrad, 1)
    n2 = size(gradgrad, 2)
    allocate(this%gradgrad(n * (n + 1) / 2))
    if (upper) then
        do i = 1, n
            lo = up + i
            up = up + 1
            if (i <= n2) then
                if (i <= n1) then
                    this%gradgrad(lo:up) = gradgrad(:i, i)
                else
                    up_ = up + n1 - i
                    this%gradgrad(lo:up_) = gradgrad(:n1, i)
                    up_ = up_ + 1
                    this%gradgrad(up_:up) = 0
                end if
            else
                this%gradgrad(lo:up) = 0
            end if
        end do
    else
        do i = 1, n
            lo = up + i
            up = up + 1
            if (i <= n1) then
                if (i <= n2) then
                    this%gradgrad(lo:up) = gradgrad(i, :i)
                else
                    up_ = up + n2 - i
                    this%gradgrad(lo:up_) = gradgrad(i, :n2)
                    up_ = up_ + 1
                    this%gradgrad(up_:up) = 0
                end if
            else
                this%gradgrad(lo:up) = 0
            end if
        end do
    end if
#elif _DERIV_ID == _DIVGRAD
    this%divgrad = divgrad
#endif
end function _PROC
#undef _PROC


#define _PROC _TYPE_UNARY_OP(get_val)
pure function _PROC(this) result(val)
    class(_NAME), intent(in) :: this
    _ELEM_TYPE :: val

    val = this%val
end function _PROC
#undef _PROC


#define _PROC _TYPE_UNARY_OP(get_grad)
pure function _PROC(this) result(grad)
    class(_NAME), intent(in) :: this
    _ELEM_TYPE :: grad(size(this%grad))

    grad = this%grad
end function _PROC
#undef _PROC


#if _DERIV_ID == _GRADGRAD
#  define _PROC _TYPE_UNARY_OP(get_gradgrad)
pure function _PROC(this) result(gradgrad)
    class(_NAME), intent(in) :: this
    _ELEM_TYPE :: gradgrad(size(this%grad), size(this%grad))

    integer :: n, i1, i2, lo, up

    n = size(this%grad)
    up = 0
    do i1 = 1, n
        lo = up + i1
        up = up + 1
        gradgrad(:i1, i1) = this%gradgrad(lo:up)
    end do
    do i1 = 2, n
        do i2 = 1, i1 - 1
            gradgrad(i1, i2) = gradgrad(i2, i1)
        end do
    end do
end function _PROC
#  undef _PROC
#endif


#if (_DERIV_ID == _GRADGRAD) || (_DERIV_ID == _DIVGRAD)
#  define _PROC _TYPE_UNARY_OP(get_divgrad)
pure function _PROC(this) result(divgrad)
    class(_NAME), intent(in) :: this
    _ELEM_TYPE :: divgrad

#  if _DERIV_ID == _GRADGRAD
    integer :: i, idx
#  endif

#  if _DERIV_ID == _GRADGRAD
    divgrad = 0
    idx = 0
    do i = 1, size(this%grad)
        idx = idx + i
        divgrad = divgrad + this%gradgrad(idx)
    end do
#  elif _DERIV_ID == _DIVGRAD
    divgrad = this%divgrad
#  endif
end function _PROC
#  undef _PROC
#endif

! -----------------------------------------------------------------------------

#define _PROC _TYPE_BINARY_OP(eq)
elemental function _PROC(this, that) result(res)
    class(_NAME), intent(in) :: this, that
    logical :: res

    res = this%val == that%val .and. all(this%grad == that%grad)
#if _DERIV_ID == _GRADGRAD
    res = res .and. all(this%gradgrad == that%gradgrad)
#elif _DERIV_ID == _DIVGRAD
    res = res .and. this%divgrad == that%divgrad
#endif
end function _PROC
#undef _PROC


#define _PROC _TYPE_BINARY_OP(ne)
elemental function _PROC(this, that) result(res)
    class(_NAME), intent(in) :: this, that
    logical :: res

    res = this%val /= that%val .or. any(this%grad /= that%grad)
#if _DERIV_ID == _GRADGRAD
    res = res .or. any(this%gradgrad /= that%gradgrad)
#elif _DERIV_ID == _DIVGRAD
    res = res .or. this%divgrad /= that%divgrad
#endif
end function _PROC
#undef _PROC


#define _PROC _TYPE_UNARY_OP(pos)
elemental function _PROC(this) result(res)
    class(_NAME), intent(in) :: this
    type(_NAME) :: res

    res%val = this%val
    res%grad = this%grad
#if _DERIV_ID == _GRADGRAD
    res%gradgrad = this%gradgrad
#elif _DERIV_ID == _DIVGRAD
    res%divgrad = this%divgrad
#endif
end function _PROC
#undef _PROC


#define _PROC _TYPE_UNARY_OP(neg)
elemental function _PROC(this) result(res)
    class(_NAME), intent(in) :: this
    type(_NAME) :: res

    res%val = -this%val
    res%grad = -this%grad
#if _DERIV_ID == _GRADGRAD
    res%gradgrad = -this%gradgrad
#elif _DERIV_ID == _DIVGRAD
    res%divgrad = -this%divgrad
#endif
end function _PROC
#undef _PROC


#define _PROC _TYPE_BINARY_OP(add)
elemental function _PROC(this, that) result(res)
    class(_NAME), intent(in) :: this, that
    type(_NAME) :: res

    res%val = this%val + that%val
    res%grad = this%grad + that%grad
#if _DERIV_ID == _GRADGRAD
    res%gradgrad = this%gradgrad + that%gradgrad
#elif _DERIV_ID == _DIVGRAD
    res%divgrad = this%divgrad + that%divgrad
#endif
end function _PROC
#undef _PROC


#define _PROC _TYPE_BINARY_OP(sub)
elemental function _PROC(this, that) result(res)
    class(_NAME), intent(in) :: this, that
    type(_NAME) :: res

    res%val = this%val - that%val
    res%grad = this%grad - that%grad
#if _DERIV_ID == _GRADGRAD
    res%gradgrad = this%gradgrad - that%gradgrad
#elif _DERIV_ID == _DIVGRAD
    res%divgrad = this%divgrad - that%divgrad
#endif
end function _PROC
#undef _PROC


#define _PROC _TYPE_BINARY_OP(mul)
elemental function _PROC(this, that) result(res)
    class(_NAME), intent(in) :: this, that
    type(_NAME) :: res

#if _DERIV_ID == _GRADGRAD
    integer :: i, lo, up
#endif

    res%val = this%val * that%val
    res%grad = this%grad * that%val + this%val * that%grad
#if _DERIV_ID == _GRADGRAD
    allocate(res%gradgrad(min(size(this%gradgrad), size(that%gradgrad))))
    up = 0
    do i = 1, size(res%grad)
        lo = up + i
        up = up + 1
        res%gradgrad(lo:up) = ( &
            this%gradgrad(lo:up) * that%val &
            + this%grad(:i) * that%grad(i) &
            + this%grad(i) * that%grad(:i) &
            + this%val * that%gradgrad(lo:up) &
        )
    end do
#elif _DERIV_ID == _DIVGRAD
    res%divgrad = ( &
        this%divgrad * that%val &
        + 2 * dot_product(this%grad, that%grad) &
        + this%val * that%divgrad &
    )
#endif
end function _PROC
#undef _PROC


#if (_TYPE_ID == _REAL) || (_TYPE_ID == _COMPLEX)
#  define _PROC _TYPE_BINARY_OP(div)
elemental function _PROC(this, that) result(res)
    class(_NAME), intent(in) :: this, that
    type(_NAME) :: res

#  if _DERIV_ID == _GRADGRAD
    integer :: i, lo, up
    _ELEM_TYPE :: two_val
#  endif
    _ELEM_TYPE :: inv_val

    inv_val = 1 / that%val
    res%val = this%val * inv_val
    res%grad = (this%grad - res%val * that%grad) * inv_val
#  if _DERIV_ID == _GRADGRAD
    two_val = 2 * res%val
    allocate(res%gradgrad(min(size(this%gradgrad), size(that%gradgrad))))
    up = 0
    do i = 1, size(res%grad)
        lo = up + i
        up = up + 1
        res%gradgrad(lo:up) = inv_val * ( &
            this%gradgrad(lo:up) &
            + inv_val * ( &
                (two_val * that%grad(i) - this%grad(i)) * that%grad(:i) &
                - this%grad(:i) * that%grad(i) &
            ) &
            - res%val * that%gradgrad(lo:up) &
        )
    end do
#  elif _DERIV_ID == _DIVGRAD
    res%divgrad = inv_val * ( &
        this%divgrad &
        + 2 * inv_val * dot_product( &
            res%val * that%grad - this%grad, that%grad &
        ) &
        - res%val * that%divgrad &
    )
#  endif
end function _PROC
#  undef _PROC


#  define _PROC _TYPE_BINARY_OP(pow)
elemental function _PROC(this, that) result(res)
    class(_NAME), intent(in) :: this, that
    type(_NAME) :: res

#  if _DERIV_ID == _GRADGRAD
    integer :: i, lo, up
#  endif
    _ELEM_TYPE :: inv_val, val_ratio, log_val
#  if (_DERIV_ID == _GRADGRAD) || (_DERIV_ID == _DIVGRAD)
    _ELEM_TYPE :: temp1, temp2, temp3
#  endif

    res%val = this%val**that%val
    inv_val = 1 / this%val
    val_ratio = that%val * inv_val
    log_val = log(this%val)
#  if (_DERIV_ID == _GRADGRAD) || (_DERIV_ID == _DIVGRAD)
    temp1 = val_ratio * (val_ratio - inv_val)
    temp2 = val_ratio * log_val + inv_val
    temp3 = log_val**2
#  endif
    val_ratio = val_ratio * res%val
    log_val = log_val * res%val
    res%grad = this%grad * val_ratio + log_val * that%grad
#  if _DERIV_ID == _GRADGRAD
    temp1 = temp1 * res%val
    temp2 = temp2 * res%val
    temp3 = temp3 * res%val
    allocate(res%gradgrad(min(size(this%gradgrad), size(that%gradgrad))))
    up = 0
    do i = 1, size(res%grad)
        lo = up + i
        up = up + 1
        res%gradgrad(lo:up) = ( &
            this%gradgrad(lo:up) * val_ratio &
            + this%grad(:i) * (this%grad(i) * temp1 + temp2 * that%grad(i)) &
            + (this%grad(i) * temp2 + temp3 * that%grad(i)) * that%grad(:i) &
            + log_val * that%gradgrad(lo:up) &
        )
    end do
#  elif _DERIV_ID == _DIVGRAD
    res%divgrad = ( &
        this%divgrad * val_ratio &
        + res%val * ( &
            temp1 * dot_product(this%grad, this%grad) &
            + 2 * temp2 * dot_product(this%grad, that%grad) &
            + temp3 * dot_product(that%grad, that%grad) &
        ) &
        + log_val * that%divgrad &
    )
#  endif
end function _PROC
#  undef _PROC
#endif

! -----------------------------------------------------------------------------

#if _TYPE_ID == _COMPLEX
#  define _PROC _TYPE_UNARY_OP(real)
elemental function _PROC(this) result(res)
    class(_NAME), intent(in) :: this
    type(_CAT3(_DERIV,R,_KIND_LABEL)) :: res

    res%val = real(this%val)
    res%grad = real(this%grad)
#  if _DERIV_ID == _GRADGRAD
    res%gradgrad = real(this%gradgrad)
#  elif _DERIV_ID == _DIVGRAD
    res%divgrad = real(this%divgrad)
#  endif
end function _PROC
#  undef _PROC


#  define _PROC _TYPE_UNARY_OP(aimag)
elemental function _PROC(this) result(res)
    class(_NAME), intent(in) :: this
    type(_CAT3(_DERIV,R,_KIND_LABEL)) :: res

    res%val = aimag(this%val)
    res%grad = aimag(this%grad)
#  if _DERIV_ID == _GRADGRAD
    res%gradgrad = aimag(this%gradgrad)
#  elif _DERIV_ID == _DIVGRAD
    res%divgrad = aimag(this%divgrad)
#  endif
end function _PROC
#  undef _PROC


#  define _PROC _TYPE_UNARY_OP(conjg)
elemental function _PROC(this) result(res)
    class(_NAME), intent(in) :: this
    type(_NAME) :: res

    res%val = conjg(this%val)
    res%grad = conjg(this%grad)
#  if _DERIV_ID == _GRADGRAD
    res%gradgrad = conjg(this%gradgrad)
#  elif _DERIV_ID == _DIVGRAD
    res%divgrad = conjg(this%divgrad)
#  endif
end function _PROC
#  undef _PROC
#endif


#define _PROC _TYPE_UNARY_OP(abs)
elemental function _PROC(this) result(res)
    class(_NAME), intent(in) :: this
    type(_NAME) :: res

#if _TYPE_ID == _COMPLEX
    res = sqrt(this * conjg(this))
#else
    if (this%val > 0) then
        res = this
    else if (this%val < 0) then
        res = -this
    else
        res%val = this%val
#  if _TYPE_ID == _REAL
#    define _NAN ieee_value(res%val, IEEE_QUIET_NAN)
#  else
#    define _NAN 0 / res%val
#  endif
        res%grad = _NAN
#  if _DERIV_ID == _GRADGRAD
        res%gradgrad = _NAN
#  elif _DERIV_ID == _DIVGRAD
        res%divgrad = _NAN
#  endif
#  undef _NAN
    end if
#endif
end function _PROC
#undef _PROC


#if (_TYPE_ID == _REAL) || (_TYPE_ID == _COMPLEX)
#  define _PROC _TYPE_UNARY_OP(sqrt)
elemental function _PROC(this) result(res)
    class(_NAME), intent(in) :: this
    type(_NAME) :: res

#  if _DERIV_ID == _GRADGRAD
    integer :: i, lo, up
#  endif
    _ELEM_TYPE :: factor1
#  if (_DERIV_ID == _GRADGRAD) || (_DERIV_ID == _DIVGRAD)
    _ELEM_TYPE :: factor2
#  endif

    res%val = sqrt(this%val)
    factor1 = 1 / (2 * res%val)
    res%grad = factor1 * this%grad
#  if (_DERIV_ID == _GRADGRAD) || (_DERIV_ID == _DIVGRAD)
    factor2 = -factor1 / (2 * this%val)
#  endif
#  if _DERIV_ID == _GRADGRAD
    allocate(res%gradgrad(size(this%gradgrad)))
    up = 0
    do i = 1, size(res%grad)
        lo = up + i
        up = up + 1
        res%gradgrad(lo:up) = ( &
            factor1 * this%gradgrad(lo:up) &
            + factor2 * this%grad(i) * this%grad(:i) &
        )
    end do
#  elif _DERIV_ID == _DIVGRAD
    res%divgrad = ( &
        factor1 * this%divgrad + factor2 * dot_product(this%grad, this%grad) &
    )
#  endif
end function _PROC
#  undef _PROC


#  define _PROC _TYPE_UNARY_OP(exp)
elemental function _PROC(this) result(res)
    class(_NAME), intent(in) :: this
    type(_NAME) :: res

#  if _DERIV_ID == _GRADGRAD
    integer :: i, lo, up
#  endif

    res%val = exp(this%val)
    res%grad = res%val * this%grad
#  if _DERIV_ID == _GRADGRAD
    allocate(res%gradgrad(size(this%gradgrad)))
    up = 0
    do i = 1, size(res%grad)
        lo = up + i
        up = up + 1
        res%gradgrad(lo:up) = res%val * ( &
            this%gradgrad(lo:up) + this%grad(i) * this%grad(:i) &
        )
    end do
#  elif _DERIV_ID == _DIVGRAD
    res%divgrad = res%val * (this%divgrad + dot_product(this%grad, this%grad))
#  endif
end function _PROC
#  undef _PROC


#  define _PROC _TYPE_UNARY_OP(log)
elemental function _PROC(this) result(res)
    class(_NAME), intent(in) :: this
    type(_NAME) :: res

#  if _DERIV_ID == _GRADGRAD
    integer :: i, lo, up
#  endif
    _ELEM_TYPE :: inv_val

    res%val = log(this%val)
    inv_val = 1 / this%val
    res%grad = inv_val * this%grad
#  if _DERIV_ID == _GRADGRAD
    allocate(res%gradgrad(size(this%gradgrad)))
    up = 0
    do i = 1, size(res%grad)
        lo = up + i
        up = up + 1
        res%gradgrad(lo:up) = ( &
            inv_val * this%gradgrad(lo:up) - res%grad(i) * res%grad(:i) &
        )
    end do
#  elif _DERIV_ID == _DIVGRAD
    res%divgrad = inv_val * this%divgrad - dot_product(res%grad, res%grad)
#  endif
end function _PROC
#  undef _PROC


#  if _TYPE_ID == _REAL
#    define _PROC _TYPE_UNARY_OP(log10)
elemental function _PROC(this) result(res)
    class(_NAME), intent(in) :: this
    type(_NAME) :: res

#    if _DERIV_ID == _GRADGRAD
    integer :: i, lo, up
#    endif
    _ELEM_TYPE :: log_10, inv_val

    res%val = log10(this%val)
    log_10 = log(real(10, _KIND))
    inv_val = 1 / (this%val * log_10)
    res%grad = inv_val * this%grad
#    if _DERIV_ID == _GRADGRAD
    allocate(res%gradgrad(size(this%gradgrad)))
    up = 0
    do i = 1, size(res%grad)
        lo = up + i
        up = up + 1
        res%gradgrad(lo:up) = ( &
            inv_val * this%gradgrad(lo:up) &
            - log_10 * res%grad(i) * res%grad(:i) &
        )
    end do
#    elif _DERIV_ID == _DIVGRAD
    res%divgrad = ( &
        inv_val * this%divgrad - log_10 * dot_product(res%grad, res%grad) &
    )
#    endif
end function _PROC
#    undef _PROC
#  endif


#  define _PROC _TYPE_UNARY_OP(sin)
elemental function _PROC(this) result(res)
    class(_NAME), intent(in) :: this
    type(_NAME) :: res

#  if _DERIV_ID == _GRADGRAD
    integer :: i, lo, up
#  endif
    _ELEM_TYPE :: cos_val

    res%val = sin(this%val)
    cos_val = cos(this%val)
    res%grad = cos_val * this%grad
#  if _DERIV_ID == _GRADGRAD
    allocate(res%gradgrad(size(this%gradgrad)))
    up = 0
    do i = 1, size(res%grad)
        lo = up + i
        up = up + 1
        res%gradgrad(lo:up) = ( &
            cos_val * this%gradgrad(lo:up) &
            - res%val * this%grad(i) * this%grad(:i) &
        )
    end do
#  elif _DERIV_ID == _DIVGRAD
    res%divgrad = ( &
        cos_val * this%divgrad - res%val * dot_product(this%grad, this%grad) &
    )
#  endif
end function _PROC
#  undef _PROC


#  define _PROC _TYPE_UNARY_OP(cos)
elemental function _PROC(this) result(res)
    class(_NAME), intent(in) :: this
    type(_NAME) :: res

#  if _DERIV_ID == _GRADGRAD
    integer :: i, lo, up
#  endif
    _ELEM_TYPE :: sin_val

    res%val = cos(this%val)
    sin_val = -sin(this%val)
    res%grad = sin_val * this%grad
#  if _DERIV_ID == _GRADGRAD
    allocate(res%gradgrad(size(this%gradgrad)))
    up = 0
    do i = 1, size(res%grad)
        lo = up + i
        up = up + 1
        res%gradgrad(lo:up) = ( &
            sin_val * this%gradgrad(lo:up) &
            - res%val * this%grad(i) * this%grad(:i) &
        )
    end do
#  elif _DERIV_ID == _DIVGRAD
    res%divgrad = ( &
        sin_val * this%divgrad - res%val * dot_product(this%grad, this%grad) &
    )
#  endif
end function _PROC
#  undef _PROC


#  define _PROC _TYPE_UNARY_OP(tan)
elemental function _PROC(this) result(res)
    class(_NAME), intent(in) :: this
    type(_NAME) :: res

#  if _DERIV_ID == _GRADGRAD
    integer :: i, lo, up
    _ELEM_TYPE :: two_val
#  endif
    _ELEM_TYPE :: factor

    res%val = tan(this%val)
    factor = 1 + res%val**2
    res%grad = factor * this%grad
#  if _DERIV_ID == _GRADGRAD
    two_val = 2 * res%val
    allocate(res%gradgrad(size(this%gradgrad)))
    up = 0
    do i = 1, size(res%grad)
        lo = up + i
        up = up + 1
        res%gradgrad(lo:up) = factor * ( &
            this%gradgrad(lo:up) + two_val * this%grad(i) * this%grad(:i) &
        )
    end do
#  elif _DERIV_ID == _DIVGRAD
    res%divgrad = factor * ( &
        this%divgrad + 2 * res%val * dot_product(this%grad, this%grad) &
    )
#  endif
end function _PROC
#  undef _PROC


#  define _PROC _TYPE_UNARY_OP(asin)
elemental function _PROC(this) result(res)
    class(_NAME), intent(in) :: this
    type(_NAME) :: res

#  if _DERIV_ID == _GRADGRAD
    integer :: i, lo, up
#  endif
    _ELEM_TYPE :: factor1, factor2

    res%val = asin(this%val)
    factor2 = 1 / (1 - this%val**2)
    factor1 = sqrt(factor2)
    res%grad = factor1 * this%grad
#  if (_DERIV_ID == _GRADGRAD) || (_DERIV_ID == _DIVGRAD)
    factor2 = factor2 * this%val
#  endif
#  if _DERIV_ID == _GRADGRAD
    allocate(res%gradgrad(size(this%gradgrad)))
    up = 0
    do i = 1, size(res%grad)
        lo = up + i
        up = up + 1
        res%gradgrad(lo:up) = ( &
            factor1 * this%gradgrad(lo:up) &
            + factor2 * res%grad(i) * this%grad(:i) &
        )
    end do
#  elif _DERIV_ID == _DIVGRAD
    res%divgrad = ( &
        factor1 * this%divgrad + factor2 * dot_product(res%grad, this%grad) &
    )
#  endif
end function _PROC
#  undef _PROC


#  define _PROC _TYPE_UNARY_OP(acos)
elemental function _PROC(this) result(res)
    class(_NAME), intent(in) :: this
    type(_NAME) :: res

#  if _DERIV_ID == _GRADGRAD
    integer :: i, lo, up
#  endif
    _ELEM_TYPE :: factor1, factor2

    res%val = acos(this%val)
    factor2 = 1 / (1 - this%val**2)
    factor1 = -sqrt(factor2)
    res%grad = factor1 * this%grad
#  if (_DERIV_ID == _GRADGRAD) || (_DERIV_ID == _DIVGRAD)
    factor2 = factor2 * this%val
#  endif
#  if _DERIV_ID == _GRADGRAD
    allocate(res%gradgrad(size(this%gradgrad)))
    up = 0
    do i = 1, size(res%grad)
        lo = up + i
        up = up + 1
        res%gradgrad(lo:up) = ( &
            factor1 * this%gradgrad(lo:up) &
            + factor2 * res%grad(i) * this%grad(:i) &
        )
    end do
#  elif _DERIV_ID == _DIVGRAD
    res%divgrad = ( &
        factor1 * this%divgrad + factor2 * dot_product(res%grad, this%grad) &
    )
#  endif
end function _PROC
#  undef _PROC


#  define _PROC _TYPE_UNARY_OP(atan)
elemental function _PROC(this) result(res)
    class(_NAME), intent(in) :: this
    type(_NAME) :: res

#  if _DERIV_ID == _GRADGRAD
    integer :: i, lo, up
    _ELEM_TYPE :: factor2
#  endif
    _ELEM_TYPE :: factor1

    res%val = atan(this%val)
    factor1 = 1 / (1 + this%val**2)
    res%grad = factor1 * this%grad
#  if _DERIV_ID == _GRADGRAD
    factor2 = -2 * factor1 * this%val
    allocate(res%gradgrad(size(this%gradgrad)))
    up = 0
    do i = 1, size(res%grad)
        lo = up + i
        up = up + 1
        res%gradgrad(lo:up) = ( &
            factor1 * this%gradgrad(lo:up) &
            + factor2 * res%grad(i) * this%grad(:i) &
        )
    end do
#  elif _DERIV_ID == _DIVGRAD
    res%divgrad = factor1 * ( &
        this%divgrad - 2 * this%val * dot_product(res%grad, this%grad) &
    )
#  endif
end function _PROC
#  undef _PROC


#  define _PROC _TYPE_UNARY_OP(sinh)
elemental function _PROC(this) result(res)
    class(_NAME), intent(in) :: this
    type(_NAME) :: res

#  if _DERIV_ID == _GRADGRAD
    integer :: i, lo, up
#  endif
    _ELEM_TYPE :: cosh_val

    res%val = sinh(this%val)
    cosh_val = cosh(this%val)
    res%grad = cosh_val * this%grad
#  if _DERIV_ID == _GRADGRAD
    allocate(res%gradgrad(size(this%gradgrad)))
    up = 0
    do i = 1, size(res%grad)
        lo = up + i
        up = up + 1
        res%gradgrad(lo:up) = ( &
            cosh_val * this%gradgrad(lo:up) &
            + res%val * this%grad(i) * this%grad(:i) &
        )
    end do
#  elif _DERIV_ID == _DIVGRAD
    res%divgrad = ( &
        cosh_val * this%divgrad + res%val * dot_product(this%grad, this%grad) &
    )
#  endif
end function _PROC
#  undef _PROC


#  define _PROC _TYPE_UNARY_OP(cosh)
elemental function _PROC(this) result(res)
    class(_NAME), intent(in) :: this
    type(_NAME) :: res

#  if _DERIV_ID == _GRADGRAD
    integer :: i, lo, up
#  endif
    _ELEM_TYPE :: sinh_val

    res%val = cosh(this%val)
    sinh_val = sinh(this%val)
    res%grad = sinh_val * this%grad
#  if _DERIV_ID == _GRADGRAD
    allocate(res%gradgrad(size(this%gradgrad)))
    up = 0
    do i = 1, size(res%grad)
        lo = up + i
        up = up + 1
        res%gradgrad(lo:up) = ( &
            sinh_val * this%gradgrad(lo:up) &
            + res%val * this%grad(i) * this%grad(:i) &
        )
    end do
#  elif _DERIV_ID == _DIVGRAD
    res%divgrad = ( &
        sinh_val * this%divgrad + res%val * dot_product(this%grad, this%grad) &
    )
#  endif
end function _PROC
#  undef _PROC


#  define _PROC _TYPE_UNARY_OP(tanh)
elemental function _PROC(this) result(res)
    class(_NAME), intent(in) :: this
    type(_NAME) :: res

#  if _DERIV_ID == _GRADGRAD
    integer :: i, lo, up
    _ELEM_TYPE :: two_val
#  endif
    _ELEM_TYPE :: factor

    res%val = tanh(this%val)
    factor = 1 - res%val**2
    res%grad = factor * this%grad
#  if _DERIV_ID == _GRADGRAD
    two_val = 2 * res%val
    allocate(res%gradgrad(size(this%gradgrad)))
    up = 0
    do i = 1, size(res%grad)
        lo = up + i
        up = up + 1
        res%gradgrad(lo:up) = -factor * ( &
            this%gradgrad(lo:up) + two_val * this%grad(i) * this%grad(:i) &
        )
    end do
#  elif _DERIV_ID == _DIVGRAD
    res%divgrad = -factor * ( &
        this%divgrad + 2 * res%val * dot_product(this%grad, this%grad) &
    )
#  endif
end function _PROC
#  undef _PROC


#  define _PROC _TYPE_UNARY_OP(asinh)
elemental function _PROC(this) result(res)
    class(_NAME), intent(in) :: this
    type(_NAME) :: res

#  if _DERIV_ID == _GRADGRAD
    integer :: i, lo, up
#  endif
    _ELEM_TYPE :: factor1, factor2

    res%val = asinh(this%val)
    factor2 = 1 / (1 + this%val**2)
    factor1 = sqrt(factor2)
    res%grad = factor1 * this%grad
#  if (_DERIV_ID == _GRADGRAD) || (_DERIV_ID == _DIVGRAD)
    factor2 = -factor2 * this%val
#  endif
#  if _DERIV_ID == _GRADGRAD
    allocate(res%gradgrad(size(this%gradgrad)))
    up = 0
    do i = 1, size(res%grad)
        lo = up + i
        up = up + 1
        res%gradgrad(lo:up) = ( &
            factor1 * this%gradgrad(lo:up) &
            + factor2 * res%grad(i) * this%grad(:i) &
        )
    end do
#  elif _DERIV_ID == _DIVGRAD
    res%divgrad = ( &
        factor1 * this%divgrad + factor2 * dot_product(res%grad, this%grad) &
    )
#  endif
end function _PROC
#  undef _PROC


#  define _PROC _TYPE_UNARY_OP(acosh)
elemental function _PROC(this) result(res)
    class(_NAME), intent(in) :: this
    type(_NAME) :: res

#  if _DERIV_ID == _GRADGRAD
    integer :: i, lo, up
#  endif
    _ELEM_TYPE :: factor1, factor2

    res%val = acosh(this%val)
    factor2 = -1 / (1 - this%val**2)
    factor1 = sqrt(factor2)
    res%grad = factor1 * this%grad
#  if (_DERIV_ID == _GRADGRAD) || (_DERIV_ID == _DIVGRAD)
    factor2 = -factor2 * this%val
#  endif
#  if _DERIV_ID == _GRADGRAD
    allocate(res%gradgrad(size(this%gradgrad)))
    up = 0
    do i = 1, size(res%grad)
        lo = up + i
        up = up + 1
        res%gradgrad(lo:up) = ( &
            factor1 * this%gradgrad(lo:up) &
            + factor2 * res%grad(i) * this%grad(:i) &
        )
    end do
#  elif _DERIV_ID == _DIVGRAD
    res%divgrad = ( &
        factor1 * this%divgrad + factor2 * dot_product(res%grad, this%grad) &
    )
#  endif
end function _PROC
#  undef _PROC


#  define _PROC _TYPE_UNARY_OP(atanh)
elemental function _PROC(this) result(res)
    class(_NAME), intent(in) :: this
    type(_NAME) :: res

#  if _DERIV_ID == _GRADGRAD
    integer :: i, lo, up
    _ELEM_TYPE :: factor2
#  endif
    _ELEM_TYPE :: factor1

    res%val = atanh(this%val)
    factor1 = 1 / (1 - this%val**2)
    res%grad = factor1 * this%grad
#  if _DERIV_ID == _GRADGRAD
    factor2 = -2 * factor1 * this%val
    allocate(res%gradgrad(size(this%gradgrad)))
    up = 0
    do i = 1, size(res%grad)
        lo = up + i
        up = up + 1
        res%gradgrad(lo:up) = ( &
            factor1 * this%gradgrad(lo:up) &
            + factor2 * res%grad(i) * this%grad(:i) &
        )
    end do
#  elif _DERIV_ID == _DIVGRAD
    res%divgrad = factor1 * ( &
        this%divgrad - 2 * this%val * dot_product(res%grad, this%grad) &
    )
#  endif
end function _PROC
#  undef _PROC
#endif
