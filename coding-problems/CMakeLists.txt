find_package(GTest REQUIRED)

if(NOT GTEST_LIBRARY)
    message("not found")
endif()

set(PROBLEMS
    easy/area-intersection-rectangles.cpp
    easy/valid-parentheses.cpp
    medium/add-subtract-currying.cpp
    medium/intersecting-line-segments.cpp
    medium/lazy-bartender.cpp
    medium/longest-palindrome-subsequence.cpp
    medium/longest-palindrome-substring.cpp
    medium/max-profit-weights.cpp
    medium/next-greater-element.cpp
    medium/next-permutation.cpp
    medium/nth-perfect-number.cpp
    medium/pascals-triangle.cpp
    medium/point-inside-polygon.cpp
    medium/print-matrix-diagonally.cpp
    medium/subsets-with-equal-sum.cpp
    medium/swap-even-odd-bits.cpp
    hard/page-rank.cpp
    hard/submatrix.cpp
    main.cpp
)

add_executable(coding-problems ${PROBLEMS})
target_link_libraries(coding-problems dsa ${GTEST_LIBRARIES} ${GTEST_MAIN_LIBRARIES})
