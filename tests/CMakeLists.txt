file(GLOB_RECURSE sources "unittest/*.f90" "unittest/*.F90")
add_library(unittest ${sources})

file(GLOB sources "*.f90" "*.F90")
foreach(source ${sources})
    get_filename_component(label "${source}" NAME_WE)
    add_executable("${label}" "${source}")
    target_link_libraries("${label}" PRIVATE autodiff unittest)
    target_include_directories(
        "${label}" PRIVATE "${PROJECT_BINARY_DIR}/include"
    )
    add_test(NAME "${label}" COMMAND "${label}")
endforeach()
