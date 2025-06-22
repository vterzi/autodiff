cmake_minimum_required(VERSION 3.14.0)

project(autodiff
    LANGUAGES Fortran
    VERSION 0.1.0
)

set(CMAKE_Fortran_STANDARD 2008)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/bin")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/lib")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/lib")
set(CMAKE_Fortran_MODULE_DIRECTORY "${PROJECT_BINARY_DIR}/include")

set(
    EXCL
    "K1;K2;K16;HP;XDP;QP"
    CACHE
    STRING
    "Semicolon-separated list of excluded kinds"
)
include(cmake/kinds.cmake)

add_subdirectory(src)
add_subdirectory(tests)
