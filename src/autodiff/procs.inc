#define _PROC _BINARY(assign)
elemental subroutine _PROC(this, that)
    class(_NAME), intent(inout) :: this
    class(_NAME), intent(in) :: that

    this%val = that%val
    this%grad = that%grad
#if defined(_GRADGRAD)
    this%gradgrad = that%gradgrad
#elif defined(_DIVGRAD)
    this%divgrad = that%divgrad
#endif
end subroutine _PROC
#undef _PROC


#define _PROC _BINARY(eq)
elemental function _PROC(this, that) result(res)
    class(_NAME), intent(in) :: this, that
    logical :: res

    res = this%val == that%val .and. all(this%grad == that%grad)
#if defined(_GRADGRAD)
    res = res .and. all(this%gradgrad == that%gradgrad)
#elif defined(_DIVGRAD)
    res = res .and. this%divgrad == that%divgrad
#endif
end function _PROC
#undef _PROC


#define _PROC _BINARY(ne)
elemental function _PROC(this, that) result(res)
    class(_NAME), intent(in) :: this, that
    logical :: res

    res = this%val /= that%val .or. any(this%grad /= that%grad)
#if defined(_GRADGRAD)
    res = res .or. any(this%gradgrad /= that%gradgrad)
#elif defined(_DIVGRAD)
    res = res .or. this%divgrad /= that%divgrad
#endif
end function _PROC
#undef _PROC


#define _PROC _UNARY(pos)
elemental function _PROC(this) result(res)
    class(_NAME), intent(in) :: this
    type(_NAME) :: res

    res%val = this%val
    res%grad = this%grad
#if defined(_GRADGRAD)
    res%gradgrad = this%gradgrad
#elif defined(_DIVGRAD)
    res%divgrad = this%divgrad
#endif
end function _PROC
#undef _PROC


#define _PROC _UNARY(neg)
elemental function _PROC(this) result(res)
    class(_NAME), intent(in) :: this
    type(_NAME) :: res

    res%val = -this%val
    res%grad = -this%grad
#if defined(_GRADGRAD)
    res%gradgrad = -this%gradgrad
#elif defined(_DIVGRAD)
    res%divgrad = -this%divgrad
#endif
end function _PROC
#undef _PROC


#define _PROC _BINARY(add)
elemental function _PROC(this, that) result(res)
    class(_NAME), intent(in) :: this, that
    type(_NAME) :: res

    res%val = this%val + that%val
    res%grad = this%grad + that%grad
#if defined(_GRADGRAD)
    res%gradgrad = this%gradgrad + that%gradgrad
#elif defined(_DIVGRAD)
    res%divgrad = this%divgrad + that%divgrad
#endif
end function _PROC
#undef _PROC


#define _PROC _BINARY(sub)
elemental function _PROC(this, that) result(res)
    class(_NAME), intent(in) :: this, that
    type(_NAME) :: res

    res%val = this%val - that%val
    res%grad = this%grad - that%grad
#if defined(_GRADGRAD)
    res%gradgrad = this%gradgrad - that%gradgrad
#elif defined(_DIVGRAD)
    res%divgrad = this%divgrad - that%divgrad
#endif
end function _PROC
#undef _PROC


#define _PROC _BINARY(mul)
elemental function _PROC(this, that) result(res)
    class(_NAME), intent(in) :: this, that
    type(_NAME) :: res

#if defined(_GRADGRAD)
    integer :: i, lo, up
#endif

    res%val = this%val * that%val
    res%grad = this%grad * that%val + this%val * that%grad
#if defined(_GRADGRAD)
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
#elif defined(_DIVGRAD)
    res%divgrad = ( &
        this%divgrad * that%val &
        + 2 * dot_product(this%grad, that%grad) &
        + this%val * that%divgrad &
    )
#endif
end function _PROC
#undef _PROC


#if _CLASS_ID == _CLASS_P
#  define _PROC _BINARY(div)
elemental function _PROC(this, that) result(res)
    class(_NAME), intent(in) :: this, that
    type(_NAME) :: res

#  if defined(_GRADGRAD)
    integer :: i, lo, up
    _ELEM_TYPE :: two_val
#  endif
    _ELEM_TYPE :: inv_val

    inv_val = 1 / that%val
    res%val = this%val * inv_val
    res%grad = (this%grad - res%val * that%grad) * inv_val
#  if defined(_GRADGRAD)
    allocate(res%gradgrad(min(size(this%gradgrad), size(that%gradgrad))))
    two_val = 2 * res%val
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
#  elif defined(_DIVGRAD)
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


#  define _PROC _BINARY(pow)
elemental function _PROC(this, that) result(res)
    class(_NAME), intent(in) :: this, that
    type(_NAME) :: res

#  if defined(_GRADGRAD)
    integer :: i, lo, up
#  endif
    _ELEM_TYPE :: inv_val, val_ratio, log_val
#  if defined(_GRADGRAD) || defined(_DIVGRAD)
    _ELEM_TYPE :: temp1, temp2, temp3
#  endif

    res%val = this%val ** that%val
    inv_val = 1 / this%val
    val_ratio = that%val * inv_val
    log_val = log(this%val)
#  if defined(_GRADGRAD) || defined(_DIVGRAD)
    temp1 = val_ratio * (val_ratio - inv_val)
    temp2 = val_ratio * log_val + inv_val
    temp3 = log_val ** 2
#  endif
    val_ratio = val_ratio * res%val
    log_val = log_val * res%val
    res%grad = this%grad * val_ratio + log_val * that%grad
#  if defined(_GRADGRAD)
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
#  elif defined(_DIVGRAD)
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


#  define _PROC _UNARY(sqrt)
elemental function _PROC(this) result(res)
    class(_NAME), intent(in) :: this
    type(_NAME) :: res

#  if defined(_GRADGRAD)
    integer :: i, lo, up
#  endif
    _ELEM_TYPE :: temp1
#  if defined(_GRADGRAD) || defined(_DIVGRAD)
    _ELEM_TYPE :: temp2
#  endif

    res%val = sqrt(this%val)
    temp1 = 1 / (2 * res%val)
    res%grad = temp1 * this%grad
#  if defined(_GRADGRAD) || defined(_DIVGRAD)
    temp2 = -temp1 / (2 * this%val)
#  endif
#  if defined(_GRADGRAD)
    allocate(res%gradgrad(size(this%gradgrad)))
    up = 0
    do i = 1, size(res%grad)
        lo = up + i
        up = up + 1
        res%gradgrad(lo:up) = ( &
            temp1 * this%gradgrad(lo:up) &
            + temp2 * this%grad(i) * this%grad(:i) &
        )
    end do
#  elif defined(_DIVGRAD)
    res%divgrad = ( &
        temp1 * this%divgrad &
        + temp2 * dot_product(this%grad, this%grad) &
    )
#  endif
end function _PROC
#  undef _PROC
#endif
