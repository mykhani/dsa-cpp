#include "backtracking.h"
#include <utility>
#include <string>

using namespace std;

// Exclude permutations including "AB"
// In permuations for "ABC", "ABC" and "CAB" must be avoided
/*   ABC
ABC   BAC CBA
ACB   BCA    CAB

*/
vector<string> PermutationsExcluding(string &s, const string &pattern)
{
    vector<string> result;

    /*
    CAB*/

    function<void(int)> permutate_at = [&](int index)
    {
        if (index == s.length() - 1)
        {
            result.push_back(s);
            return;
        }

        for (int i = index; i < s.length(); i++)
        {
            swap(s[index], s[i]);
            if (index >= pattern.length() - 1 && (s.find(pattern) != string::npos))
            {
                /* skip */
            }
            else
            {
                permutate_at(index + 1);
            }
            swap(s[index], s[i]);
        }
    };

    permutate_at(0);

    return result;

    // function<void(string &, int, int)> permutate = [&permutate, &result](string &s, int left, int right)
    // {
    //     if (left == right)
    //     {
    //         result.push_back(s);
    //         return;
    //     }

    //     auto IsSafe = [](string &s, int l, int r, int i) -> bool
    //     {
    //         if (l > 0 && s[l - 1] == 'A' && s[i] == 'B')
    //             return false;

    //         if (l + 1 == r && s[l] == 'B' && s[i] == 'A')
    //             return false;

    //         return true;
    //     };

    //     // A B C
    //     for (int i = left; i <= right; i++)
    //     {
    //         if (IsSafe(s, left, right, i))
    //         {                        // backtracking conditions, don't proceed if the result won't be valid
    //             swap(s[left], s[i]); // without backtracking, no condition
    //             permutate(s, left + 1, right);
    //             swap(s[i], s[left]); // restore the original string
    //         }
    //     }
    // };

    // permutate(s, 0, s.length() - 1);
    // BAC CBA
    // ACB BCA
    // return result;
}
