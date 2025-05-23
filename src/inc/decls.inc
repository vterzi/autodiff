! $1<?> = ([_DEFAULT? | _DEFAULT_ONLY?])
! {_DECL_ONE} + (_ID, $1<>) -(_DECL)> ("id.inc", "decl.inc")
! {_DECL_TWO} + (_ID1, _ID2, $1<1>, $1<2>, $1<>) -(_DECL, _CLASS, $1<>, _KIND_LABEL)> ("id.inc", "decl.inc")
! Add the declaration line `_DECL_ONE(<kind_label>)` for all kinds of one basic data type `_ID` or add the declaration line
! `_DECL_TWO(<kind_label_1>,<kind_label_2>)` for all kinds of two basic data types `_ID1` and `_ID2`.  If `_DEFAULT?` is defined,
! the line for the default kind of the corresponding type is additionally added.  If `_DEFAULT_ONLY?` is defined, the line is added
! only for the default kind of the corresponding type.

#include "../inc/id.inc"

#if _N_IDS == 2
#  ifndef _DECL_TWO
#    error The argument `_DECL_TWO(<kind_label_1>,<kind_label_2>)` for two arguments `_ID1` and `_ID2` required
#  endif
#  ifdef _DEFAULT_ONLY
#    undef _DEFAULT_ONLY
#    define _DEFAULT_ONLY1
#    define _DEFAULT_ONLY2
#  endif
#  ifdef _DEFAULT
#    undef _DEFAULT
#    define _DEFAULT1
#    define _DEFAULT2
#  endif
#  ifdef _DEFAULT_ONLY1
#    define _DEFAULT1
#  endif
#  undef _CLASS
#  define _CLASS _CLASS2
#  ifdef _DEFAULT_ONLY2
#    define _DEFAULT_ONLY
#  endif
#  ifdef _DEFAULT2
#    define _DEFAULT
#  endif
#  define _DECL(X) _DECL_TWO(_KIND_LABEL,X)
#  ifdef _DEFAULT1
#    undef _KIND_LABEL
#    define _KIND_LABEL
#    include "../inc/decl.inc"
#  endif
#  ifndef _DEFAULT_ONLY1
#    if _CLASS1 == _CLASS_K
#      ifdef _K1
#        undef _KIND_LABEL
#        define _KIND_LABEL K1
#        include "../inc/decl.inc"
#      endif
#      ifdef _K2
#        undef _KIND_LABEL
#        define _KIND_LABEL K2
#        include "../inc/decl.inc"
#      endif
#      ifdef _K4
#        undef _KIND_LABEL
#        define _KIND_LABEL K4
#        include "../inc/decl.inc"
#      endif
#      ifdef _K8
#        undef _KIND_LABEL
#        define _KIND_LABEL K8
#        include "../inc/decl.inc"
#      endif
#      ifdef _K16
#        undef _KIND_LABEL
#        define _KIND_LABEL K16
#        include "../inc/decl.inc"
#      endif
#    elif _CLASS1 == _CLASS_P
#      ifdef _HP
#        undef _KIND_LABEL
#        define _KIND_LABEL HP
#        include "../inc/decl.inc"
#      endif
#      ifdef _SP
#        undef _KIND_LABEL
#        define _KIND_LABEL SP
#        include "../inc/decl.inc"
#      endif
#      ifdef _DP
#        undef _KIND_LABEL
#        define _KIND_LABEL DP
#        include "../inc/decl.inc"
#      endif
#      ifdef _XDP
#        undef _KIND_LABEL
#        define _KIND_LABEL XDP
#        include "../inc/decl.inc"
#      endif
#      ifdef _QP
#        undef _KIND_LABEL
#        define _KIND_LABEL QP
#        include "../inc/decl.inc"
#      endif
#    elif _CLASS1 == _CLASS_S
#      ifdef _ASCII
#        undef _KIND_LABEL
#        define _KIND_LABEL A
#        include "../inc/decl.inc"
#      endif
#      ifdef _UCS4
#        undef _KIND_LABEL
#        define _KIND_LABEL U
#        include "../inc/decl.inc"
#      endif
#    endif
#  endif
#  undef _DEFAULT_ONLY1
#  undef _DEFAULT_ONLY2
#  undef _DEFAULT1
#  undef _DEFAULT2
#elif _N_IDS == 1
#  ifndef _DECL_ONE
#    error The argument `_DECL_ONE(<kind_label>)` for one argument `_ID` required
#  endif
#  define _DECL(X) _DECL_ONE(X)
#  include "../inc/decl.inc"
#endif
#undef _DECL
#undef _DEFAULT_ONLY
#undef _DEFAULT
