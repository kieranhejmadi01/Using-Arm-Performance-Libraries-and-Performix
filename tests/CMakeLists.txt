add_executable(${SWEEP_TEST_EXECUTABLE} "sweep-test.cpp")
add_executable(${GENERATE_VISUALIZATION_EXECUTABLE} "generate_visualization.cpp")

target_link_libraries(${SWEEP_TEST_EXECUTABLE}
        PUBLIC
            ${CORE_LIBRARY}        
)
target_link_libraries(${SWEEP_TEST_EXECUTABLE}
        PUBLIC
            ${CORE_LIBRARY}        
)

