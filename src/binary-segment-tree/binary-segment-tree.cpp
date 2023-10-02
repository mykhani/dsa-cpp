#include "binary-segment-tree.h"
#include <numeric>

using namespace std;

int BinarySegmentTree::left(int i)
{
    return 2 * i + 1;
}

int BinarySegmentTree::right(int i)
{
    return 2 * i + 2;
}

int BinarySegmentTree::parent(int i)
{
    return (i - 1) / 2;
}

// Time O(n)
int BinarySegmentTree::create(int startIdx, int endIdx, int rootIdx)
{
    // left half always has equal or one more number of elements than right
    // half. For example if arr has 5 elements, there are 3 elements in left
    // and 2 elements in right half

    if (startIdx == endIdx)
    {
        return arr[startIdx];
    }

    int midIdx = (startIdx + endIdx) / 2;
    int left_sum = create(startIdx, midIdx, left(rootIdx));
    int right_sum = create(midIdx + 1, endIdx, right(rootIdx));

    tree[left(rootIdx)] = left_sum;
    tree[right(rootIdx)] = right_sum;

    return left_sum + right_sum;
}

BinarySegmentTree::BinarySegmentTree(const std::vector<int> input)
    : arr{input} // tree(4 * arr.size(), INT_MAX)
{
    int n = arr.size();
    int k = 2 * pow(2, ceil(log10(n) / log10(2))) - 1;
    tree = vector<int>(k, INT_MAX);

    tree[0] = create(0, arr.size() - 1, 0);
}

vector<int> BinarySegmentTree::Tree()
{
    return tree;
}

// Get Sum of a query range marked by qs and qe, both inclusive
int BinarySegmentTree::GetSum(int qs, int qe)
{
    // Idea: collect the sum of all the segments that lie within the query range
    /*
    qs: query start
    qe: query end
    ss: segment start
    se: segment end
    root: root representing the current segment
    */
    function<int(int, int, int, int, int)> GetSumHelper = [&](int qs, int qe, int ss, int se, int root) -> int
    {
        /*
            if query completely outside the range, return 0
                 ss       se
            qs qe           qs  qe
        */
        if (qe < ss || qs > se)
            return 0;

        /*
            if the segment lies within the query. This way, we collect all the segments
            that lie within the query
                ss       se
            qs                 qe
                qs       qe
        */
        if (qs <= ss && qe >= se)
            return tree[root];

        int mid = (ss + se) / 2;

        return GetSumHelper(qs, qe, ss, mid, left(root)) +
               GetSumHelper(qs, qe, mid + 1, se, right(root));
    };

    return GetSumHelper(qs, qe, 0, arr.size() - 1, 0);
}

void BinarySegmentTree::Update(int idx, int value)
{
    if (idx >= arr.size())
        return;

    int difference = value - arr[idx];
    arr[idx] = value;

    function<void(int, int, int, int, int)> UpdateHelper = [&](int idx, int diff, int ss, int se, int root)
    {
        // if index lies outside the segment, ignore
        /*
               ss    se
            idx         idx
        */
        if (idx < ss || idx > se)
            return;

        tree[root] += diff;

        if (ss < se)
        {
            int mid = (ss + se) / 2;

            UpdateHelper(idx, diff, ss, mid, left(root));
            UpdateHelper(idx, diff, mid + 1, se, right(root));
        }
    };

    // check if a segment needs to be updated
    UpdateHelper(idx, difference, 0, arr.size() - 1, 0);
}
