#include <gtest/gtest.h>
#include <stack>
/*
Given a string s containing just the characters '(', ')', '{', '}', '[' and ']',
determine if the input string is valid.

An input string is valid if :

Open brackets must be closed by the same type of brackets.
Open brackets must be closed in the correct order.
Every close bracket has a corresponding open bracket of the same type.

Example 1 :
Input : s = "()"
Output : true

Example 2 :
Input : s = "()[]{}"
Output : true

Example 3 :
Input : s = "(]"
Output : false

Constraints :
1 <= s.length <= 104
s consists of parentheses only '()[]{}'.

*/

using namespace std;

// O(len(s))
bool ValidParentheses(string str)
{
    stack<char> s;

    for (const auto &c : str)
    {
        if (c == '(' || c == '{' || c == '[')
        {
            s.push(c);
        }
        else
        {
            // closing bracket
            if (s.empty() ||
                (c == ')' && s.top() != '(') ||
                (c == '}' && s.top() != '{') ||
                (c == ']' && s.top() != '['))
            {
                return false;
            }
            s.pop();
        }
    }
    return s.empty();
}

TEST(ValidParentheses, TestCase1)
{
    string s{"()"};
    EXPECT_EQ(ValidParentheses(s), true);

    s = "]";

    EXPECT_EQ(ValidParentheses(s), false);
}