# Automatic Differentiation Library in Fortran

This Fortran library provides **multi-dimensional automatic differentiation**
up to second order.  It can compute **gradients**, **Hessians**, and
**Laplacians** (the trace of the Hessian).  The library supports all intrinsic
signed numeric types with all available kinds, which are automatically detected
at configuration time via CMake.  It provides derived types and defines
corresponding interfaces for intrinsic operators and procedures.  Interfaces
for binary operators include all possible combinations of derived types and
intrinsic types.


## Requirements

- Fortran 2008-compliant compiler
- CMake 3.3.2 or higher


## Installation

1. Configure, build, and install:
   ```sh
   cmake -B build \
         [-DCMAKE_INSTALL_PREFIX=<install-path>] \
         [-DBUILD_SHARED_LIBS=on] \
         [-DBUILD_TESTING=on] \
         [-DEXCLUDED_KINDS=<excluded-kinds>]

   cmake --build build
   cmake --install build
   ```
   - `<excluded-kinds>` is a semicolon-separated list of kinds to exclude
   (default: `K1;K2;K8;K16;HP;XDP;QP`).  Used kind labels are described in the
   documentation.  Excluding kinds reduces compilation time.

2. Optionally test the build:
   ```sh
   ctest --test-dir build/test
   ```
   - Can be run only if testing was enabled during configuration
   (`-DBUILD_TESTING=on`).


## Usage

1. Compile your source files using the library:
   ```sh
   <compiler> -I<install-path>/include \
              <source-file> [<another-source-file>...] \
              -L<install-path>/lib -lautodiff \
              -o <executable>
   ```

2. Run the executable:
   ```sh
   [LD_LIBRARY_PATH=$LD_LIBRARY_PATH:<install-path>/lib] ./<executable>
   ```
   - The `LD_LIBRARY_PATH` adjustment is required only if the library was built
   as a shared library (`-DBUILD_SHARED_LIBS=on`).
