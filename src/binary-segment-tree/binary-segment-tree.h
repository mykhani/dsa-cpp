#ifndef BINARY_SEGMENT_TREE_H
#define BINARY_SEGMENT_TREE_H

#include <vector>

/*
  Segment tree is suitable for problems where you have a fixed sized array
  and there are large number of operations on it like:
  1. Range query (find something over a range of elements e.g sum of elements from index i to k)
  2. Insert operations

  If it were only range queries, it would have suffice to do use some other preprocessing
  technique like prefix sum which would take O(n) to preprocess the array and then O(1) to
  find the sum over a range but then there are frequent insert operations as well which
  means prefix_sum array would have to be recomputed i.e. O(n)

  The idea is to create a tree-like stucture out of the array (similar to heap) using another
  array.

  The tree is created by dividing the number of elements in the array into 2
  segments, the left half of which can be bigger than the right in size. The root represents
  some computation over these two left and right segments, depending on the problem. For example,
  it could be the total sum of both left and right segments.

  We would like to represent the tree as an array similar to binary heap and use the same
  left(i), right(i) and parent(i) calculations to find the left, right and parent of a element
  at index i like:
  left(i) = 2*i + 1;
  right(i) = 2*i + 2;
  parent(i) = (i - 1)/2;

  Since the tree won't necessarily be a complete tee like a heap (all levels filled except last
  and last level filled left-to-right), we need to add extra dummy elements in the tree array so
  the size of the array representing binary segment tree would be greater than the actual array.
  To find the size of it, suppose the array contains n elements and n is the power of 2 e.g. 8,
  then the number of elements to create binary segment tree is 2n-1=15. For example below is the
  tree for array={0, 1, 2, 3, 4, 5, 6, 7} i.e. with 8 elements
          28
      6         22
   1    5    9    13
  0 1  2 3  4 5  6  7
  Represented as segment_tree_array={28, 6, 22, 1, 5, 9, 13, 0, 1, 2, 3, 4, 5, 6, 7}

  So if we have an array with size 6, we would need to add few dummy nodes to have an tree_array
  of size 15. The formula to calculate the size of segment_tree_array for array of size n
  is is 2k-1 where k is the next smallest power of 2 greater than n. For n=6, k=8 and for n=10, k=16
  To mathematically find next smallest power of 2 greater than n, the formala is
  ceil(log(base2)n) for example ceil(log(base2)6)=ceil(log(base10)6/log(base10)2) = ceil(2.58) = 3

  However, to keep it simple and to avoid calculations, it can be upper bounded by 4n. So the
  segment_tree_array can be safely assumed to be of size 4n.

  */

class BinarySegmentTree
{
private:
    std::vector<int> tree;
    std::vector<int> arr;
    int left(int i);
    int right(int i);
    int parent(int i);
    int create(int startIdx, int endIdx, int rootIdx); // O(n)

public:
    BinarySegmentTree(const std::vector<int> input);
    std::vector<int> Tree();
    int GetSum(int qs, int qe); // qs and qe for query start and end index, Time O(logn)
    void Update(int idx, int value);
};

#endif