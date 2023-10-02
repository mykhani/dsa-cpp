#ifndef BINARY_INDEX_TREE_H
#define BINARY_INDEX_TREE_H

#include <vector>

/*
  BinaryIndexTree is bit similar to binary segment tree.
  It is suitable if you have a fixed-size array and frequent operations on it like:
  1. PrefixSum i.e. operation on a certain number of elements from index 0 to n.
     Note that it is bit different from range based query between two end point
     indices like startIdx and endIdx.
  2. Updating the value of array element.

         arr ={1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13}
         tree={-, 1, 3, 3, 10, 5, 11, 7, 36, 9, 19, 11, 42, 13} "-" represents dummy node
  sumoffirstN     1, 2, 3, 4,  5,  6, 7,  8, 9, 10, 11, 12, 13

  Note that sums are computed in groups of sizes power of 2 i.e. 1, 2, 4, 8
  The index of tree i represents the number of elements in prefix sum e.g.
  tree[1] contains first element of arr
  tree[2] contains sum of first 2 elements of arr
  tree[4] contains sum of first 4 elements of arr
  tree[8] contains sum of first 8 elements of arr
  Now coming to i which is not a power of 3 i.e. 3, 5, 6, 7, 9, 10, 11, 12, 13,
  somehow we should be able to reuse the computed sums for i 1, 2, 4, 8. Therefore
  tree[3] = arr[2] (which is added to tree[2] before returning result or tree[2] is
            the parent of tree[3])
  tree[5] = arr[4] (with parent tree[4])
  tree[6] = arr[4] + arr[5] (with parent tree[4])
  tree[7] = arr[6] (parent tree[6])
  tree[9] = arr[8] (parent tree[8])
  tree[10] = arr[8] + arr[9] (parent tree[8])
  tree[11] = arr[10] (parent tree[10])
  tree[12] = arr[8] + arr[9] + arr[10] + arr[11] (parent tree[8])
  tree[13] = arr[12] (parent tree[12])

  The tree would look like

             ---- root-------
            /   /   \         \
          1    3    10         36
             /     /  \       /  \    \
            3     5    11    9    19   42
                        \          \    \
                         7          11   13


  */

class BinaryIndexTree
{
private:
    std::vector<int> tree;
    std::vector<int> arr;

public:
    BinaryIndexTree(const std::vector<int> &input);
    int GetSum(int i); // Get sum of first i elements of arr
    int Parent(int i);
    void Update(int index, int val);
};

#endif