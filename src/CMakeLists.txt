add_library(${CORE_LIBRARY} 
    STATIC 
        "rectangle.cpp"
        "point.cpp"
        "vec1d.cpp"
        "export_data.cpp"
)


add_executable(${MAIN_EXECUTABLE} "main.cpp")

target_link_libraries(${MAIN_EXECUTABLE} 
        PUBLIC 
            ${CORE_LIBRARY}
)

if(USE_APL)
    # Apply to library code (vec1d.cpp) and propagate to dependents
    target_compile_definitions(${CORE_LIBRARY} PUBLIC USE_ARMPL=1)

    target_include_directories(${CORE_LIBRARY}
        PUBLIC
            ${ARMPL_DIR}/include
    )

    find_library(ARMPL_LIB armpl_lp64 HINTS ${ARMPL_DIR}/lib REQUIRED)
    find_library(AMATH_LIB amath HINTS ${ARMPL_DIR}/lib REQUIRED)

    target_link_libraries(${CORE_LIBRARY}
        PRIVATE
            ${ARMPL_LIB}
            ${AMATH_LIB}
            m
    )
else()
    target_compile_definitions(${CORE_LIBRARY} PUBLIC USE_ARMPL=0)
endif()
