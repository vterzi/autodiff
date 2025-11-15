#define _(X) X
#define _CAT(A,B) _(A)B
#define _CAT3(A,B,C) _(A)_(B)C

#define _LOGICAL (1 << (_KIND_BITS))
#define _INTEGER (1 << (_KIND_BITS + 1))
#define _REAL (1 << (_KIND_BITS + 2))
#define _COMPLEX (1 << (_KIND_BITS + 3))

#define _DIM0 (1 << 0)
#define _DIM1 (1 << 1)
#define _DIM2 (1 << 2)
#define _DIM3 (1 << 3)
#define _DIM4 (1 << 4)
#define _DIM5 (1 << 5)
#define _DIM6 (1 << 6)
#define _DIM7 (1 << 7)

#define _ELEM_TYPE _TYPE(_KIND)
#define _LABEL _CAT3(_TYPE_LABEL,_DIM_LABEL,_KIND_LABEL)
#define _UNARY(X) _CAT3(X,_,_LABEL)

module unittest
    implicit none

#define _FILE "decl.inc"
#define _DIM_IDS (_DIM0 | _DIM1 | _DIM2 | _DIM3 | _DIM4 | _DIM5 | _DIM6 | _DIM7)

#define _TYPE_IDS (_LOGICAL | _INTEGER | _REAL | _COMPLEX)
#define _PROC _CAT3(_OP,_,_LABEL)
#define _OP to_character
#include "iface.inc"
#undef _PROC
    public :: operator(//)
#define _PROC _CAT(_LABEL,_cat_S)
#define _NO_PUBLIC
#define _OP operator(//)
#include "iface.inc"
#undef _PROC
#define _PROC _CAT(S_cat_,_LABEL)
#define _NO_PUBLIC
#define _OP operator(//)
#include "iface.inc"
#undef _PROC
#undef _TYPE_IDS

#define _PROC _UNARY(_OP)
#define _TYPE_IDS (_LOGICAL)
#define _OP assert_true
#include "iface.inc"
#define _OP assert_false
#include "iface.inc"
#undef _TYPE_IDS
#define _TYPE_IDS (_INTEGER | _REAL | _COMPLEX)
#define _OP assert_equal
#include "iface.inc"
#undef _TYPE_IDS
#define _TYPE_IDS (_REAL | _COMPLEX)
#define _OP assert_close
#include "iface.inc"
#undef _TYPE_IDS
#undef _PROC

#undef _DIM_IDS
#undef _FILE

contains
    pure function msg_src(file, line) result(msg)
        character(len=*), intent(in), optional :: file
        integer, intent(in), optional :: line
        character(len=:), allocatable :: msg

        msg = ''
        if (present(file)) msg = msg // file // ':'
        if (present(line)) msg = msg // line // ':'
        if (len(msg) > 0) msg = msg // ' '
    end function msg_src


    pure function unravel_idx(idx, dims) result(idxs)
        integer, intent(in) :: idx, dims(:)
        integer :: idxs(size(dims))

        integer :: i, j

        i = idx - 1
        do j = 1, size(dims)
            idxs(j) = mod(i, dims(j)) + 1
            i = i / dims(j)
        end do
    end function unravel_idx


#define _DIM_IDS (_DIM0 | _DIM1 | _DIM2 | _DIM3 | _DIM4 | _DIM5 | _DIM6 | _DIM7)
#define _TYPE_IDS (_LOGICAL | _INTEGER | _REAL | _COMPLEX)
#define _FILE "to_character.inc"
#include "dims.inc"
#undef _FILE
#define _FILE "assert.inc"
#include "dims.inc"
#undef _FILE
#undef _TYPE_IDS
#undef _DIM_IDS

end module unittest
