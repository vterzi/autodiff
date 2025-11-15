#define _PROC _CAT(to_character_,_LABEL)
pure function _PROC(arg) result(string)
    _ARG_TYPE, intent(in) :: arg
    character(len=:), allocatable :: string

#if _DIM_ID > _DIM0
    integer :: i
    _ELEM_TYPE :: arr(size(arg))
#endif
    character(len=94) :: buffer

#if _DIM_ID > _DIM0
    arr = reshape(arg, shape(arr))
    string = '['
    do i = 1, size(arr)
        if (i > 1) string = string // ','
        write(buffer, *) arr(i)
        string = string // trim(adjustl(buffer))
    end do
    string = string // ']'
#else
    write(buffer, *) arg
    string = trim(adjustl(buffer))
#endif
end function _PROC
#undef _PROC


#define _PROC _CAT(_LABEL,_cat_S)
pure function _PROC(arg1, arg2) result(string)
    _ARG_TYPE, intent(in) :: arg1
    character(len=*), intent(in) :: arg2
    character(len=:), allocatable :: string

    string = to_character(arg1) // arg2
end function _PROC
#undef _PROC


#define _PROC _CAT(S_cat_,_LABEL)
pure function _PROC(arg1, arg2) result(string)
    character(len=*), intent(in) :: arg1
    _ARG_TYPE, intent(in) :: arg2
    character(len=:), allocatable :: string

    string = arg1 // to_character(arg2)
end function _PROC
#undef _PROC
