# Contributing

## Style Guide

This library (mostly) follows the PEP8 style guide, and the code is formatted
in a similar manner as the Black formatter would do it.  The C preprocessor
is used for code generation instead of Fypp to avoid an additional dependency.
Hence, the docstrings are omitted in the source code.


## Naming Conventions

The following acronyms are used in this library:
| Acronym          | Meaning                                                  |
|------------------|----------------------------------------------------------|
| `add`            | addition                                                 |
| `arg`            | argument                                                 |
| `autodiff`       | automatic differentiation                                |
| `cat`            | concatenate, concatenation                               |
| `conv`           | convert, conversion                                      |
| `curr`           | current                                                  |
| `decl`           | declaration                                              |
| `deriv`          | derivative                                               |
| `dg`, `divgrad`  | divergence of gradient                                   |
| `div`            | division                                                 |
| `elem`           | element                                                  |
| `eq`             | equal                                                    |
| `expr`           | expression                                               |
| `f`              | factor                                                   |
| `g`, `grad`      | gradient                                                 |
| `gg`, `gradgrad` | gradient of gradient                                     |
| `i`, `j`         | index                                                    |
| `id`             | identifier                                               |
| `iface`          | interface                                                |
| `inc`            | include                                                  |
| `init`           | initialize, initialization                               |
| `lo`             | lower bound                                              |
| `mul`            | multiplication                                           |
| `n`, `m`         | number                                                   |
| `ne`             | not equal                                                |
| `neg`            | negative                                                 |
| `op`             | operation, operator                                      |
| `pos`            | positive                                                 |
| `pow`            | power                                                    |
| `prev`           | previous                                                 |
| `proc`           | procedure                                                |
| `r`              | result                                                   |
| `sub`            | subtraction                                              |
| `t`, `temp`      | temporary                                                |
| `up`             | upper bound                                              |
| `v`, `val`       | value                                                    |

The acronyms used for numeric types and kinds are explained in the
documentation.

The dummy variable names (e.g. `x`, `y`, `z`, and `a`) of the overloaded
intrinsic procedures match the standard.


## Storage of Symmetric Matrices

Symmetric matrices (e.g. Hessian) are stored in this library as vectors
containing the upper triangular part of the matrix in column-major order.


## Derivation of Formulas

The formulas in this library can be derived using SymPy as follows:
```python
from sympy import *
try:
    from IPython.display import display
except ImportError:
    def display(x): print(x)

a, b = symbols('a, b')
x = Function('x')(a, b)
y = Function('y')(a, b)
repl = {
    Derivative(x, a, b): Symbol(r'\nabla{\nabla^\top{x}}'),
    Derivative(x, b): Symbol(r'\nabla^\top{x}'),
    Derivative(x, a): Symbol(r'\nabla{x}'),
    x: Symbol('x'),
    Derivative(y, a, b): Symbol(r'\nabla{\nabla^\top{y}}'),
    Derivative(y, b): Symbol(r'\nabla^\top{y}'),
    Derivative(y, a): Symbol(r'\nabla{y}'),
    y: Symbol('y'),
}
r = x + y  # example expression
display(r.simplify().subs(repl))
display(r.diff(a).simplify().subs(repl))
display(r.diff(a, b).simplify().subs(repl))
```
This code displays the given expression, its gradient and its Hessian.
$\nabla{z}$ indicates the gradient, $\nabla^\top{z}$ its transpose,
$\nabla{\nabla^\top{z}}$ the Hessian, and $\nabla^\top{\nabla{z}}$ the
Laplacian of a scalar function $z$.  The Laplacian can be obtained from the
expression for the Hessian by swapping $\nabla$ and $\nabla^\top$.
$\nabla^\top{x} \nabla{y}$ is the inner (dot) product of the gradients, while
$\nabla{x} \nabla^\top{y}$ is their outer product.
