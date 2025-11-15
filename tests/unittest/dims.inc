#if defined(_DIM_IDS)
#  if _DIM_IDS & _DIM0
#    define _DIM_ID _DIM0
#    define _ARG_TYPE _ELEM_TYPE
#    define _DIM_LABEL
#    include "types.inc"
#    undef _DIM_ID
#    undef _ARG_TYPE
#    undef _DIM_LABEL
#  endif
#  if _DIM_IDS & _DIM1
#    define _DIM_ID _DIM1
#    define _ARG_TYPE _ELEM_TYPE, dimension(:)
#    define _DIM_LABEL 1
#    include "types.inc"
#    undef _DIM_ID
#    undef _ARG_TYPE
#    undef _DIM_LABEL
#  endif
#  if _DIM_IDS & _DIM2
#    define _DIM_ID _DIM2
#    define _ARG_TYPE _ELEM_TYPE, dimension(:, :)
#    define _DIM_LABEL 2
#    include "types.inc"
#    undef _DIM_ID
#    undef _ARG_TYPE
#    undef _DIM_LABEL
#  endif
#  if _DIM_IDS & _DIM3
#    define _DIM_ID _DIM3
#    define _ARG_TYPE _ELEM_TYPE, dimension(:, :, :)
#    define _DIM_LABEL 3
#    include "types.inc"
#    undef _DIM_ID
#    undef _ARG_TYPE
#    undef _DIM_LABEL
#  endif
#  if _DIM_IDS & _DIM4
#    define _DIM_ID _DIM4
#    define _ARG_TYPE _ELEM_TYPE, dimension(:, :, :, :)
#    define _DIM_LABEL 4
#    include "types.inc"
#    undef _DIM_ID
#    undef _ARG_TYPE
#    undef _DIM_LABEL
#  endif
#  if _DIM_IDS & _DIM5
#    define _DIM_ID _DIM5
#    define _ARG_TYPE _ELEM_TYPE, dimension(:, :, :, :, :)
#    define _DIM_LABEL 5
#    include "types.inc"
#    undef _DIM_ID
#    undef _ARG_TYPE
#    undef _DIM_LABEL
#  endif
#  if _DIM_IDS & _DIM6
#    define _DIM_ID _DIM6
#    define _ARG_TYPE _ELEM_TYPE, dimension(:, :, :, :, :, :)
#    define _DIM_LABEL 6
#    include "types.inc"
#    undef _DIM_ID
#    undef _ARG_TYPE
#    undef _DIM_LABEL
#  endif
#  if _DIM_IDS & _DIM7
#    define _DIM_ID _DIM7
#    define _ARG_TYPE _ELEM_TYPE, dimension(:, :, :, :, :, :, :)
#    define _DIM_LABEL 7
#    include "types.inc"
#    undef _DIM_ID
#    undef _ARG_TYPE
#    undef _DIM_LABEL
#  endif
#endif
