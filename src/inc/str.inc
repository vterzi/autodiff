! () -> ([_STRING], _STR0, _STR)
! Define the combination of macros `_STR0` and `_STR(<arg>)` to stringify its
! argument.  The combination starts with `_STR0` followed by `_STR(<string>)`
! at the beginning of the next line.

#undef _STR0
#undef _STR
#ifdef __GFORTRAN__
#  define _STR0 '&
#  define _STR(X) X'
#else
#  undef _STRING
#  define _STRING(X) # X
#  define _STR0 &
#  define _STR(X) _STRING(X)
#endif
