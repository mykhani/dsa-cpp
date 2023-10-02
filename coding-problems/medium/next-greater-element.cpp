#include <vector>
#include <stack>
#include <gtest/gtest.h>

using namespace std;

/*

Given an array arr[] of size N having elements, the task
is to find the next greater element for each element of the array
in order of their appearance in the array.

Next greater element of an element in the array is the nearest element
on the right which is greater than the current element.

If there does not exist next greater of current element, than next
greater element for current element is -1. For example, next greater
if the last element is always -1.

Example: N = 4, arr[] = [1, 3, 2, 4]
Output:
3 4 4 -1

*/

vector<int> NextGreaterElement(const vector<int> &arr)
{
    vector<int> greater(arr.size(), -1);
    int N = arr.size();
    greater[N - 1] = -1;
    stack<int> s;
    s.push(arr[N - 1]);

    // start from second to last element
    for (int i = arr.size() - 2; i >= 0; i--)
    {
        // greater equal to the next greater element
        // skip if next element from stack is not greater
        while (!s.empty() && s.top() <= arr[i])
        {
            s.pop();
        }

        greater[i] = !s.empty() ? s.top() : -1;
        s.push(arr[i]);
    }

    return greater;
}

TEST(NextGreaterElement, TestCase1)
{
    vector<int> arr{1, 3, 2, 4};
    vector<int> result = NextGreaterElement(arr);
    vector<int> expected{3, 4, 4, -1};
    EXPECT_EQ(result, expected);

    arr = {4, 5, 2, 25};
    result = NextGreaterElement(arr);
    expected = {5, 25, 25, -1};
    EXPECT_EQ(result, expected);
}