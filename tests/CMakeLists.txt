find_package(GTest REQUIRED)

if(NOT GTEST_LIBRARY)
   message("not found")
endif()

set(DSA_TESTS
    arrays_tests.cpp
    binary-heap_tests.cpp
    binary-search-tree_tests.cpp
    bit-magic_tests.cpp
    graph_tests.cpp
    greedy_tests.cpp
    mathematical_tests.cpp
    strings_tests.cpp
    tree_tests.cpp
    dp_tests.cpp
)

add_executable(dsa-tests run-tests.cpp)
target_sources(dsa-tests PRIVATE ${DSA_TESTS})
target_include_directories(dsa-tests PRIVATE ${GTEST_INCLUDE_DIRS})
target_link_libraries(dsa-tests dsa ${GTEST_LIBRARIES} ${GTEST_MAIN_LIBRARIES})
