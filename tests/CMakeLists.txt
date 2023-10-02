find_package(GTest REQUIRED)

if(NOT GTEST_LIBRARY)
    message("not found")
endif()

set(DSA_TESTS
    arrays_tests.cpp
    backtracking_tests.cpp
    binary-heap_tests.cpp
    binary-index-tree_tests.cpp
    binary-search-tree_tests.cpp
    binary-segment-tree_tests.cpp
    bit-magic_tests.cpp
    disjoint-set_tests.cpp
    dp_tests.cpp
    graph_tests.cpp
    greedy_tests.cpp
    mathematical_tests.cpp
    recursion_tests.cpp
    sorting_tests.cpp
    strings_tests.cpp
    tree_tests.cpp
    trie_tests.cpp
)

add_executable(dsa-tests run-tests.cpp)
target_sources(dsa-tests PRIVATE ${DSA_TESTS})
target_include_directories(dsa-tests PRIVATE ${GTEST_INCLUDE_DIRS})
target_link_libraries(dsa-tests dsa ${GTEST_LIBRARIES} ${GTEST_MAIN_LIBRARIES})
