set(CMAKE_CXX_STANDARD 17)

set(DSA_SOURCES
    arrays/arrays.cpp
    backtracking/backtracking.cpp
    binary-heap/binary-heap.cpp
    binary-search-tree/binary-search-tree.cpp
    bit-magic/bit-magic.cpp
    graph/graph.cpp
    greedy/greedy.cpp
    hashing/hashing.cpp
    mathematical/mathematical.cpp
    matrix/matrix.cpp
    recursion/recursion.cpp
    searching/searching.cpp
    sorting/sorting.cpp
    strings/strings.cpp
    tree/tree.cpp
    dp/dp.cpp
    trie/trie.cpp
    disjoint-set/disjoint-set.cpp
)

# add_executable(dsa main.cpp)
add_library(dsa SHARED ${DSA_SOURCES})
target_include_directories(dsa PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_sources(dsa PRIVATE ${DSA_SOURCES})