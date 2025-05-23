! $1 = ([_DEFAULT | _DEFAULT_ONLY])
! {_DECL(?)} + (_ID, $1) -(_UNDEF_ARGS)> ("id.inc")
! {_DECL(?), "id.inc", $1} + () -(_UNDEF_ARGS)> ()
! Add the declaration line `_DECL(<kind_label>)` for all kinds of the basic data type `_ID`.  If `_DEFAULT` is defined, the line for
! the default kind is additionally added.  If `_DEFAULT_ONLY` is defined, the line is added only for the default kind.  If "id.inc"
! is included beforehand, the argument `_ID` must be omitted.

#ifndef _DECL
#  error The argument `_DECL(<kind_label>)` required
#endif
#undef _UNDEF_ARGS
#ifdef _ID
#  include "../inc/id.inc"
#  define _UNDEF_ARGS
#elif ! (defined(_CLASS) & defined(_CLASS_K) & defined(_CLASS_P) & defined(_CLASS_S))
#  error The argument `_ID` or the inclusion of "id.inc" beforehand required
#endif
#ifdef _DEFAULT_ONLY
#  define _DEFAULT
#endif
#ifdef _DEFAULT
_DECL()
#endif
#ifndef _DEFAULT_ONLY
#  if _CLASS == _CLASS_K
#    ifdef _K1
_DECL(K1)
#    endif
#    ifdef _K2
_DECL(K2)
#    endif
#    ifdef _K4
_DECL(K4)
#    endif
#    ifdef _K8
_DECL(K8)
#    endif
#    ifdef _K16
_DECL(K16)
#    endif
#  elif _CLASS == _CLASS_P
#    ifdef _HP
_DECL(HP)
#    endif
#    ifdef _SP
_DECL(SP)
#    endif
#    ifdef _DP
_DECL(DP)
#    endif
#    ifdef _XDP
_DECL(XDP)
#    endif
#    ifdef _QP
_DECL(QP)
#    endif
#  elif _CLASS == _CLASS_S
#    ifdef _ASCII
_DECL(A)
#    endif
#    ifdef _UCS4
_DECL(U)
#    endif
#  endif
#endif
#ifdef _UNDEF_ARGS
#  undef _DEFAULT_ONLY
#  undef _DEFAULT
#endif
