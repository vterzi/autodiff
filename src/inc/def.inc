! $1 = ([_DEFAULT | _DEFAULT_ONLY])
! {_FILE} + (_ID, $1) -(_UNDEF_ARGS)> ("id.inc")
! {_FILE, "id.inc", $1} + () -(_UNDEF_ARGS, _ID)> ()
! Include the contents of the file `_FILE` for all kinds of the basic data type `_ID`.  If `_DEFAULT` is defined, the file for the
! default kind is additionally included.  If `_DEFAULT_ONLY` is defined, the file is included only for the default kind.  If
! "id.inc" is included beforehand, the argument `_ID` must be omitted.

#ifndef _FILE
#  error The argument `_FILE` required
#endif
#undef _UNDEF_ARGS
#ifdef _ID
#  include "../inc/id.inc"
#  define _UNDEF_ARGS
#elif ! (defined(_TYPE) & defined(_CLASS) & defined(_CLASS_K) & defined(_CLASS_P) & defined(_CLASS_S))
#  error The argument `_ID` or the inclusion of "id.inc" beforehand required
#endif
#ifdef _DEFAULT_ONLY
#  define _DEFAULT
#endif
#ifdef _DEFAULT
#  undef _ID
#  define _ID _TYPE
#  include "../inc/id.inc"
#  include _FILE
#endif
#ifndef _DEFAULT_ONLY
#  if _CLASS == _CLASS_K
#    ifdef _K1
#      undef _ID
#      define _ID (_TYPE+_K1)
#      include "../inc/id.inc"
#      include _FILE
#    endif
#    ifdef _K2
#      undef _ID
#      define _ID (_TYPE+_K2)
#      include "../inc/id.inc"
#      include _FILE
#    endif
#    ifdef _K4
#      undef _ID
#      define _ID (_TYPE+_K4)
#      include "../inc/id.inc"
#      include _FILE
#    endif
#    ifdef _K8
#      undef _ID
#      define _ID (_TYPE+_K8)
#      include "../inc/id.inc"
#      include _FILE
#    endif
#    ifdef _K16
#      undef _ID
#      define _ID (_TYPE+_K16)
#      include "../inc/id.inc"
#      include _FILE
#    endif
#  elif _CLASS == _CLASS_P
#    ifdef _HP
#      undef _ID
#      define _ID (_TYPE+_HP)
#      include "../inc/id.inc"
#      include _FILE
#    endif
#    ifdef _SP
#      undef _ID
#      define _ID (_TYPE+_SP)
#      include "../inc/id.inc"
#      include _FILE
#    endif
#    ifdef _DP
#      undef _ID
#      define _ID (_TYPE+_DP)
#      include "../inc/id.inc"
#      include _FILE
#    endif
#    ifdef _XDP
#      undef _ID
#      define _ID (_TYPE+_XDP)
#      include "../inc/id.inc"
#      include _FILE
#    endif
#    ifdef _QP
#      undef _ID
#      define _ID (_TYPE+_QP)
#      include "../inc/id.inc"
#      include _FILE
#    endif
#  elif _CLASS == _CLASS_S
#    ifdef _ASCII
#      undef _ID
#      define _ID (_TYPE+_ASCII)
#      include "../inc/id.inc"
#      include _FILE
#    endif
#    ifdef _UCS4
#      undef _ID
#      define _ID (_TYPE+_UCS4)
#      include "../inc/id.inc"
#      include _FILE
#    endif
#  endif
#endif
#ifdef _UNDEF_ARGS
#  undef _DEFAULT_ONLY
#  undef _DEFAULT
#endif
