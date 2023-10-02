#include "binary-index-tree.h"

using namespace std;

// to return parent of i (next smaller power of 2)
// e.g. 2 for i=3, 4 for i=5,6 and 6 for i=7, 8 for i=9,10,12, 10 for 11, 12 for i=13
// simply unset the last set bit
int BinaryIndexTree::Parent(int i)
{
    // if i=1010, -i=0110 (flip bits and add 1)
    //   1010
    // & 0110
    // = 0010 (2)
    // so 10-2=8 i.e. 8 is the parent of 2
    // while taking 2's complement, we flip bits so all bits
    // after the first set bit become 1's. E.g.
    //          flip
    // xxx1000000 ------> xxx0111111
    // when we add 1 to xxx0111111, we have xxx1000000
    // if xxx were 111 in i, -i now has 0001000000
    // if xxx were 000 in i, -i now has 1111000000
    // hence i & -i gives the location first set bit i.e. 0001000000
    return i - (i & -i);
}

void BinaryIndexTree::Update(int i, int val)
{
    // if index is 0, the tree indices to be updated are 1, 2, 4, 8, ...
    // if index 2 (3rd element), to tree indices to be updated are 3, 4, 8,..
    // if index 3, the tree indices to be updated are 4, 8
    // if index 4, the indices to be updated are 5, 6, 8
    // so for index i, tree[i + 1] needs to be updated for sure.
    // There is a pattern between
    // for 2, the indices that needs to be updated in binary representation
    // are 0x0011, 0x0100, 0x1000
    // for 3, the indices are 0x0100, 0x1000
    // for 4, these are 0x0101, 0x0110, 0x1000
    // so the next index to be updated can be found by adding 1 to the
    // last set bit position of the previous index i.e.
    // i = i + (i & -i);
    // we keep finding next index till it remains withing size of the tree array
    int difference = val - arr[i];

    arr[i] = val;

    i = i + 1;
    while (i <= tree.size())
    {
        tree[i] += difference;
        i = i + (i & -i);
    }
}

BinaryIndexTree::BinaryIndexTree(const std::vector<int> &input)
    : arr(input.size(), 0), tree(input.size() + 1, 0)
{
    for (int i = 0; i < arr.size(); i++)
    {
        Update(i, input[i]);
    }
}

int BinaryIndexTree::GetSum(int i)
{
    i = i + 1; // add 1 as we have added one extra dummy node in tree
               // so that tree[2] represents sum of first 2 elements
    int sum = 0;

    while (i > 0)
    {
        sum += tree[i];
        i = Parent(i);
    }

    return sum;
}
