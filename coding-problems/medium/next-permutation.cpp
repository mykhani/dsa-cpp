#include <gtest/gtest.h>

using namespace std;

/*

Given an integer, find the next permutation of it
in absolute order. For example, given 48975, the next
permutation would be 49578

Order here means lexicographical order (sorted alphabetically/numerically)

See https://stackoverflow.com/questions/1622532/algorithm-to-find-next-greater-permutation-of-a-given-string


The idea is like this:
The final permutation will be in descending order e.g.
for n=01234, the last permutation would be 43210
So if all the digits of the number are in ascending-order going
from right to left, the number is the last permutation
Another example is permutations for number 123 in lexicographical order
1, 2, 3
1, 3 ,2
2, 1, 3
2, 3, 1
3, 2, 1 -> last permutation

There is a pattern between two successive permutations, there is a pivot point.

Let say the number is represented by a string s

1. Starting from the rightmost index, find the index i where s[i] > s[i-1] or
   s[i-1] < s[i]. The index i-1 becomes the pivot point. If no such index exists,
   the permutation is the last permutation.

2. Find the highest index j > i such that s[j] > s[i]. Such a j must exist,
   since i+1 is such an index.Swap s[i] with s[j].

3. Reverse the order of all of the elements after index i till the last element.

*/

// O(n*n!)
// for string of length n
// The outer permutate is called for indices 0 to n-1 i.e n times
// For each permutate at index i, the permutate is called n! times
// See GeeksforGeeks video on permutations using recusion time complexity
// calculation
int NextOrderedPermutationBrute(int n)
{
    // convert n to string
    string s{to_string(n)};
    int result = INT_MAX;

    function<void(string &, int)> permutate = [&permutate, &result, &n](string &s, int index)
    {
        if (index == s.length() - 1)
        {
            int p = stoi(s);
            if (p > n)
            {
                result = std::min(p, result);
            }
            return;
        }
        // O(n^2)
        for (int i = index; i < s.length(); i++)
        {
            std::swap(s[index], s[i]);
            permutate(s, index + 1);
            swap(s[index], s[i]);
        }
    };

    permutate(s, 0);

    return result;
}

// O(digits) or O(n)
int NextOrderedPermutationBetter(int n)
{
    // convert n to string
    string s{to_string(n)};
    int result = INT_MAX;
    int N = s.length();

    int pivot = -1;

    // finding the pivot
    for (int i = N - 1; i > 0; i--)
    {
        if (s[i - 1] < s[i])
        {
            pivot = i - 1;
            break;
        }
    }

    if (pivot == -1)
    { // no pivot found, the n itself is the last permutation
        return n;
    }

    // now find the smallest greater element than s[pivot]
    // Note that the values from indices pivot + 1 to N left-to-right are sorted in
    // descending order (they didn't satisfy the condition s[i] > s[i - 1])
    // so to pick the smallest greater element than s[pivot], we traverse
    // from right to left and pick the first element s[i] > s[pivot]
    // one you find that element, swap it with the pivot and break
    for (int i = N - 1; i > pivot; i--)
    {
        if (s[i] > s[pivot])
        {
            swap(s[pivot], s[i]);
            break;
        }
    }

    // Let say the index i satified s[i] > s[pivot] in the above loop,
    // after swapping, the elements from s[pivot] onwards still
    // follow the descending order because,
    // we picked the s[i] which is the smallest element satisfying
    // s[i] > s[pivot]
    // and the value at s[i-1] > s[i]
    // since s[i] > s[pivot] and s[i-1] > s[i]
    // s[i-1] > s[pivot]
    // so after the swap(s[i], s[pivot])
    // the order remains valid
    // Now we just need to reverse the order from s[pivot + 1] to s[N-1]
    // to make it from descending to ascending
    std::reverse(s.begin() + pivot + 1, s.end()); // convert to ascending order

    return stoi(s);
}

TEST(NextOrderedPermutationBrute, TestCase1)
{
    EXPECT_EQ(NextOrderedPermutationBrute(48975), 49578);
}

TEST(NextOrderedPermutationBetter, TestCase1)
{
    EXPECT_EQ(NextOrderedPermutationBetter(132), 213);
    EXPECT_EQ(NextOrderedPermutationBetter(48975), 49578);
}