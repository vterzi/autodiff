#if defined(_TYPE_ID)
#  if (_TYPE_ID == _LOGICAL) || (_TYPE_ID == _INTEGER)
#    ifdef _K1
#      define _KIND _K1
#      define _KIND_LABEL K1
#      include _FILE
#      undef _KIND
#      undef _KIND_LABEL
#    endif
#    ifdef _K2
#      define _KIND _K2
#      define _KIND_LABEL K2
#      include _FILE
#      undef _KIND
#      undef _KIND_LABEL
#    endif
#    ifdef _K4
#      define _KIND _K4
#      define _KIND_LABEL K4
#      include _FILE
#      undef _KIND
#      undef _KIND_LABEL
#    endif
#    ifdef _K8
#      define _KIND _K8
#      define _KIND_LABEL K8
#      include _FILE
#      undef _KIND
#      undef _KIND_LABEL
#    endif
#    ifdef _K16
#      define _KIND _K16
#      define _KIND_LABEL K16
#      include _FILE
#      undef _KIND
#      undef _KIND_LABEL
#    endif
#  elif (_TYPE_ID == _REAL) || (_TYPE_ID == _COMPLEX)
#    ifdef _HP
#      define _KIND _HP
#      define _KIND_LABEL HP
#      include _FILE
#      undef _KIND
#      undef _KIND_LABEL
#    endif
#    ifdef _SP
#      define _KIND _SP
#      define _KIND_LABEL SP
#      include _FILE
#      undef _KIND
#      undef _KIND_LABEL
#    endif
#    ifdef _DP
#      define _KIND _DP
#      define _KIND_LABEL DP
#      include _FILE
#      undef _KIND
#      undef _KIND_LABEL
#    endif
#    ifdef _XDP
#      define _KIND _XDP
#      define _KIND_LABEL XDP
#      include _FILE
#      undef _KIND
#      undef _KIND_LABEL
#    endif
#    ifdef _QP
#      define _KIND _QP
#      define _KIND_LABEL QP
#      include _FILE
#      undef _KIND
#      undef _KIND_LABEL
#    endif
#  endif
#endif
