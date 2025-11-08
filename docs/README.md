# Documentation

## Importing the Module

It is recommended to import the whole module to include all interfaces:
```fortran
use autodiff
```


## Naming Scheme for Derived Types

The naming scheme for derived types consists of three parts
(`<derivative><type><kind>`):
- `<derivative>` indicates the type of the highest derivative:
  - `Grad` - gradient
  - `Gradgrad` - Hessian (gradient of gradient)
  - `Divgrad` - Laplacian (divergence of gradient)
- `<type>` indicates the numeric type:
  - `I` - `integer`
  - `R` - `real`
  - `C` - `complex`
- `<kind>` encodes the kind parameter:
  - for `integer`:
    - `K1` - 1 byte
    - `K2` - 2 bytes
    - `K4` - 4 bytes
    - `K8` - 8 bytes
    - `K16` - 16 bytes
  - for `real` and `complex`:
    - `HP` - half precision
    - `SP` - single precision
    - `DP` - double precision
    - `XDP` - extended double precision
    - `QP` - quadruple precision


## Constructors

The constructors for the derived types are
- `Grad<type><kind>(val, grad)`
- `Gradgrad<type><kind>(val, grad, gradgrad, upper)`
- `Divgrad<type><kind>(val, grad, divgrad)`
with the following arguments:
- `val` - value as a scalar
- `grad` - gradient as a rank-1 array
- `gradgrad` - Hessian as a rank-2 array
- `divgrad` - Laplacian as a scalar
- `upper` - `logical` scalar indicating whether the upper triangular part of
Hessian should be stored

The dimensionality is determined from the size of the `grad` argument.  Extra
entries of the `gradgrad` argument are truncated and missing entries are
filled with zeros.


## Getters

The components of the derived types can be accessed via the following
type-bound functions:
- `%val()` - value
- `%grad()` - gradient
- `%gradgrad()` - Hessian
- `%divgrad()` - Laplacian (also works for `Gradgrad` types)


## Assignment, Comparison, and Arithmetic Operators

The following operators are overloaded for the derived types and intrinsic
signed numeric types:
- `=` - assignment
- `==` - equality
- `/=` - inequality
- `+` - identity, addition
- `-` - negation, subtraction
- `*` - multiplication
- `/` - division
- `**` - exponentiation

In the case of assignment of a source type to a different target type, the
components are converted to the target numeric type and kind, extra components
are truncated and missing components are filled with zeros.  Assignment of a
`Gradgrad` type to a `Divgrad` type calculates the Laplacian from the Hessian.

Two derived types are considered equal if they have the same derivative type
and all their components are equal.

In the case of binary arithmetic operations with different types, the lower
derivative type is converted to the higher one, and lower numeric type and kind
are converted to the higher ones.  The result of division and exponentiation
of integer types is obtained by converting them to the real type with the
default kind, performing the operation, and then converting the result back to
the target integer type.


## Changing Dimensionality

The dimensionality of a derived type can be changed by applying the
concatenation operator `//` with an integer, which specifies the change of
dimensionality.  Positive integers increase dimensionality, while negative
integers decrease it.  New entries are filled with zeros.  Applying
concatenation from the left changes first entries, while applying it from the
right changes last entries.  The dimensionality cannot become negative as a
result of this operation.


## Implemented Intrinsics

The following intrinsics are implemented:
- inquiry functions:
  - `kind`
- conversion functions:
  - `int`
  - `real`
  - `cmplx`
- functions for complex numbers:
  - `real`
  - `aimag`
  - `conjg`
- basic functions:
  - `sign`
  - `abs`
  - `sqrt`
  - `hypot`
  - `exp`
  - `log`
  - `log10`
- error functions:
  - `erf`
  - `erfc`
  - `erfc_scaled`
- trigonometric functions:
  - `sin`
  - `cos`
  - `tan`
  - `asin`
  - `acos`
  - `atan`
  - `atan2`
- hyperbolic functions:
  - `sinh`
  - `cosh`
  - `tanh`
  - `asinh`
  - `acosh`
  - `atanh`

The dummy variable names of the overloaded variants of the intrinsic procedures
match the built-in ones.

It is impossible to create procedures in Fortran that accept scalar integer
constant expressions as arguments or return them.  This limitation is the
reason for the following restrictions:
- The result of the inquiry function `kind` with a derived type as its argument
is not an integer constant.
- The `kind` argument of the conversion functions with a derived type as their
first argument accepts a scalar of the target numeric type and kind instead of
an integer constant.
- The `cmplx` function with derived types as its first two arguments (`x`, `y`)
requires both arguments to be of the same derivative type and the same numeric
type and kind.


## Validity Check

For performance reasons, no validity checks are performed on the arguments of
procedures and operands of operators.  It is the user's responsibility to
ensure that the arguments and operands are valid.  Some argument values may
lead to undefined behavior, such as applying the `abs` function to a derived
type with a zero value.


## Not Implemented Intrinsics

The following intrinsics are **not** implemented:
- Fortran 2008 intrinsics:
  - rounding functions:
    - `aint`
    - `anint`
    - `nint`
    - `ceiling`
    - `floor`
  - conversion functions:
    - `dble`
  - Bessel functions:
    - `bessel_j0`
    - `bessel_j1`
    - `bessel_jn`
    - `bessel_y0`
    - `bessel_y1`
    - `bessel_yn`
  - Gamma functions:
    - `gamma`
    - `log_gamma`
  - Other functions:
    - `dim`
    - `mod`
    - `modulo`
- Fortran 2023 intrinsics:
  - `unsigned` data type
  - conversion functions:
    - `uint`
  - trigonometric functions with degrees:
    - `sind`
    - `cosd`
    - `tand`
    - `asind`
    - `acosd`
    - `atand`
    - `atan2d`
  - circular trigonometric functions:
    - `sinpi`
    - `cospi`
    - `tanpi`
    - `asinpi`
    - `acospi`
    - `atanpi`
    - `atan2pi`
