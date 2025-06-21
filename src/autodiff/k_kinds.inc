#ifdef _K1
#  define _KIND _K1
#  define _KIND_LABEL K1
#  include _FILE
#  undef _KIND
#  undef _KIND_LABEL
#endif
#ifdef _K2
#  define _KIND _K2
#  define _KIND_LABEL K2
#  include _FILE
#  undef _KIND
#  undef _KIND_LABEL
#endif
#ifdef _K4
#  define _KIND _K4
#  define _KIND_LABEL K4
#  include _FILE
#  undef _KIND
#  undef _KIND_LABEL
#endif
#ifdef _K8
#  define _KIND _K8
#  define _KIND_LABEL K8
#  include _FILE
#  undef _KIND
#  undef _KIND_LABEL
#endif
#ifdef _K16
#  define _KIND _K16
#  define _KIND_LABEL K16
#  include _FILE
#  undef _KIND
#  undef _KIND_LABEL
#endif
