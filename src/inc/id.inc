! $1 = (
!   _KIND_BITS, _TYPE_BITS, _DIM_BITS,
!   _KIND_MASK, _TYPE_MASK, _DIM_MASK,
!   _IS_TYPE, _IS_KIND, _IS_DIM,
!   _LOGICAL, _INTEGER, _REAL, _COMPLEX, _CHARACTER,
!   _CLASS_K, _CLASS_P, _CLASS_S,
!   _1_DIMS, _2_DIMS, _3_DIMS, _4_DIMS, _5_DIMS, _6_DIMS, _7_DIMS,
! )
! $2<?> = (_ID?)
! $3<?> = (
!   _TYPE_ID?, _KIND_ID?, _DIM_ID?, _CLASS_ID?,
!   _TYPE?, _KIND?, _DIM?,
!   _DIM_AS?, _TYPE_LEN?, _ELEM_TYPE?, _TYPE_AS?, _ARG_TYPE?, _ALLOC_TYPE?,
!   _SIZE?, _EQ?, _NE?,
!   _TYPE_LABEL?, _KIND_LABEL?, _DIM_LABEL?, _LABEL?,
! )
! {_KEEP_ARGS} + ($2<>) -> ("cat.inc", $1, [$2<>], $3<>, _N_IDS)
! {_KEEP_ARGS} + ($2<1>, $2<2>) -> (
!   "cat.inc", $1, [$2<1>], [$2<2>], $3<1>, $3<2>, _N_IDS
! )
! Determine information about one basic data type `_ID` or two basic data types
! `_ID1` and `_ID2`.  `_ID?` is the disjunction of a type identifier
! (`_LOGICAL`, `_INTEGER`, `_REAL`, `_COMPLEX`, `_CHARACTER`), a kind
! identifier (`_K1`, `_K2`, `_K4`, `_K8`, `_K16`, `_HP`, `_SP`, `_DP`, `_XDP`,
! `_QP`, `_ASCII`, `_UCS4`), and a dimension identifier (`_1_DIMS`, `_2_DIMS`,
! `_3_DIMS`, `_4_DIMS`, `_5_DIMS`, `_6_DIMS`, `_7_DIMS`).  The number of
! arguments is saved in `_N_IDS`.  If `_KEEP_ARGS` is defined, the arguments
! are not undefined after the inclusion of the file.  The resulting
! informations are:
!   * `_TYPE_ID?`: type identifier,
!   * `_KIND_ID?`: kind identifier,
!   * `_DIM_ID?`: dimension identifier,
!   * `_CLASS_ID?`: kind class identifier (`_CLASS_K` for `_LOGICAL` and
!     `_INTEGER`, `_CLASS_P` for `_REAL` and `_COMPLEX`, `_CLASS_S` for
!     `_CHARACTER`),
!   * `_TYPE?`: type specifier,
!   * `_KIND?`: kind specifier,
!   * `_DIM?`: dimension attribute with deferred/assumed shape,
!   * `_DIM_AS?(<object>)`: dimension attribute with the same shape as a given
!     object,
!   * `_TYPE_LEN?(<length>)`: type specifier with a given length,
!   * `_ELEM_TYPE?`: type specifier for scalars,
!   * `_TYPE_AS?(<object>)`: type specifier with the same length and shape as a
!     given object,
!   * `_ARG_TYPE?`: type specifier for procedure arguments,
!   * `_ALLOC_TYPE?`: type specifier for allocatable variables,
!   * `_SIZE?(<object>)`: size of a given object,
!   * `_EQ?(<object-1>,<object-2>)`: equality test of two given objects,
!   * `_NE?(<object-1>,<object-2>)`: inequality test of two given objects,
!   * `_TYPE_LABEL?`: type label,
!   * `_KIND_LABEL?`: kind label,
!   * `_DIM_LABEL?`: dimension label,
!   * `_LABEL?`: combined label of type, kind, and dimension,

!   * `_LOGICAL < _INTEGER < _REAL < _COMPLEX < _CHARACTER`,
!   * `_K1 < _K2 < _K4 < _K8 < _K16`,
!   * `_HP < _SP < _DP < _XDP < _QP`,
!   * `_ASCII < _UCS4`.

#include "../inc/cat.inc"

#undef _KIND_BITS
#define _KIND_BITS 5
#undef _TYPE_BITS
#define _TYPE_BITS 3
#undef _DIM_BITS
#define _DIM_BITS 3

#undef _KIND_MASK
#define _KIND_MASK ((1 << _KIND_BITS) - 1)
#undef _TYPE_MASK
#define _TYPE_MASK (((1 << _TYPE_BITS) - 1) << _KIND_BITS)
#undef _DIM_MASK
#define _DIM_MASK (((1 << _DIM_BITS) - 1) << (_KIND_BITS + _TYPE_BITS))

#undef _IS_TYPE
#define _IS_TYPE(ID,TYPE) (((ID) & _TYPE_MASK) == TYPE)
#undef _IS_KIND
#define _IS_KIND(ID,KIND) (((ID) & _KIND_MASK) == KIND)
#undef _IS_DIM
#define _IS_DIM(ID,DIM) (((ID) & _DIM_MASK) == DIM)

#undef _LOGICAL
#define _LOGICAL (1 << _KIND_BITS)
#undef _INTEGER
#define _INTEGER (2 << _KIND_BITS)
#undef _REAL
#define _REAL (3 << _KIND_BITS)
#undef _COMPLEX
#define _COMPLEX (4 << _KIND_BITS)
#undef _CHARACTER
#define _CHARACTER (5 << _KIND_BITS)

#undef _CLASS_K
#define _CLASS_K _INTEGER
#undef _CLASS_P
#define _CLASS_P _REAL
#undef _CLASS_S
#define _CLASS_S _CHARACTER

#undef _1_DIMS
#define _1_DIMS (1 << (_KIND_BITS + _TYPE_BITS))
#undef _2_DIMS
#define _2_DIMS (2 << (_KIND_BITS + _TYPE_BITS))
#undef _3_DIMS
#define _3_DIMS (3 << (_KIND_BITS + _TYPE_BITS))
#undef _4_DIMS
#define _4_DIMS (4 << (_KIND_BITS + _TYPE_BITS))
#undef _5_DIMS
#define _5_DIMS (5 << (_KIND_BITS + _TYPE_BITS))
#undef _6_DIMS
#define _6_DIMS (6 << (_KIND_BITS + _TYPE_BITS))
#undef _7_DIMS
#define _7_DIMS (7 << (_KIND_BITS + _TYPE_BITS))

#undef _N_IDS
#if defined(_ID1) && defined(_ID2)
#  define _N_IDS 2
#  undef _TYPE_ID1
#  undef _KIND_ID1
#  undef _DIM_ID1
#  undef _CLASS_ID1
#  undef _TYPE1
#  undef _KIND1
#  undef _DIM1
#  undef _DIM_AS1
#  undef _TYPE_LEN1
#  undef _ELEM_TYPE1
#  undef _TYPE_AS1
#  undef _ARG_TYPE1
#  undef _ALLOC_TYPE1
#  undef _SIZE1
#  undef _EQ1
#  undef _NE1
#  undef _TYPE_LABEL1
#  undef _KIND_LABEL1
#  undef _DIM_LABEL1
#  undef _LABEL1
#  if _IS_DIM(_ID1,0)
#    define _SIZE1(X) 1
#    define _DIM_LABEL1
#  else
#    define _SIZE1(X) size(X)
#    if _IS_DIM(_ID1,_1_DIMS)
#      define _DIM_ID1 _1_DIMS
#      define _DIM1 dimension(:)
#      define _DIM_AS1(X) dimension(size(X,1))
#      define _DIM_LABEL1 1
#    elif _IS_DIM(_ID1,_2_DIMS)
#      define _DIM_ID1 _2_DIMS
#      define _DIM1 dimension(:,:)
#      define _DIM_AS1(X) dimension(size(X,1),size(X,2))
#      define _DIM_LABEL1 2
#    elif _IS_DIM(_ID1,_3_DIMS)
#      define _DIM_ID1 _3_DIMS
#      define _DIM1 dimension(:,:,:)
#      define _DIM_AS1(X) dimension(size(X,1),size(X,2),size(X,3))
#      define _DIM_LABEL1 3
#    elif _IS_DIM(_ID1,_4_DIMS)
#      define _DIM_ID1 _4_DIMS
#      define _DIM1 dimension(:,:,:,:)
#      define _DIM_AS1(X) dimension(size(X,1),size(X,2),size(X,3),size(X,4))
#      define _DIM_LABEL1 4
#    elif _IS_DIM(_ID1,_5_DIMS)
#      define _DIM_ID1 _5_DIMS
#      define _DIM1 dimension(:,:,:,:,:)
#      define _DIM_AS1(X) dimension(size(X,1),size(X,2),size(X,3),size(X,4),size(X,5))
#      define _DIM_LABEL1 5
#    elif _IS_DIM(_ID1,_6_DIMS)
#      define _DIM_ID1 _6_DIMS
#      define _DIM1 dimension(:,:,:,:,:,:)
#      define _DIM_AS1(X) dimension(size(X,1),size(X,2),size(X,3),size(X,4),size(X,5),size(X,6))
#      define _DIM_LABEL1 6
#    elif _IS_DIM(_ID1,_7_DIMS)
#      define _DIM_ID1 _7_DIMS
#      define _DIM1 dimension(:,:,:,:,:,:,:)
#      define _DIM_AS1(X) dimension(size(X,1),size(X,2),size(X,3),size(X,4),size(X,5),size(X,6),size(X,7))
#      define _DIM_LABEL1 7
#    else
#      error Number of dimensions of `_ID1` out of range (0..7)
#    endif
#  endif
#  define _KIND1 _KIND_ID1
#  if _IS_TYPE(_ID1,_CHARACTER)
#    define _TYPE_ID1 _CHARACTER
#    define _CLASS_ID1 _CLASS_S
#    define _TYPE1 character
#    define _TYPE_LABEL1 S
#    if defined(_ASCII) && _IS_KIND(_ID1,_ASCII)
#      define _KIND_ID1 _ASCII
#      define _KIND_LABEL1 A
#    elif defined(_UCS4) && _IS_KIND(_ID1,_UCS4)
#      define _KIND_ID1 _UCS4
#      define _KIND_LABEL1 U
#    endif
#    ifdef _KIND_ID1
#      define _TYPE_LEN1(X) _TYPE1(len=X,kind=_KIND1)
#    else
#      define _TYPE_LEN1(X) _TYPE1(len=X)
#    endif
#    define _ELEM_TYPE1 _TYPE_LEN1(:),allocatable
#  else
#    if _IS_TYPE(_ID1,_LOGICAL)
#      define _TYPE_ID1 _LOGICAL
#      define _CLASS_ID1 _CLASS_K
#      define _TYPE1 logical
#      define _TYPE_LABEL1 L
#    elif _IS_TYPE(_ID1,_INTEGER)
#      define _TYPE_ID1 _INTEGER
#      define _CLASS_ID1 _CLASS_K
#      define _TYPE1 integer
#      define _TYPE_LABEL1 I
#    elif _IS_TYPE(_ID1,_REAL)
#      define _TYPE_ID1 _REAL
#      define _CLASS_ID1 _CLASS_P
#      define _TYPE1 real
#      define _TYPE_LABEL1 R
#    elif _IS_TYPE(_ID1,_COMPLEX)
#      define _TYPE_ID1 _COMPLEX
#      define _CLASS_ID1 _CLASS_P
#      define _TYPE1 complex
#      define _TYPE_LABEL1 C
#    else
#      error Unknown type of `_ID1`
#    endif
#    if _CLASS_ID1 == _CLASS_K
#      if defined(_K1) && _IS_KIND(_ID1,_K1)
#        define _KIND_ID1 _K1
#        define _KIND_LABEL1 K1
#      elif defined(_K2) && _IS_KIND(_ID1,_K2)
#        define _KIND_ID1 _K2
#        define _KIND_LABEL1 K2
#      elif defined(_K4) && _IS_KIND(_ID1,_K4)
#        define _KIND_ID1 _K4
#        define _KIND_LABEL1 K4
#      elif defined(_K8) && _IS_KIND(_ID1,_K8)
#        define _KIND_ID1 _K8
#        define _KIND_LABEL1 K8
#      elif defined(_K16) && _IS_KIND(_ID1,_K16)
#        define _KIND_ID1 _K16
#        define _KIND_LABEL1 K16
#      endif
#    elif _CLASS_ID1 == _CLASS_P
#      if defined(_HP) && _IS_KIND(_ID1,_HP)
#        define _KIND_ID1 _HP
#        define _KIND_LABEL1 HP
#      elif defined(_SP) && _IS_KIND(_ID1,_SP)
#        define _KIND_ID1 _SP
#        define _KIND_LABEL1 SP
#      elif defined(_DP) && _IS_KIND(_ID1,_DP)
#        define _KIND_ID1 _DP
#        define _KIND_LABEL1 DP
#      elif defined(_XDP) && _IS_KIND(_ID1,_XDP)
#        define _KIND_ID1 _XDP
#        define _KIND_LABEL1 XDP
#      elif defined(_QP) && _IS_KIND(_ID1,_QP)
#        define _KIND_ID1 _QP
#        define _KIND_LABEL1 QP
#      endif
#    endif
#    ifdef _KIND_ID1
#      define _TYPE_LEN1(X) _TYPE1(_KIND1)
#    else
#      define _TYPE_LEN1(X) _TYPE1
#    endif
#    define _ELEM_TYPE1 _TYPE_LEN2(:)
#  endif
#  ifndef _KIND_ID1
#    define _KIND_ID1 0
#    undef _KIND1
#    define _KIND_LABEL1
#  endif
#  ifdef _DIM1
#    define _TYPE_AS1(X) _TYPE_LEN1(len(X)),_DIM_AS1(X)
#    define _ARG_TYPE1 _TYPE_LEN1(*),_DIM1
#    define _ALLOC_TYPE1 _TYPE_LEN1(:),_DIM1,allocatable
#    if _IS_TYPE(_ID1,_LOGICAL)
#      define _EQ1(X,Y) all(X.eqv.Y)
#      define _NE1(X,Y) any(X.neqv.Y)
#    else
#      define _EQ1(X,Y) all(X==Y)
#      define _NE1(X,Y) any(X/=Y)
#    endif
#  else
#    define _TYPE_AS1(X) _TYPE_LEN1(len(X))
#    define _ARG_TYPE1 _TYPE_LEN1(*)
#    define _ALLOC_TYPE1 _ELEM_TYPE1
#    if _IS_TYPE(_ID1,_LOGICAL)
#      define _EQ1(X,Y) X.eqv.Y
#      define _NE1(X,Y) X.neqv.Y
#    else
#      define _EQ1(X,Y) X==Y
#      define _NE1(X,Y) X/=Y
#    endif
#  endif
#  define _LABEL1 _CAT3(_TYPE_LABEL1,_DIM_LABEL1,_KIND_LABEL1)
#  undef _TYPE_ID2
#  undef _KIND_ID2
#  undef _DIM_ID2
#  undef _CLASS_ID2
#  undef _TYPE2
#  undef _KIND2
#  undef _DIM2
#  undef _DIM_AS2
#  undef _TYPE_LEN2
#  undef _ELEM_TYPE2
#  undef _TYPE_AS2
#  undef _ARG_TYPE2
#  undef _ALLOC_TYPE2
#  undef _SIZE2
#  undef _EQ2
#  undef _NE2
#  undef _TYPE_LABEL2
#  undef _KIND_LABEL2
#  undef _DIM_LABEL2
#  undef _LABEL2
#  if _IS_DIM(_ID2,0)
#    define _SIZE2(X) 1
#    define _DIM_LABEL2
#  else
#    define _SIZE2(X) size(X)
#    if _IS_DIM(_ID2,_1_DIMS)
#      define _DIM_ID2 _1_DIMS
#      define _DIM2 dimension(:)
#      define _DIM_AS2(X) dimension(size(X,1))
#      define _DIM_LABEL2 1
#    elif _IS_DIM(_ID2,_2_DIMS)
#      define _DIM_ID2 _2_DIMS
#      define _DIM2 dimension(:,:)
#      define _DIM_AS2(X) dimension(size(X,1),size(X,2))
#      define _DIM_LABEL2 2
#    elif _IS_DIM(_ID2,_3_DIMS)
#      define _DIM_ID2 _3_DIMS
#      define _DIM2 dimension(:,:,:)
#      define _DIM_AS2(X) dimension(size(X,1),size(X,2),size(X,3))
#      define _DIM_LABEL2 3
#    elif _IS_DIM(_ID2,_4_DIMS)
#      define _DIM_ID2 _4_DIMS
#      define _DIM2 dimension(:,:,:,:)
#      define _DIM_AS2(X) dimension(size(X,1),size(X,2),size(X,3),size(X,4))
#      define _DIM_LABEL2 4
#    elif _IS_DIM(_ID2,_5_DIMS)
#      define _DIM_ID2 _5_DIMS
#      define _DIM2 dimension(:,:,:,:,:)
#      define _DIM_AS2(X) dimension(size(X,1),size(X,2),size(X,3),size(X,4),size(X,5))
#      define _DIM_LABEL2 5
#    elif _IS_DIM(_ID2,_6_DIMS)
#      define _DIM_ID2 _6_DIMS
#      define _DIM2 dimension(:,:,:,:,:,:)
#      define _DIM_AS2(X) dimension(size(X,1),size(X,2),size(X,3),size(X,4),size(X,5),size(X,6))
#      define _DIM_LABEL2 6
#    elif _IS_DIM(_ID2,_7_DIMS)
#      define _DIM_ID2 _7_DIMS
#      define _DIM2 dimension(:,:,:,:,:,:,:)
#      define _DIM_AS2(X) dimension(size(X,1),size(X,2),size(X,3),size(X,4),size(X,5),size(X,6),size(X,7))
#      define _DIM_LABEL2 7
#    else
#      error Number of dimensions of `_ID2` out of range (0..7)
#    endif
#  endif
#  define _KIND2 _KIND_ID2
#  if _IS_TYPE(_ID2,_CHARACTER)
#    define _TYPE_ID2 _CHARACTER
#    define _CLASS_ID2 _CLASS_S
#    define _TYPE2 character
#    define _TYPE_LABEL2 S
#    if defined(_ASCII) && _IS_KIND(_ID2,_ASCII)
#      define _KIND_ID2 _ASCII
#      define _KIND_LABEL2 A
#    elif defined(_UCS4) && _IS_KIND(_ID2,_UCS4)
#      define _KIND_ID2 _UCS4
#      define _KIND_LABEL2 U
#    endif
#    ifdef _KIND_ID2
#      define _TYPE_LEN2(X) _TYPE2(len=X,kind=_KIND2)
#    else
#      define _TYPE_LEN2(X) _TYPE2(len=X)
#    endif
#    define _ELEM_TYPE2 _TYPE_LEN2(:),allocatable
#  else
#    if _IS_TYPE(_ID2,_LOGICAL)
#      define _TYPE_ID2 _LOGICAL
#      define _CLASS_ID2 _CLASS_K
#      define _TYPE2 logical
#      define _TYPE_LABEL2 L
#    elif _IS_TYPE(_ID2,_INTEGER)
#      define _TYPE_ID2 _INTEGER
#      define _CLASS_ID2 _CLASS_K
#      define _TYPE2 integer
#      define _TYPE_LABEL2 I
#    elif _IS_TYPE(_ID2,_REAL)
#      define _TYPE_ID2 _REAL
#      define _CLASS_ID2 _CLASS_P
#      define _TYPE2 real
#      define _TYPE_LABEL2 R
#    elif _IS_TYPE(_ID2,_COMPLEX)
#      define _TYPE_ID2 _COMPLEX
#      define _CLASS_ID2 _CLASS_P
#      define _TYPE2 complex
#      define _TYPE_LABEL2 C
#    else
#      error Unknown type of `_ID2`
#    endif
#    if _CLASS_ID2 == _CLASS_K
#      if defined(_K1) && _IS_KIND(_ID2,_K1)
#        define _KIND_ID2 _K1
#        define _KIND_LABEL2 K1
#      elif defined(_K2) && _IS_KIND(_ID2,_K2)
#        define _KIND_ID2 _K2
#        define _KIND_LABEL2 K2
#      elif defined(_K4) && _IS_KIND(_ID2,_K4)
#        define _KIND_ID2 _K4
#        define _KIND_LABEL2 K4
#      elif defined(_K8) && _IS_KIND(_ID2,_K8)
#        define _KIND_ID2 _K8
#        define _KIND_LABEL2 K8
#      elif defined(_K16) && _IS_KIND(_ID2,_K16)
#        define _KIND_ID2 _K16
#        define _KIND_LABEL2 K16
#      endif
#    elif _CLASS_ID2 == _CLASS_P
#      if defined(_HP) && _IS_KIND(_ID2,_HP)
#        define _KIND_ID2 _HP
#        define _KIND_LABEL2 HP
#      elif defined(_SP) && _IS_KIND(_ID2,_SP)
#        define _KIND_ID2 _SP
#        define _KIND_LABEL2 SP
#      elif defined(_DP) && _IS_KIND(_ID2,_DP)
#        define _KIND_ID2 _DP
#        define _KIND_LABEL2 DP
#      elif defined(_XDP) && _IS_KIND(_ID2,_XDP)
#        define _KIND_ID2 _XDP
#        define _KIND_LABEL2 XDP
#      elif defined(_QP) && _IS_KIND(_ID2,_QP)
#        define _KIND_ID2 _QP
#        define _KIND_LABEL2 QP
#      endif
#    endif
#    ifdef _KIND_ID2
#      define _TYPE_LEN2(X) _TYPE2(_KIND2)
#    else
#      define _TYPE_LEN2(X) _TYPE2
#    endif
#    define _ELEM_TYPE2 _TYPE_LEN2(:)
#  endif
#  ifndef _KIND_ID2
#    define _KIND_ID2 0
#    undef _KIND2
#    define _KIND_LABEL2
#  endif
#  ifdef _DIM2
#    define _TYPE_AS2(X) _TYPE_LEN2(len(X)),_DIM_AS2(X)
#    define _ARG_TYPE2 _TYPE_LEN2(*),_DIM2
#    define _ALLOC_TYPE2 _TYPE_LEN2(:),_DIM2,allocatable
#    if _IS_TYPE(_ID2,_LOGICAL)
#      define _EQ2(X,Y) all(X.eqv.Y)
#      define _NE2(X,Y) any(X.neqv.Y)
#    else
#      define _EQ2(X,Y) all(X==Y)
#      define _NE2(X,Y) any(X/=Y)
#    endif
#  else
#    define _TYPE_AS2(X) _TYPE_LEN2(len(X))
#    define _ARG_TYPE2 _TYPE_LEN2(*)
#    define _ALLOC_TYPE2 _ELEM_TYPE2
#    if _IS_TYPE(_ID2,_LOGICAL)
#      define _EQ2(X,Y) X.eqv.Y
#      define _NE2(X,Y) X.neqv.Y
#    else
#      define _EQ2(X,Y) X==Y
#      define _NE2(X,Y) X/=Y
#    endif
#  endif
#  define _LABEL2 _CAT3(_TYPE_LABEL2,_DIM_LABEL2,_KIND_LABEL2)
! #  undef _TYPE0
! #  undef _KIND0
! #  undef _ELEM_TYPE0
! #  if (_TYPE_ID1 | _KIND_ID1) >= (_TYPE_ID2 | _KIND_ID2)
! #    undef _TYPE_ID0
! #    undef _KIND_ID0
! #    define _TYPE_ID0 _TYPE_ID1
! #    define _KIND_ID0 _KIND_ID1
! #    define _TYPE0 _TYPE1
! #    ifdef _KIND1
! #      define _KIND0 _KIND1
! #    endif
! #    define _ELEM_TYPE0 _ELEM_TYPE1
! #  else
! #    undef _TYPE_ID0
! #    undef _KIND_ID0
! #    define _TYPE_ID0 _TYPE_ID2
! #    define _KIND_ID0 _KIND_ID2
! #    define _TYPE0 _TYPE2
! #    ifdef _KIND2
! #      define _KIND0 _KIND2
! #    endif
! #    define _ELEM_TYPE0 _ELEM_TYPE2
! #  endif
#  ifndef _KEEP_ARGS
#    undef _ID1
#    undef _ID2
#  endif
#elif defined(_ID)
#  define _N_IDS 1
#  undef _TYPE_ID
#  undef _KIND_ID
#  undef _DIM_ID
#  undef _CLASS_ID
#  undef _TYPE
#  undef _KIND
#  undef _DIM
#  undef _DIM_AS
#  undef _TYPE_LEN
#  undef _ELEM_TYPE
#  undef _TYPE_AS
#  undef _ARG_TYPE
#  undef _ALLOC_TYPE
#  undef _SIZE
#  undef _EQ
#  undef _NE
#  undef _TYPE_LABEL
#  undef _KIND_LABEL
#  undef _DIM_LABEL
#  undef _LABEL
#  if _IS_DIM(_ID,0)
#    define _SIZE(X) 1
#    define _DIM_LABEL
#  else
#    define _SIZE(X) size(X)
#    if _IS_DIM(_ID,_1_DIMS)
#      define _DIM_ID _1_DIMS
#      define _DIM dimension(:)
#      define _DIM_AS(X) dimension(size(X,1))
#      define _DIM_LABEL 1
#    elif _IS_DIM(_ID,_2_DIMS)
#      define _DIM_ID _2_DIMS
#      define _DIM dimension(:,:)
#      define _DIM_AS(X) dimension(size(X,1),size(X,2))
#      define _DIM_LABEL 2
#    elif _IS_DIM(_ID,_3_DIMS)
#      define _DIM_ID _3_DIMS
#      define _DIM dimension(:,:,:)
#      define _DIM_AS(X) dimension(size(X,1),size(X,2),size(X,3))
#      define _DIM_LABEL 3
#    elif _IS_DIM(_ID,_4_DIMS)
#      define _DIM_ID _4_DIMS
#      define _DIM dimension(:,:,:,:)
#      define _DIM_AS(X) dimension(size(X,1),size(X,2),size(X,3),size(X,4))
#      define _DIM_LABEL 4
#    elif _IS_DIM(_ID,_5_DIMS)
#      define _DIM_ID _5_DIMS
#      define _DIM dimension(:,:,:,:,:)
#      define _DIM_AS(X) dimension(size(X,1),size(X,2),size(X,3),size(X,4),size(X,5))
#      define _DIM_LABEL 5
#    elif _IS_DIM(_ID,_6_DIMS)
#      define _DIM_ID _6_DIMS
#      define _DIM dimension(:,:,:,:,:,:)
#      define _DIM_AS(X) dimension(size(X,1),size(X,2),size(X,3),size(X,4),size(X,5),size(X,6))
#      define _DIM_LABEL 6
#    elif _IS_DIM(_ID,_7_DIMS)
#      define _DIM_ID _7_DIMS
#      define _DIM dimension(:,:,:,:,:,:,:)
#      define _DIM_AS(X) dimension(size(X,1),size(X,2),size(X,3),size(X,4),size(X,5),size(X,6),size(X,7))
#      define _DIM_LABEL 7
#    else
#      error Number of dimensions of `_ID` out of range (0..7)
#    endif
#  endif
#  define _KIND _KIND_ID
#  if _IS_TYPE(_ID,_CHARACTER)
#    define _TYPE_ID _CHARACTER
#    define _CLASS_ID _CLASS_S
#    define _TYPE character
#    define _TYPE_LABEL S
#    if defined(_ASCII) && _IS_KIND(_ID,_ASCII)
#      define _KIND_ID _ASCII
#      define _KIND_LABEL A
#    elif defined(_UCS4) && _IS_KIND(_ID,_UCS4)
#      define _KIND_ID _UCS4
#      define _KIND_LABEL U
#    endif
#    ifdef _KIND_ID
#      define _TYPE_LEN(X) _TYPE(len=X,kind=_KIND)
#    else
#      define _TYPE_LEN(X) _TYPE(len=X)
#    endif
#    define _ELEM_TYPE _TYPE_LEN(:),allocatable
#  else
#    if _IS_TYPE(_ID,_LOGICAL)
#      define _TYPE_ID _LOGICAL
#      define _CLASS_ID _CLASS_K
#      define _TYPE logical
#      define _TYPE_LABEL L
#    elif _IS_TYPE(_ID,_INTEGER)
#      define _TYPE_ID _INTEGER
#      define _CLASS_ID _CLASS_K
#      define _TYPE integer
#      define _TYPE_LABEL I
#    elif _IS_TYPE(_ID,_REAL)
#      define _TYPE_ID _REAL
#      define _CLASS_ID _CLASS_P
#      define _TYPE real
#      define _TYPE_LABEL R
#    elif _IS_TYPE(_ID,_COMPLEX)
#      define _TYPE_ID _COMPLEX
#      define _CLASS_ID _CLASS_P
#      define _TYPE complex
#      define _TYPE_LABEL C
#    else
#      error Unknown type of `_ID`
#    endif
#    if _CLASS_ID == _CLASS_K
#      if defined(_K1) && _IS_KIND(_ID,_K1)
#        define _KIND_ID _K1
#        define _KIND_LABEL K1
#      elif defined(_K2) && _IS_KIND(_ID,_K2)
#        define _KIND_ID _K2
#        define _KIND_LABEL K2
#      elif defined(_K4) && _IS_KIND(_ID,_K4)
#        define _KIND_ID _K4
#        define _KIND_LABEL K4
#      elif defined(_K8) && _IS_KIND(_ID,_K8)
#        define _KIND_ID _K8
#        define _KIND_LABEL K8
#      elif defined(_K16) && _IS_KIND(_ID,_K16)
#        define _KIND_ID _K16
#        define _KIND_LABEL K16
#      endif
#    elif _CLASS_ID == _CLASS_P
#      if defined(_HP) && _IS_KIND(_ID,_HP)
#        define _KIND_ID _HP
#        define _KIND_LABEL HP
#      elif defined(_SP) && _IS_KIND(_ID,_SP)
#        define _KIND_ID _SP
#        define _KIND_LABEL SP
#      elif defined(_DP) && _IS_KIND(_ID,_DP)
#        define _KIND_ID _DP
#        define _KIND_LABEL DP
#      elif defined(_XDP) && _IS_KIND(_ID,_XDP)
#        define _KIND_ID _XDP
#        define _KIND_LABEL XDP
#      elif defined(_QP) && _IS_KIND(_ID,_QP)
#        define _KIND_ID _QP
#        define _KIND_LABEL QP
#      endif
#    endif
#    ifdef _KIND_ID
#      define _TYPE_LEN(X) _TYPE(_KIND)
#    else
#      define _TYPE_LEN(X) _TYPE
#    endif
#    define _ELEM_TYPE _TYPE_LEN2(:)
#  endif
#  ifndef _KIND_ID
#    define _KIND_ID 0
#    undef _KIND
#    define _KIND_LABEL
#  endif
#  ifdef _DIM
#    define _TYPE_AS(X) _TYPE_LEN(len(X)),_DIM_AS(X)
#    define _ARG_TYPE _TYPE_LEN(*),_DIM
#    define _ALLOC_TYPE _TYPE_LEN(:),_DIM,allocatable
#    if _IS_TYPE(_ID,_LOGICAL)
#      define _EQ(X,Y) all(X.eqv.Y)
#      define _NE(X,Y) any(X.neqv.Y)
#    else
#      define _EQ(X,Y) all(X==Y)
#      define _NE(X,Y) any(X/=Y)
#    endif
#  else
#    define _TYPE_AS(X) _TYPE_LEN(len(X))
#    define _ARG_TYPE _TYPE_LEN(*)
#    define _ALLOC_TYPE _ELEM_TYPE
#    if _IS_TYPE(_ID,_LOGICAL)
#      define _EQ(X,Y) X.eqv.Y
#      define _NE(X,Y) X.neqv.Y
#    else
#      define _EQ(X,Y) X==Y
#      define _NE(X,Y) X/=Y
#    endif
#  endif
#  define _LABEL _CAT3(_TYPE_LABEL,_DIM_LABEL,_KIND_LABEL)
#  ifndef _KEEP_ARGS
#    undef _ID
#  endif
#else
#  error Two arguments `_ID1` and `_ID2` or one argument `_ID` required
#endif
