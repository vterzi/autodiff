#define _KIND_MASK ((1 << _KIND_BITS) - 1)
#define _TYPE_MASK (((1 << _TYPE_BITS) - 1) << _KIND_BITS)
#define _DIM_MASK (((1 << _DIM_BITS) - 1) << (_KIND_BITS + _TYPE_BITS))

#define _IS_TYPE(ID,TYPE) (((ID) & _TYPE_MASK) == TYPE)
#define _IS_KIND(ID,KIND) (((ID) & _KIND_MASK) == KIND)
#define _IS_DIM(ID,DIM) (((ID) & _DIM_MASK) == DIM)

#define _LOGICAL (1 << _KIND_BITS)
#define _INTEGER (2 << _KIND_BITS)
#define _REAL (3 << _KIND_BITS)
#define _COMPLEX (4 << _KIND_BITS)
#define _CHARACTER (5 << _KIND_BITS)

#define _CLASS_K _INTEGER
#define _CLASS_P _REAL
#define _CLASS_S _CHARACTER

#define _1_DIMS (1 << (_KIND_BITS + _TYPE_BITS))
#define _2_DIMS (2 << (_KIND_BITS + _TYPE_BITS))
#define _3_DIMS (3 << (_KIND_BITS + _TYPE_BITS))
#define _4_DIMS (4 << (_KIND_BITS + _TYPE_BITS))
#define _5_DIMS (5 << (_KIND_BITS + _TYPE_BITS))
#define _6_DIMS (6 << (_KIND_BITS + _TYPE_BITS))
#define _7_DIMS (7 << (_KIND_BITS + _TYPE_BITS))
