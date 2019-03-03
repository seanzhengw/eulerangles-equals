find_package(Threads REQUIRED)
find_package(GTest REQUIRED)

include(GoogleTest)

function(add_test TEST_NAME)
    add_executable(${TEST_NAME} ${ARGN})
    target_include_directories(${TEST_NAME}
        PRIVATE ${GTEST_INCLUDE_DIRS}
    )
    target_link_directories(${TEST_NAME} PRIVATE ${GTEST_LIBRARY_DIRS})
    target_link_libraries(${TEST_NAME}
        PRIVATE ${GTEST_BOTH_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT}
    )
    gtest_discover_tests(${TEST_NAME})
endfunction(add_test)

add_subdirectory(euler)
add_subdirectory(quat)
add_subdirectory(unite)
add_subdirectory(euler_simplify)
