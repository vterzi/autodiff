#if _CLASS_ID == _CLASS_K
#  ifdef _K1
module procedure::_PROC(K1)
#  endif
#  ifdef _K2
module procedure::_PROC(K2)
#  endif
#  ifdef _K4
module procedure::_PROC(K4)
#  endif
#  ifdef _K8
module procedure::_PROC(K8)
#  endif
#  ifdef _K16
module procedure::_PROC(K16)
#  endif
#elif _CLASS_ID == _CLASS_P
#  ifdef _HP
module procedure::_PROC(HP)
#  endif
#  ifdef _SP
module procedure::_PROC(SP)
#  endif
#  ifdef _DP
module procedure::_PROC(DP)
#  endif
#  ifdef _XDP
module procedure::_PROC(XDP)
#  endif
#  ifdef _QP
module procedure::_PROC(QP)
#  endif
#endif
