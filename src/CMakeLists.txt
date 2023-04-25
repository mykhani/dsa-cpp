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
)

set(DSA_HEADERS 
    arrays/arrays.h
    backtracking/backtracking.h
    binary-heap/binary-heap.h
    binary-search-tree/binary-search-tree.h
    bit-magic/bit-magic.h
    graph/graph.h
    greedy/greedy.h
    hashing/hashing.h
    mathematical/mathematical.h
    matrix/matrix.h
    recursion/recursion.h
    searching/searching.h
    sorting/sorting.h
    strings/strings.h
    tree/tree.h
    dp/dp.h
)

# add_executable(dsa main.cpp)
add_library(dsa SHARED ${DSA_SOURCES})
target_include_directories(dsa PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_sources(dsa PRIVATE ${DSA_SOURCES} ${DSA_HEADERS})