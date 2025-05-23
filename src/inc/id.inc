! $1 = (_LOGICAL, _INTEGER, _REAL, _COMPLEX, _CHARACTER, _CLASS_K, _CLASS_P, _CLASS_S)
! $2<?> = (_ID?, [_DIM?])
! $3<?> = (_CLASS?, _TYPE?, _KIND?, _ELEM_TYPE?, _ARG_TYPE?, _ALLOC_TYPE?, _TYPE_LEN?, _TYPE_AS?, _TYPE_NAME?, _TYPE_LABEL?,
!   _KIND_LABEL?, _DIM_LABEL?, _LABEL?, _SIZE?, [_NUMBER?], _EQ?, _NE?, [_DIM_EMPTY?], [_DIM_AS?])
! {_KEEP_ARGS} + ($2<>) -(_DIFF)> ("cat.inc", [$2<>], $1, $3<>, _N_IDS)
! {_KEEP_ARGS} + ($2<1>, $2<2>) -(_DIFF)> ("cat.inc", [$2<1>], [$2<2>], $1, $3<1>, $3<2>, $3<0>, _N_IDS)
! Determine information about one basic data type `_ID` or two basic data types `_ID1` and `_ID2`.  `_ID?` is the sum of a type
! value (`_LOGICAL`, `_INTEGER`, `_REAL`, `_COMPLEX`, `_CHARACTER`) and a kind value (`_K1`, `_K2`, `_K4`, `_K16`, `_HP`, `_SP`,
! `_DP`, `_XDP`, `_QP`, `_ASCII`, `_UCS4`).  The number of data type as arguments is saved in `_N_IDS`.  Dimensionality of data
! types can be specified by the optional arguments `_DIM` or `_DIM1` and `_DIM2`.  If `_KEEP_ARGS` is defined, the arguments are not
! undefined at the end of the file.  The resulting informations are:
!   * `_CLASS?`: the kind class of the type (`_CLASS_K` for logical or integer, `_CLASS_P` for real or complex, `_CLASS_S` for
!     character),
!   * `_TYPE?`: the type value,
!   * `_KIND?`: the kind value,
!   * `_ELEM_TYPE?`: the type specifier for declarations of scalar variables,
!   * `_ARG_TYPE?`: the type specifier for declarations of procedure arguments,
!   * `_ALLOC_TYPE?`: the type specifier for declarations of allocatable variables,
!   * `_TYPE_LEN?(<length>)`: the type specifier for declarations of character variables with a given length,
!   * `_TYPE_AS?(<object>)`: the type specifier for declarations of variables with the same length and dimensions as a given object,
!   * `_TYPE_NAME?`: the full name of the type,
!   * `_TYPE_LABEL?`: the type label,
!   * `_KIND_LABEL?`: the kind label,
!   * `_DIM_LABEL?`: the dimension label,
!   * `_LABEL?`: the combined label of the type, the kind, and the dimension,
!   * `_SIZE?(<object>)`: the size of a given object,
!   * `_EQ?(<object_1>,<object_2>)`: the comparison of two given objects for equality,
!   * `_NE?(<object_1>,<object_2>)`: the comparison of two given objects for inequality,
!   * `_NUMBER?`: a defined variable if the type is a number type.
! In the case of two arguments, the information of the larger type and kind value (value of `_ID?`) is copied to variables with the
! label `0` ($2<0>).
!   * `_LOGICAL < _INTEGER < _REAL < _COMPLEX < _CHARACTER`,
!   * `_K1 < _K2 < _K4 < _K8 < _K16`,
!   * `_HP < _SP < _DP < _XDP < _QP`,
!   * `_ASCII < _UCS4`.

#include "../inc/cat.inc"

#undef _LOGICAL
#define _LOGICAL (_MAX_KIND+1)
#undef _INTEGER
#define _INTEGER (_LOGICAL+_MAX_KIND+1)
#undef _REAL
#define _REAL (_INTEGER+_MAX_KIND+1)
#undef _COMPLEX
#define _COMPLEX (_REAL+_MAX_KIND+1)
#undef _CHARACTER
#define _CHARACTER (_COMPLEX+_MAX_KIND+1)
#undef _CLASS_K
#define _CLASS_K _INTEGER
#undef _CLASS_P
#define _CLASS_P _REAL
#undef _CLASS_S
#define _CLASS_S _CHARACTER

#undef _N_IDS
#if defined(_ID1) & defined(_ID2)
#  define _N_IDS 2
#  undef _TYPE_NAME1
#  undef _CLASS1
#  undef _KIND1
#  undef _ELEM_TYPE1
#  undef _ARG_TYPE1
#  undef _ALLOC_TYPE1
#  undef _TYPE_LEN1
#  undef _TYPE_AS1
#  undef _TYPE_LABEL1
#  undef _KIND_LABEL1
#  undef _DIM_LABEL1
#  undef _LABEL1
#  undef _SIZE1
#  undef _NUMBER1
#  undef _EQ1
#  undef _NE1
#  undef _DIM_EMPTY1
#  undef _DIM_AS1
#  ifndef _DIM1
#    define _DIM1 0
#  endif
#  if _DIM1 == 0
#    define _DIM_LABEL1
#    define _SIZE1(X) 1
#  else
#    define _DIM_LABEL1 _CAT(D,_DIM1)
#    define _SIZE1(X) size(X)
#    if _DIM1 == 1
#      define _DIM_EMPTY1 dimension(:)
#      define _DIM_AS1(X) dimension(size(X,1))
#    elif _DIM1 == 2
#      define _DIM_EMPTY1 dimension(:,:)
#      define _DIM_AS1(X) dimension(size(X,1),size(X,2))
#    elif _DIM1 == 3
#      define _DIM_EMPTY1 dimension(:,:,:)
#      define _DIM_AS1(X) dimension(size(X,1),size(X,2),size(X,3))
#    elif _DIM1 == 4
#      define _DIM_EMPTY1 dimension(:,:,:,:)
#      define _DIM_AS1(X) dimension(size(X,1),size(X,2),size(X,3),size(X,4))
#    elif _DIM1 == 5
#      define _DIM_EMPTY1 dimension(:,:,:,:,:)
#      define _DIM_AS1(X) dimension(size(X,1),size(X,2),size(X,3),size(X,4),size(X,5))
#    elif _DIM1 == 6
#      define _DIM_EMPTY1 dimension(:,:,:,:,:,:)
#      define _DIM_AS1(X) dimension(size(X,1),size(X,2),size(X,3),size(X,4),size(X,5),size(X,6))
#    elif _DIM1 == 7
#      define _DIM_EMPTY1 dimension(:,:,:,:,:,:,:)
#      define _DIM_AS1(X) dimension(size(X,1),size(X,2),size(X,3),size(X,4),size(X,5),size(X,6),size(X,7))
#    else
#      error The value of the argument `_DIM1` out of range (0..7)
#    endif
#  endif
#  if _CHARACTER <= _ID1 & _ID1 <= _CHARACTER + _MAX_KIND
#    define _TYPE_NAME1 character
#    define _TYPE_LABEL1 S
#    undef _TYPE1
#    define _TYPE1 _CHARACTER
#    define _CLASS1 _CLASS_S
#    define _DIFF (_ID1-_TYPE1)
#    if defined(_ASCII) & _DIFF == _ASCII
#      define _KIND1 ASCII
#      define _KIND_LABEL1 A
#    elif defined(_UCS4) & _DIFF == _UCS4
#      define _KIND1 UCS4
#      define _KIND_LABEL1 U
#    else
#      define _KIND_LABEL1
#    endif
#    ifdef _KIND1
#      define _TYPE_LEN1(X) _TYPE_NAME1(len=X, kind=_KIND1)
#    else
#      define _TYPE_LEN1(X) _TYPE_NAME1(len=X)
#    endif
#    ifdef _DIM_AS1
#      define _ARG_TYPE1 _TYPE_LEN1(*), _DIM_EMPTY1
#      define _ALLOC_TYPE1 _TYPE_LEN1(:), _DIM_EMPTY1, allocatable
#      define _ELEM_TYPE1 _TYPE_LEN1(:), allocatable
#      define _TYPE_AS1(X) _TYPE_LEN1(len(X)), _DIM_AS1(X)
#      define _EQ1(X,Y) all(X == Y)
#      define _NE1(X,Y) any(X /= Y)
#    else
#      define _ARG_TYPE1 _TYPE_LEN1(*)
#      define _ALLOC_TYPE1 _TYPE_LEN1(:), allocatable
#      define _ELEM_TYPE1 _ALLOC_TYPE1
#      define _TYPE_AS1(X) _TYPE_LEN1(len(X))
#      define _EQ1(X,Y) X == Y
#      define _NE1(X,Y) X /= Y
#    endif
#  else
#    if _LOGICAL <= _ID1 & _ID1 <= _LOGICAL + _MAX_KIND
#      define _TYPE_NAME1 logical
#      define _TYPE_LABEL1 L
#      undef _TYPE1
#      define _TYPE1 _LOGICAL
#      define _CLASS1 _CLASS_K
#    elif _INTEGER <= _ID1 & _ID1 <= _INTEGER + _MAX_KIND
#      define _TYPE_NAME1 integer
#      define _TYPE_LABEL1 I
#      undef _TYPE1
#      define _TYPE1 _INTEGER
#      define _CLASS1 _CLASS_K
#      define _NUMBER1
#    elif _REAL <= _ID1 & _ID1 <= _REAL + _MAX_KIND
#      define _TYPE_NAME1 real
#      define _TYPE_LABEL1 R
#      undef _TYPE1
#      define _TYPE1 _REAL
#      define _CLASS1 _CLASS_P
#      define _NUMBER1
#    elif _COMPLEX <= _ID1 & _ID1 <= _COMPLEX + _MAX_KIND
#      define _TYPE_NAME1 complex
#      define _TYPE_LABEL1 C
#      undef _TYPE1
#      define _TYPE1 _COMPLEX
#      define _CLASS1 _CLASS_P
#      define _NUMBER1
#    else
#      error Unknown type of `_ID1`
#    endif
#    define _DIFF (_ID1-_TYPE1)
#    if _CLASS1 == _CLASS_K
#      if defined(_K1) & _DIFF == _K1
#        define _KIND1 K1
#      elif defined(_K2) & _DIFF == _K2
#        define _KIND1 K2
#      elif defined(_K4) & _DIFF == _K4
#        define _KIND1 K4
#      elif defined(_K8) & _DIFF == _K8
#        define _KIND1 K8
#      elif defined(_K16) & _DIFF == _K16
#        define _KIND1 K16
#      endif
#    elif _CLASS1 == _CLASS_P
#      if defined(_HP) & _DIFF == _HP
#        define _KIND1 HP
#      elif defined(_SP) & _DIFF == _SP
#        define _KIND1 SP
#      elif defined(_DP) & _DIFF == _DP
#        define _KIND1 DP
#      elif defined(_XDP) & _DIFF == _XDP
#        define _KIND1 XDP
#      elif defined(_QP) & _DIFF == _QP
#        define _KIND1 QP
#      endif
#    endif
#    ifdef _KIND1
#      define _ELEM_TYPE1 _TYPE_NAME1(_KIND1)
#      define _KIND_LABEL1 _KIND1
#    else
#      define _ELEM_TYPE1 _TYPE_NAME1
#      define _KIND_LABEL1
#    endif
#    ifdef _DIM_AS1
#      define _ARG_TYPE1 _ELEM_TYPE1, _DIM_EMPTY1
#      define _ALLOC_TYPE1 _ARG_TYPE1, allocatable
#      define _TYPE_LEN1(X) _ALLOC_TYPE1
#      define _TYPE_AS1(X) _ELEM_TYPE1, _DIM_AS1(X)
#      ifdef _NUMBER1
#        define _EQ1(X,Y) all(X == Y)
#        define _NE1(X,Y) any(X /= Y)
#      else
#        define _EQ1(X,Y) all(X .eqv. Y)
#        define _NE1(X,Y) any(X .neqv. Y)
#      endif
#    else
#      define _ARG_TYPE1 _ELEM_TYPE1
#      define _ALLOC_TYPE1 _ELEM_TYPE1
#      define _TYPE_LEN1(X) _ELEM_TYPE1
#      define _TYPE_AS1(X) _ELEM_TYPE1
#      ifdef _NUMBER1
#        define _EQ1(X,Y) X == Y
#        define _NE1(X,Y) X /= Y
#      else
#        define _EQ1(X,Y) X .eqv. Y
#        define _NE1(X,Y) X .neqv. Y
#      endif
#    endif
#  endif
#  define _LABEL1 _CAT3(_TYPE_LABEL1,_KIND_LABEL1,_DIM_LABEL1)
#  undef _DIFF
#  undef _TYPE_NAME2
#  undef _CLASS2
#  undef _KIND2
#  undef _ELEM_TYPE2
#  undef _ARG_TYPE2
#  undef _ALLOC_TYPE2
#  undef _TYPE_LEN2
#  undef _TYPE_AS2
#  undef _TYPE_LABEL2
#  undef _KIND_LABEL2
#  undef _DIM_LABEL2
#  undef _LABEL2
#  undef _SIZE2
#  undef _NUMBER2
#  undef _EQ2
#  undef _NE2
#  undef _DIM_EMPTY2
#  undef _DIM_AS2
#  ifndef _DIM2
#    define _DIM2 0
#  endif
#  if _DIM2 == 0
#    define _DIM_LABEL2
#    define _SIZE2(X) 1
#  else
#    define _DIM_LABEL2 _CAT(D,_DIM2)
#    define _SIZE2(X) size(X)
#    if _DIM2 == 1
#      define _DIM_EMPTY2 dimension(:)
#      define _DIM_AS2(X) dimension(size(X,1))
#    elif _DIM2 == 2
#      define _DIM_EMPTY2 dimension(:,:)
#      define _DIM_AS2(X) dimension(size(X,1),size(X,2))
#    elif _DIM2 == 3
#      define _DIM_EMPTY2 dimension(:,:,:)
#      define _DIM_AS2(X) dimension(size(X,1),size(X,2),size(X,3))
#    elif _DIM2 == 4
#      define _DIM_EMPTY2 dimension(:,:,:,:)
#      define _DIM_AS2(X) dimension(size(X,1),size(X,2),size(X,3),size(X,4))
#    elif _DIM2 == 5
#      define _DIM_EMPTY2 dimension(:,:,:,:,:)
#      define _DIM_AS2(X) dimension(size(X,1),size(X,2),size(X,3),size(X,4),size(X,5))
#    elif _DIM2 == 6
#      define _DIM_EMPTY2 dimension(:,:,:,:,:,:)
#      define _DIM_AS2(X) dimension(size(X,1),size(X,2),size(X,3),size(X,4),size(X,5),size(X,6))
#    elif _DIM2 == 7
#      define _DIM_EMPTY2 dimension(:,:,:,:,:,:,:)
#      define _DIM_AS2(X) dimension(size(X,1),size(X,2),size(X,3),size(X,4),size(X,5),size(X,6),size(X,7))
#    else
#      error The value of the argument `_DIM2` out of range (0..7)
#    endif
#  endif
#  if _CHARACTER <= _ID2 & _ID2 <= _CHARACTER + _MAX_KIND
#    define _TYPE_NAME2 character
#    define _TYPE_LABEL2 S
#    undef _TYPE2
#    define _TYPE2 _CHARACTER
#    define _CLASS2 _CLASS_S
#    define _DIFF (_ID2-_TYPE2)
#    if defined(_ASCII) & _DIFF == _ASCII
#      define _KIND2 ASCII
#      define _KIND_LABEL2 A
#    elif defined(_UCS4) & _DIFF == _UCS4
#      define _KIND2 UCS4
#      define _KIND_LABEL2 U
#    else
#      define _KIND_LABEL2
#    endif
#    ifdef _KIND2
#      define _TYPE_LEN2(X) _TYPE_NAME2(len=X, kind=_KIND2)
#    else
#      define _TYPE_LEN2(X) _TYPE_NAME2(len=X)
#    endif
#    ifdef _DIM_AS2
#      define _ARG_TYPE2 _TYPE_LEN2(*), _DIM_EMPTY2
#      define _ALLOC_TYPE2 _TYPE_LEN2(:), _DIM_EMPTY2, allocatable
#      define _ELEM_TYPE2 _TYPE_LEN2(:), allocatable
#      define _TYPE_AS2(X) _TYPE_LEN2(len(X)), _DIM_AS2(X)
#      define _EQ2(X,Y) all(X == Y)
#      define _NE2(X,Y) any(X /= Y)
#    else
#      define _ARG_TYPE2 _TYPE_LEN2(*)
#      define _ALLOC_TYPE2 _TYPE_LEN2(:), allocatable
#      define _ELEM_TYPE2 _ALLOC_TYPE2
#      define _TYPE_AS2(X) _TYPE_LEN2(len(X))
#      define _EQ2(X,Y) X == Y
#      define _NE2(X,Y) X /= Y
#    endif
#  else
#    if _LOGICAL <= _ID2 & _ID2 <= _LOGICAL + _MAX_KIND
#      define _TYPE_NAME2 logical
#      define _TYPE_LABEL2 L
#      undef _TYPE2
#      define _TYPE2 _LOGICAL
#      define _CLASS2 _CLASS_K
#    elif _INTEGER <= _ID2 & _ID2 <= _INTEGER + _MAX_KIND
#      define _TYPE_NAME2 integer
#      define _TYPE_LABEL2 I
#      undef _TYPE2
#      define _TYPE2 _INTEGER
#      define _CLASS2 _CLASS_K
#      define _NUMBER2
#    elif _REAL <= _ID2 & _ID2 <= _REAL + _MAX_KIND
#      define _TYPE_NAME2 real
#      define _TYPE_LABEL2 R
#      undef _TYPE2
#      define _TYPE2 _REAL
#      define _CLASS2 _CLASS_P
#      define _NUMBER2
#    elif _COMPLEX <= _ID2 & _ID2 <= _COMPLEX + _MAX_KIND
#      define _TYPE_NAME2 complex
#      define _TYPE_LABEL2 C
#      undef _TYPE2
#      define _TYPE2 _COMPLEX
#      define _CLASS2 _CLASS_P
#      define _NUMBER2
#    else
#      error Unknown type of `_ID2`
#    endif
#    define _DIFF (_ID2-_TYPE2)
#    if _CLASS2 == _CLASS_K
#      if defined(_K1) & _DIFF == _K1
#        define _KIND2 K1
#      elif defined(_K2) & _DIFF == _K2
#        define _KIND2 K2
#      elif defined(_K4) & _DIFF == _K4
#        define _KIND2 K4
#      elif defined(_K8) & _DIFF == _K8
#        define _KIND2 K8
#      elif defined(_K16) & _DIFF == _K16
#        define _KIND2 K16
#      endif
#    elif _CLASS2 == _CLASS_P
#      if defined(_HP) & _DIFF == _HP
#        define _KIND2 HP
#      elif defined(_SP) & _DIFF == _SP
#        define _KIND2 SP
#      elif defined(_DP) & _DIFF == _DP
#        define _KIND2 DP
#      elif defined(_XDP) & _DIFF == _XDP
#        define _KIND2 XDP
#      elif defined(_QP) & _DIFF == _QP
#        define _KIND2 QP
#      endif
#    endif
#    ifdef _KIND2
#      define _ELEM_TYPE2 _TYPE_NAME2(_KIND2)
#      define _KIND_LABEL2 _KIND2
#    else
#      define _ELEM_TYPE2 _TYPE_NAME2
#      define _KIND_LABEL2
#    endif
#    ifdef _DIM_AS2
#      define _ARG_TYPE2 _ELEM_TYPE2, _DIM_EMPTY2
#      define _ALLOC_TYPE2 _ARG_TYPE2, allocatable
#      define _TYPE_LEN2(X) _ALLOC_TYPE2
#      define _TYPE_AS2(X) _ELEM_TYPE2, _DIM_AS2(X)
#      ifdef _NUMBER2
#        define _EQ2(X,Y) all(X == Y)
#        define _NE2(X,Y) any(X /= Y)
#      else
#        define _EQ2(X,Y) all(X .eqv. Y)
#        define _NE2(X,Y) any(X .neqv. Y)
#      endif
#    else
#      define _ARG_TYPE2 _ELEM_TYPE2
#      define _ALLOC_TYPE2 _ELEM_TYPE2
#      define _TYPE_LEN2(X) _ELEM_TYPE2
#      define _TYPE_AS2(X) _ELEM_TYPE2
#      ifdef _NUMBER2
#        define _EQ2(X,Y) X == Y
#        define _NE2(X,Y) X /= Y
#      else
#        define _EQ2(X,Y) X .eqv. Y
#        define _NE2(X,Y) X .neqv. Y
#      endif
#    endif
#  endif
#  define _LABEL2 _CAT3(_TYPE_LABEL2,_KIND_LABEL2,_DIM_LABEL2)
#  undef _DIFF
#  undef _TYPE_NAME0
#  undef _CLASS0
#  undef _KIND0
#  undef _ELEM_TYPE0
#  undef _ARG_TYPE0
#  undef _ALLOC_TYPE0
#  undef _TYPE_LEN0
#  undef _TYPE_AS0
#  undef _TYPE_LABEL0
#  undef _KIND_LABEL0
#  undef _DIM_LABEL0
#  undef _LABEL0
#  undef _SIZE0
#  undef _NUMBER0
#  undef _EQ0
#  undef _NE0
#  if _ID1 >= _ID2
#    define _TYPE_NAME0 _TYPE_NAME1
#    undef _TYPE0
#    define _TYPE0 _TYPE1
#    define _CLASS0 _CLASS1
#    ifdef _KIND1
#      define _KIND0 _KIND1
#    endif
#    define _ELEM_TYPE0 _ELEM_TYPE1
#    define _ARG_TYPE0 _ARG_TYPE1
#    define _ALLOC_TYPE0 _ALLOC_TYPE1
#    define _TYPE_LEN0 _TYPE_LEN1
#    define _TYPE_AS0 _TYPE_AS1
#    define _TYPE_LABEL0 _TYPE_LABEL1
#    define _KIND_LABEL0 _KIND_LABEL1
#    define _DIM_LABEL0 _DIM_LABEL1
#    define _LABEL0 _LABEL1
#    define _SIZE0 _SIZE1
#    define _EQ0 _EQ1
#    define _NE0 _NE1
#  else
#    define _TYPE_NAME0 _TYPE_NAME2
#    undef _TYPE0
#    define _TYPE0 _TYPE2
#    define _CLASS0 _CLASS2
#    ifdef _KIND2
#      define _KIND0 _KIND2
#    endif
#    define _ELEM_TYPE0 _ELEM_TYPE2
#    define _ARG_TYPE0 _ARG_TYPE2
#    define _ALLOC_TYPE0 _ALLOC_TYPE2
#    define _TYPE_LEN0 _TYPE_LEN2
#    define _TYPE_AS0 _TYPE_AS2
#    define _TYPE_LABEL0 _TYPE_LABEL2
#    define _KIND_LABEL0 _KIND_LABEL2
#    define _DIM_LABEL0 _DIM_LABEL2
#    define _LABEL0 _LABEL2
#    define _SIZE0 _SIZE2
#    define _EQ0 _EQ2
#    define _NE0 _NE2
#  endif
#  ifndef _KEEP_ARGS
#    undef _ID1
#    undef _ID2
#    undef _DIM1
#    undef _DIM2
#  endif
#elif defined(_ID)
#  define _N_IDS 1
#  undef _TYPE_NAME
#  undef _CLASS
#  undef _KIND
#  undef _ELEM_TYPE
#  undef _ARG_TYPE
#  undef _ALLOC_TYPE
#  undef _TYPE_LEN
#  undef _TYPE_AS
#  undef _TYPE_LABEL
#  undef _KIND_LABEL
#  undef _DIM_LABEL
#  undef _LABEL
#  undef _NUMBER
#  undef _EQ
#  undef _NE
#  undef _DIM_EMPTY
#  undef _DIM_AS
#  ifndef _DIM
#    define _DIM 0
#  endif
#  if _DIM == 0
#    define _DIM_LABEL
#  else
#    define _DIM_LABEL _CAT(D,_DIM)
#    if _DIM == 1
#      define _DIM_EMPTY dimension(:)
#      define _DIM_AS(X) dimension(size(X,1))
#    elif _DIM == 2
#      define _DIM_EMPTY dimension(:,:)
#      define _DIM_AS(X) dimension(size(X,1),size(X,2))
#    elif _DIM == 3
#      define _DIM_EMPTY dimension(:,:,:)
#      define _DIM_AS(X) dimension(size(X,1),size(X,2),size(X,3))
#    elif _DIM == 4
#      define _DIM_EMPTY dimension(:,:,:,:)
#      define _DIM_AS(X) dimension(size(X,1),size(X,2),size(X,3),size(X,4))
#    elif _DIM == 5
#      define _DIM_EMPTY dimension(:,:,:,:,:)
#      define _DIM_AS(X) dimension(size(X,1),size(X,2),size(X,3),size(X,4),size(X,5))
#    elif _DIM == 6
#      define _DIM_EMPTY dimension(:,:,:,:,:,:)
#      define _DIM_AS(X) dimension(size(X,1),size(X,2),size(X,3),size(X,4),size(X,5),size(X,6))
#    elif _DIM == 7
#      define _DIM_EMPTY dimension(:,:,:,:,:,:,:)
#      define _DIM_AS(X) dimension(size(X,1),size(X,2),size(X,3),size(X,4),size(X,5),size(X,6),size(X,7))
#    else
#      error The value of the argument `_DIM` out of range (0..7)
#    endif
#  endif
#  if _CHARACTER <= _ID & _ID <= _CHARACTER + _MAX_KIND
#    define _TYPE_NAME character
#    define _TYPE_LABEL S
#    undef _TYPE
#    define _TYPE _CHARACTER
#    define _CLASS _CLASS_S
#    define _DIFF (_ID-_TYPE)
#    if defined(_ASCII) & _DIFF == _ASCII
#      define _KIND ASCII
#      define _KIND_LABEL A
#    elif defined(_UCS4) & _DIFF == _UCS4
#      define _KIND UCS4
#      define _KIND_LABEL U
#    else
#      define _KIND_LABEL
#    endif
#    ifdef _KIND
#      define _TYPE_LEN(X) _TYPE_NAME(len=X, kind=_KIND)
#    else
#      define _TYPE_LEN(X) _TYPE_NAME(len=X)
#    endif
#    ifdef _DIM_AS
#      define _ARG_TYPE _TYPE_LEN(*), _DIM_EMPTY
#      define _ALLOC_TYPE _TYPE_LEN(:), _DIM_EMPTY, allocatable
#      define _ELEM_TYPE _TYPE_LEN(:), allocatable
#      define _TYPE_AS(X) _TYPE_LEN(len(X)), _DIM_AS(X)
#      define _EQ(X,Y) all(X == Y)
#      define _NE(X,Y) any(X /= Y)
#    else
#      define _ARG_TYPE _TYPE_LEN(*)
#      define _ALLOC_TYPE _TYPE_LEN(:), allocatable
#      define _ELEM_TYPE _ALLOC_TYPE
#      define _TYPE_AS(X) _TYPE_LEN(len(X))
#      define _EQ(X,Y) X == Y
#      define _NE(X,Y) X /= Y
#    endif
#  else
#    if _LOGICAL <= _ID & _ID <= _LOGICAL + _MAX_KIND
#      define _TYPE_NAME logical
#      define _TYPE_LABEL L
#      undef _TYPE
#      define _TYPE _LOGICAL
#      define _CLASS _CLASS_K
#    elif _INTEGER <= _ID & _ID <= _INTEGER + _MAX_KIND
#      define _TYPE_NAME integer
#      define _TYPE_LABEL I
#      undef _TYPE
#      define _TYPE _INTEGER
#      define _CLASS _CLASS_K
#      define _NUMBER
#    elif _REAL <= _ID & _ID <= _REAL + _MAX_KIND
#      define _TYPE_NAME real
#      define _TYPE_LABEL R
#      undef _TYPE
#      define _TYPE _REAL
#      define _CLASS _CLASS_P
#      define _NUMBER
#    elif _COMPLEX <= _ID & _ID <= _COMPLEX + _MAX_KIND
#      define _TYPE_NAME complex
#      define _TYPE_LABEL C
#      undef _TYPE
#      define _TYPE _COMPLEX
#      define _CLASS _CLASS_P
#      define _NUMBER
#    else
#      error Unknown type of `_ID`
#    endif
#    define _DIFF (_ID-_TYPE)
#    if _CLASS == _CLASS_K
#      if defined(_K1) & _DIFF == _K1
#        define _KIND K1
#      elif defined(_K2) & _DIFF == _K2
#        define _KIND K2
#      elif defined(_K4) & _DIFF == _K4
#        define _KIND K4
#      elif defined(_K8) & _DIFF == _K8
#        define _KIND K8
#      elif defined(_K16) & _DIFF == _K16
#        define _KIND K16
#      endif
#    elif _CLASS == _CLASS_P
#      if defined(_HP) & _DIFF == _HP
#        define _KIND HP
#      elif defined(_SP) & _DIFF == _SP
#        define _KIND SP
#      elif defined(_DP) & _DIFF == _DP
#        define _KIND DP
#      elif defined(_XDP) & _DIFF == _XDP
#        define _KIND XDP
#      elif defined(_QP) & _DIFF == _QP
#        define _KIND QP
#      endif
#    endif
#    ifdef _KIND
#      define _ELEM_TYPE _TYPE_NAME(_KIND)
#      define _KIND_LABEL _KIND
#    else
#      define _ELEM_TYPE _TYPE_NAME
#      define _KIND_LABEL
#    endif
#    ifdef _DIM_AS
#      define _ARG_TYPE _ELEM_TYPE, _DIM_EMPTY
#      define _ALLOC_TYPE _ARG_TYPE, allocatable
#      define _TYPE_LEN(X) _ALLOC_TYPE
#      define _TYPE_AS(X) _ELEM_TYPE, _DIM_AS(X)
#      ifdef _NUMBER
#        define _EQ(X,Y) all(X == Y)
#        define _NE(X,Y) any(X /= Y)
#      else
#        define _EQ(X,Y) all(X .eqv. Y)
#        define _NE(X,Y) any(X .neqv. Y)
#      endif
#    else
#      define _ARG_TYPE _ELEM_TYPE
#      define _ALLOC_TYPE _ELEM_TYPE
#      define _TYPE_LEN(X) _ELEM_TYPE
#      define _TYPE_AS(X) _ELEM_TYPE
#      ifdef _NUMBER
#        define _EQ(X,Y) X == Y
#        define _NE(X,Y) X /= Y
#      else
#        define _EQ(X,Y) X .eqv. Y
#        define _NE(X,Y) X .neqv. Y
#      endif
#    endif
#  endif
#  define _LABEL _CAT3(_TYPE_LABEL,_KIND_LABEL,_DIM_LABEL)
#  undef _DIFF
#  ifndef _KEEP_ARGS
#    undef _ID
#    undef _DIM
#  endif
#else
#  error Two arguments `_ID1` and `_ID2` or one argument `_ID` required
#endif
