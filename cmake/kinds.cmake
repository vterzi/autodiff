try_run(run_result compile_result
    "${PROJECT_BINARY_DIR}"
    "${CMAKE_SOURCE_DIR}/cmake/kinds.f90"
    RUN_OUTPUT_VARIABLE output
)

if("${run_result}" EQUAL 0)
    set(compile_definitions "")
    set(max_kind "0")
    string(REGEX MATCHALL "[A-Z0-9]+ *= *[0-9]+" list "${output}")
    foreach(item IN LISTS list)
        string(REGEX MATCH "[A-Z0-9]+" match "${item}")
        if("${match}" IN_LIST EXCL)
            continue()
        endif()
        string(REPLACE " " "" item "${item}")
        set(definition "_${item}")
        add_compile_definitions("${definition}")
        set(compile_definitions "${compile_definitions} -D${definition}")
        string(REGEX MATCH "=([0-9]+)" match "${item}")
        if("${CMAKE_MATCH_1}" GREATER "${max_kind}")
            set(max_kind "${CMAKE_MATCH_1}")
        endif()
    endforeach()
    set(kind_bits 0)
    while(TRUE)
        math(EXPR temp "1 << ${kind_bits}")
        if("${temp}" GREATER "${max_kind}")
            break()
        endif()
        math(EXPR kind_bits "${kind_bits} + 1")
    endwhile()
    add_compile_definitions("_KIND_BITS=${kind_bits}")
else()
    message(FATAL_ERROR
        "Failed to determine available kinds of basic data types"
    )
endif()
