! () -> (_PASTE, _CAT, _CAT3, _CAT4, _CAT5, _CAT6, _CAT7, _CAT8, _CAT9)
! Define the concatenation macros for up to 9 arguments.  The macro for two
! arguments is `_CAT(<arg-1>,<arg-2>)`.  The macros for more arguments contain
! the number of arguments as a suffix in their names.

#undef _PASTE
#define _PASTE(X) X
#undef _CAT
#define _CAT(A,B) _PASTE(A)B
#undef _CAT3
#define _CAT3(A,B,C) _CAT(_CAT(A,B),C)
#undef _CAT4
#define _CAT4(A,B,C,D) _CAT(_CAT3(A,B,C),D)
#undef _CAT5
#define _CAT5(A,B,C,D,E) _CAT(_CAT4(A,B,C,D),E)
#undef _CAT6
#define _CAT6(A,B,C,D,E,F) _CAT(_CAT5(A,B,C,D,E),F)
#undef _CAT7
#define _CAT7(A,B,C,D,E,F,G) _CAT(_CAT6(A,B,C,D,E,F),G)
#undef _CAT8
#define _CAT8(A,B,C,D,E,F,G,H) _CAT(_CAT7(A,B,C,D,E,F,G),H)
#undef _CAT9
#define _CAT9(A,B,C,D,E,F,G,H,I) _CAT(_CAT8(A,B,C,D,E,F,G,H),I)
