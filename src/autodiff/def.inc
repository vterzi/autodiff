#if defined(_GRADGRAD)
#  define _PREFIX Gradgrad
#elif defined(_DIVGRAD)
#  define _PREFIX Divgrad
#else
#  define _PREFIX Grad
#endif

#define _NAME _CAT3(_PREFIX,_TYPE_LABEL,_KIND_LABEL)
#define _UNARY(X) _CAT3(X,_,_NAME)
#define _BINARY(X) _CAT5(_NAME,_,X,_,_NAME)


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


#if _CLASS == _CLASS_P
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
    res%grad = res%val * (this%grad * val_ratio + log_val * that%grad)
#  if defined(_GRADGRAD) || defined(_DIVGRAD)
    temp1 = val_ratio * (val_ratio - inv_val)
    temp2 = val_ratio * log_val + inv_val
    temp3 = log_val ** 2
#  endif
#  if defined(_GRADGRAD)
    up = 0
    do i = 1, size(res%grad)
        lo = up + i
        up = up + 1
        res%gradgrad(lo:up) = res%val * ( &
            this%gradgrad(lo:up) * val_ratio &
            + this%grad(:i) * (this%grad(i) * temp1 + temp2 * that%grad(i)) &
            + (this%grad(i) * temp2 + temp3 * that%grad(i)) * that%grad(:i) &
            + log_val * that%gradgrad(lo:up) &
        )
    end do
#  elif defined(_DIVGRAD)
    res%divgrad = res%val * ( &
        this%divgrad * val_ratio &
        + temp1 * dot_product(this%grad, this%grad) &
        + 2 * temp2 * dot_product(this%grad, that%grad) &
        + temp3 * dot_product(that%grad, that%grad) &
        + log_val * that%divgrad &
    )
#  endif
end function _PROC
#  undef _PROC
#endif


#undef _PREFIX
#undef _NAME
#undef _UNARY
#undef _BINARY

#undef _GRADGRAD
#undef _DIVGRAD
