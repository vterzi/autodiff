#if _TYPE_ID & _LOGICAL
#  define _PROC _UNARY(assert_true)
pure subroutine _PROC(arg, file, line)
    _ARG_TYPE, intent(in) :: arg
    character(len=*), intent(in), optional :: file
    integer, intent(in), optional :: line

#  if _DIM_ID > _DIM0
    integer :: i
    integer, dimension(size(shape(arg))) :: dims, idxs
    _ELEM_TYPE :: arr(size(arg)), elem
#  endif
    character(len=:), allocatable :: msg

#  if _DIM_ID > _DIM0
    arr = reshape(arg, shape(arr))
    do i = 1, size(arr)
        elem = arr(i)
        if (.not. elem) then
            dims = shape(arg)
            idxs = unravel_idx(i, dims)
            msg = ( &
                msg_src(file, line) &
                // idxs // ': ' // elem // '/=' // .true. &
            )
            error stop msg
        end if
    end do
#  else
    if (.not. arg) then
        msg = msg_src(file, line) // arg // '/=' // .true.
        error stop msg
    end if
#  endif
end subroutine _PROC
#  undef _PROC


#  define _PROC _UNARY(assert_false)
pure subroutine _PROC(arg, file, line)
    _ARG_TYPE, intent(in) :: arg
    character(len=*), intent(in), optional :: file
    integer, intent(in), optional :: line

#  if _DIM_ID > _DIM0
    integer :: i
    integer, dimension(size(shape(arg))) :: dims, idxs
    _ELEM_TYPE :: arr(size(arg)), elem
#  endif
    character(len=:), allocatable :: msg

#  if _DIM_ID > _DIM0
    arr = reshape(arg, shape(arr))
    do i = 1, size(arr)
        elem = arr(i)
        if (elem) then
            dims = shape(arg)
            idxs = unravel_idx(i, dims)
            msg = ( &
                msg_src(file, line) &
                // idxs // ': ' // elem // '/=' // .false. &
            )
            error stop msg
        end if
    end do
#  else
    if (arg) then
        msg = msg_src(file, line) // arg // '/=' // .false.
        error stop msg
    end if
#  endif
end subroutine _PROC
#  undef _PROC
#endif


#if _TYPE_ID & (_INTEGER | _REAL | _COMPLEX)
#  define _PROC _UNARY(assert_equal)
pure subroutine _PROC(arg1, arg2, file, line)
    _ARG_TYPE, intent(in) :: arg1, arg2
    character(len=*), intent(in), optional :: file
    integer, intent(in), optional :: line

#  if _DIM_ID > _DIM0
    integer :: i
    integer, dimension(min(size(shape(arg1)), size(shape(arg2)))) :: dims, idxs
    _ELEM_TYPE :: arr1(size(arg1)), arr2(size(arg2)), elem1, elem2
#  endif
    character(len=:), allocatable :: msg

#  if _DIM_ID > _DIM0
    if (any(shape(arg1) /= shape(arg2))) then
        msg = msg_src(file, line) // shape(arg1) // '/=' // shape(arg2)
        error stop msg
    end if
    arr1 = reshape(arg1, shape(arr1))
    arr2 = reshape(arg2, shape(arr2))
    do i = 1, min(size(arr1), size(arr2))
        elem1 = arr1(i)
        elem2 = arr2(i)
        if (elem1 /= elem2) then
            dims = min(shape(arg1), shape(arg2))
            idxs = unravel_idx(i, dims)
            msg = msg_src(file, line) // idxs // ': ' // elem1 // '/=' // elem2
            error stop msg
        end if
    end do
#  else
    if (arg1 /= arg2) then
        msg = msg_src(file, line) // arg1 // '/=' // arg2
        error stop msg
    end if
#  endif
end subroutine _PROC
#  undef _PROC
#endif


#if _TYPE_ID & (_REAL | _COMPLEX)
#  define _PROC _UNARY(assert_close)
pure subroutine _PROC(arg1, arg2, rel_tol, abs_tol, file, line)
    _ARG_TYPE, intent(in) :: arg1, arg2
    real(_KIND), intent(in), optional :: rel_tol, abs_tol
    character(len=*), intent(in), optional :: file
    integer, intent(in), optional :: line

#  if _DIM_ID > _DIM0
    integer :: i
    integer, dimension(min(size(shape(arg1)), size(shape(arg2)))) :: dims, idxs
    _ELEM_TYPE :: arr1(size(arg1)), arr2(size(arg2)), elem1, elem2
#  endif
    real(_KIND) :: rel_tol_, abs_tol_, tol
    character(len=:), allocatable :: msg

    rel_tol_ = 0
    if (present(rel_tol)) rel_tol_ = abs(rel_tol)
    abs_tol_ = 0
    if (present(abs_tol)) abs_tol_ = abs(abs_tol)

#  if _DIM_ID > _DIM0
    if (any(shape(arg1) /= shape(arg2))) then
        msg = msg_src(file, line) // shape(arg1) // '/=' // shape(arg2)
        error stop msg
    end if
    arr1 = reshape(arg1, shape(arr1))
    arr2 = reshape(arg2, shape(arr2))
    do i = 1, min(size(arr1), size(arr2))
        elem1 = arr1(i)
        elem2 = arr2(i)
        tol = max(rel_tol_ * max(abs(elem1), abs(elem2)), abs_tol_)
        if (abs(elem1 - elem2) > tol) then
            dims = min(shape(arg1), shape(arg2))
            idxs = unravel_idx(i, dims)
            msg = ( &
                msg_src(file, line) &
                // idxs // ': |(' // elem1 // ')-(' // elem2 // ')|>' // tol &
            )
            error stop msg
        end if
    end do
#  else
    tol = max(rel_tol_ * max(abs(arg1), abs(arg2)), abs_tol_)
    if (abs(arg1 - arg2) > tol) then
        msg = ( &
            msg_src(file, line) &
            // '|(' // arg1 // ')-(' // arg2 // ')|>' // tol &
        )
        error stop msg
    end if
#  endif
end subroutine _PROC
#  undef _PROC
#endif
