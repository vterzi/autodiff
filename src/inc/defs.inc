! $1<?> = ([_DEFAULT? | _DEFAULT_ONLY?])
! {_FILE} + (_ID, $1<>) -> ("id.inc", "def.inc")
! {_FILE} + (_ID1, _ID2, $1<1>, $1<2>, $1<>) -(_CLASS, _TYPE, _KEEP_ARGS)> ("id.inc", "def.inc")
! Include the contents of the file `_FILE` for all kinds of one basic data type `_ID` or for all kinds of two basic data types
! `_ID1` and `_ID2`.  If `_DEFAULT?` is defined, the file for the default kind of the corresponding type is additionally included.
! If `_DEFAULT_ONLY?` is defined, the file is included only for the default kind of the corresponding type.

#include "../inc/id.inc"

#if _N_IDS == 2
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
#  define _KEEP_ARGS
#  undef _CLASS
#  define _CLASS _CLASS2
#  undef _TYPE
#  define _TYPE _TYPE2
#  define _ID2 _ID
#  ifdef _DEFAULT_ONLY2
#    define _DEFAULT_ONLY
#  endif
#  ifdef _DEFAULT2
#    define _DEFAULT
#  endif
#  ifdef _DEFAULT1
#    undef _ID1
#    define _ID1 _TYPE1
#    include "../inc/def.inc"
#  endif
#  ifndef _DEFAULT_ONLY1
#    if _CLASS1 == _CLASS_K
#      ifdef _K1
#        undef _ID1
#        define _ID1 (_TYPE1+_K1)
#        include "../inc/def.inc"
#      endif
#      ifdef _K2
#        undef _ID1
#        define _ID1 (_TYPE1+_K2)
#        include "../inc/def.inc"
#      endif
#      ifdef _K4
#        undef _ID1
#        define _ID1 (_TYPE1+_K4)
#        include "../inc/def.inc"
#      endif
#      ifdef _K8
#        undef _ID1
#        define _ID1 (_TYPE1+_K8)
#        include "../inc/def.inc"
#      endif
#      ifdef _K16
#        undef _ID1
#        define _ID1 (_TYPE1+_K16)
#        include "../inc/def.inc"
#      endif
#    elif _CLASS1 == _CLASS_P
#      ifdef _HP
#        undef _ID1
#        define _ID1 (_TYPE1+_HP)
#        include "../inc/def.inc"
#      endif
#      ifdef _SP
#        undef _ID1
#        define _ID1 (_TYPE1+_SP)
#        include "../inc/def.inc"
#      endif
#      ifdef _DP
#        undef _ID1
#        define _ID1 (_TYPE1+_DP)
#        include "../inc/def.inc"
#      endif
#      ifdef _XDP
#        undef _ID1
#        define _ID1 (_TYPE1+_XDP)
#        include "../inc/def.inc"
#      endif
#      ifdef _QP
#        undef _ID1
#        define _ID1 (_TYPE1+_QP)
#        include "../inc/def.inc"
#      endif
#    elif _CLASS1 == _CLASS_S
#      ifdef _ASCII
#        undef _ID1
#        define _ID1 (_TYPE1+_ASCII)
#        include "../inc/def.inc"
#      endif
#      ifdef _UCS4
#        undef _ID1
#        define _ID1 (_TYPE1+_UCS4)
#        include "../inc/def.inc"
#      endif
#    endif
#  endif
#  undef _KEEP_ARGS
#  undef _ID
#  undef _ID1
#  undef _ID2
#elif _N_IDS == 1
#  include "../inc/def.inc"
#endif
#undef _DEFAULT_ONLY
#undef _DEFAULT_ONLY1
#undef _DEFAULT_ONLY2
#undef _DEFAULT
#undef _DEFAULT1
#undef _DEFAULT2
