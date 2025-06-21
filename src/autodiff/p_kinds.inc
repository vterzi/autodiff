#ifdef _HP
#  define _KIND _HP
#  define _KIND_LABEL HP
#  include _FILE
#  undef _KIND
#  undef _KIND_LABEL
#endif
#ifdef _SP
#  define _KIND _SP
#  define _KIND_LABEL SP
#  include _FILE
#  undef _KIND
#  undef _KIND_LABEL
#endif
#ifdef _DP
#  define _KIND _DP
#  define _KIND_LABEL DP
#  include _FILE
#  undef _KIND
#  undef _KIND_LABEL
#endif
#ifdef _XDP
#  define _KIND _XDP
#  define _KIND_LABEL XDP
#  include _FILE
#  undef _KIND
#  undef _KIND_LABEL
#endif
#ifdef _QP
#  define _KIND _QP
#  define _KIND_LABEL QP
#  include _FILE
#  undef _KIND
#  undef _KIND_LABEL
#endif
