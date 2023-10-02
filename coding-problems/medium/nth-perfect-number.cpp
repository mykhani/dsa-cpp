#include <gtest/gtest.h>
#include <unordered_map>
#include <utility>

using namespace std;
/*
A number is considered perfect if its digits sum up to exactly 10.

Given a positive integer n,
return the n - th perfect number.

For example,
given 1, you should return 19. Given 2, you should return 28.

List (Arithematic progression) of perfect numbers is given below
with some outliers highlighted in angle brackets:

    19,    28,    37,    46,  55,  64,  73,  82,  91, <100>,
   109,   118,   127,   136, 145, 154, 163, 172, 181,   190,
 <199>,   208,   217,   226, 235, 244, 253, 262, 271,   280,
 <289>, <298>,   307,   316, 325, 334, 343, 352, 361,   370,
 <379>, <388>, <397>,   406, 415, 424, 433, 442, 451,   460,
 <469>, <478>, <487>, <496>, 505, 514, 523, 532, 541,   550,

Due to these outliers, the below formula won't work
nth number = 19 + 9*(n-1);
if n = 10, number = 19 + 81 = 100, should be 109
if n = 20; number = 19 + 171 = 190, should be 208
*/

// O(log10n) or O(logn)
bool IsPerfectNumber(int n)
{
    int sum = 0;
    while (n)
    {
        int digit = n % 10;
        n /= 10;
        sum += digit;
        if (sum > 10)
        {
            return false;
        }
    }
    return sum == 10;
}

// Brute force, // O(nlogn)
int NthPerfectNumberBrute(int n)
{
    int candidate = 19;
    int count = 0;

    // O(n)
    while (count != n)
    {
        if (IsPerfectNumber(candidate)) // O(logn)
        {
            count++;
        }
        if (count == n)
        {
            break;
        }
        candidate += 9;
    }

    return candidate;
}

struct pair_hash
{
    template <class T1, class T2>
    std::size_t operator()(const std::pair<T1, T2> &pair) const
    {
        return std::hash<T1>()(pair.first) ^ std::hash<T2>()(pair.second);
    }
};

// maintain a count of numbers with a certain digit sum "s" with length "l"
// e.g. 9 2-digit numbers has sum 10
//              <length, sum>
unordered_map<pair<int, int>, int, pair_hash> countOfNumbersWithLengthAndSum;

/* Dynamic Programming

CountOfNumbersWithLengthAndSum(3, 10) = 63
 \- CountOfNumbersWithLengthAndSum(2, 10) =  9  0xx -> 019 028 037 046 055 064 073 082 091
    \- CountOfNumbersWithLengthAndSum(1, 10) = 0 00x -> not possible (handled by condition B in CountOfNumbersWithLengthAndSum function)
    \- CountOfNumbersWithLengthAndSum(1, 9) = 1  01x -> 019
    \- CountOfNumbersWithLengthAndSum(1, 8) = 1  02x -> 028
    \- CountOfNumbersWithLengthAndSum(1, 7) = 1  03x -> 037
    \- CountOfNumbersWithLengthAndSum(1, 6) = 1  04x -> 046
    \- CountOfNumbersWithLengthAndSum(1, 5) = 1  05x -> 055
    \- CountOfNumbersWithLengthAndSum(1, 4) = 1  06x -> 064
    \- CountOfNumbersWithLengthAndSum(1, 3) = 1  07x -> 073
    \- CountOfNumbersWithLengthAndSum(1, 2) = 1  08x -> 082
    \- CountOfNumbersWithLengthAndSum(1, 1) = 1  09x -> 091
 \- CountOfNumbersWithLengthAndSum(2, 9)  = 10  1xx -> 109 118 127 136 145 154 163 172 181 190
    \- CountOfNumbersWithLengthAndSum(1, 9) = 1  10x -> 109
    \- CountOfNumbersWithLengthAndSum(1, 8) = 1  11x -> 118
    \- CountOfNumbersWithLengthAndSum(1, 7) = 1  12x -> 127
    \- CountOfNumbersWithLengthAndSum(1, 6) = 1  13x -> 136
    \- CountOfNumbersWithLengthAndSum(1, 5) = 1  14x -> 145
    \- CountOfNumbersWithLengthAndSum(1, 4) = 1  15x -> 154
    \- CountOfNumbersWithLengthAndSum(1, 3) = 1  16x -> 163
    \- CountOfNumbersWithLengthAndSum(1, 2) = 1  17x -> 172
    \- CountOfNumbersWithLengthAndSum(1, 1) = 1  18x -> 181
    \- CountOfNumbersWithLengthAndSum(1, 0) = 1  19x -> 190
 \- CountOfNumbersWithLengthAndSum(2, 8)  =  9  2xx -> 208 217 226 235 244 253 262 271 280
    ...
 \- CountOfNumbersWithLengthAndSum(2, 7)  =  8  3xx -> 307 316 325 334 343 352 361 370
    ...
 \- CountOfNumbersWithLengthAndSum(2, 6)  =  7  4xx -> 406 415 424 433 442 451 460
    ...
 \- CountOfNumbersWithLengthAndSum(2, 5)  =  6  5xx -> 505 514 523 532 541 550
    ...
 \- CountOfNumbersWithLengthAndSum(2, 4)  =  5  6xx -> 604 613 622 631 640
    ...
 \- CountOfNumbersWithLengthAndSum(2, 3)  =  4  7xx -> 703 712 721 730
    ...
 \- CountOfNumbersWithLengthAndSum(2, 2)  =  3  8xx -> 802 811 820
    ...
 \- CountOfNumbersWithLengthAndSum(2, 1)  =  2  9xx -> 901 910
    \- CountOfNumbersWithLengthAndSum(1, 1) = 1  90x -> 901
    \- CountOfNumbersWithLengthAndSum(1, 1) = 1  91x -> 910


Now lets say we have to find 24th term, we need to find the number of digits
that the 24th term will have.

CountOfNumbersWithLengthAndSum(1, 10); 0
CountOfNumbersWithLengthAndSum(2, 10); 9 (24 - 9 = 15 items to go)
CountOfNumbersWithLengthAndSum(3, 10); 63 (this range contains the 24th item)

If we had to find 64th element, the number of digits required would be 4.

Now we know the number of digits, e.g. 3 in the case of 24th term.
To find the actual number, we iterate on different permutations of a 3-digit
number and count their number i.e.

Count of 3 digits number starting with 0 i.e. 0xx
 \- CountOfNumbersWithLengthAndSum(2, 10) = 9
so 24th iterm is not covered by numbers starting with 0)

With 24-9=15 items to go, search for the next permutation i.e.

Count of 3 digit number starting with 1 i.e. 1xx
 \- CountOfNumbersWithLengthAndSum(2, 9) = 10
We have covered 19 terms so far and still haven't reached the 24th term. Go on

Count of 3 digit number starting with 2 i.e. 2xx
 \- CountOfNumbersWithLengthAndSum(2, 8) = 9
This range covers 9 terms from term 20 to 28. So the 24th term lies within this range.

Now we know the first digit of the 3-digit number is supposed to be 2. The remaining sum is 10-2=8
Also we have marked off 19 items from 0xx to 1xx and are at range starting with
2xx.

Now we need to find a 2-digit number which has sum 8.

Count of 2 digits number starting with 0 i.e. 0x with sum 8
 \- CountOfNumbersWithLengthAndSum(1, 8) = 1
We marked off one item and total marked off items become 20.

Count of 2 digits number starting with 1 i.e. 1x with sum 8
 \- CountOfNumbersWithLengthAndSum(1, 7) = 1 (marked off 21)

 Count of 2 digits number starting with 2 i.e. 2x with sum 8
 \- CountOfNumbersWithLengthAndSum(1, 6) = 1 (marked off 22)

 Count of 2 digits number starting with 3 i.e. 3x with sum 8
 \- CountOfNumbersWithLengthAndSum(1, 5) = 1 (marked off 23)

 Count of 2 digits number starting with 4 i.e. 4x with sum 8
 \- CountOfNumbersWithLengthAndSum(1, 4) = 1 (marked off 24)

*/

// l and s are more like length and sum remaining
int CountOfNumbersWithLengthAndSum(int l, int s)
{
    pair<int, int> key{l, s};

    if (countOfNumbersWithLengthAndSum.find(key) == countOfNumbersWithLengthAndSum.end())
    {
        if (l < 2) // one or no digit
        {
            if (s == 0) // ----- A
            {
                // return 1;
                countOfNumbersWithLengthAndSum[key] = 1;
            }
            else if (l == 1 && s < 10) //------ B
            {
                // return 1;
                countOfNumbersWithLengthAndSum[key] = 1;
            }
            else
            {
                // return 0;
                countOfNumbersWithLengthAndSum[key] = 0;
            }
        }
        else
        {
            // for two or more-digits, iterate on permutation of digits between 0 to 9
            int count = 0;
            // for (int i = 0; i < 10; i++)
            for (int i = 0; i < std::min(10, s + 1); i++)
            {
                int l_remaining = l - 1;
                int sum_remaining = s - i; // it can become negative if s < i
                                           //  an optimization is to run loop from 0 < i <= s;
                                           //  for example of l=2 and s=4, digits can be 04 or 40

                count += CountOfNumbersWithLengthAndSum(l_remaining, sum_remaining);
            }
            countOfNumbersWithLengthAndSum[key] = count;
        }
    }

    // cout << "Count for length " << l << " and sum " << s << " is " << countOfNumbersWithLengthAndSum[key] << endl;
    return countOfNumbersWithLengthAndSum[key];
}
// DynamicProgramming,
// Taken from:
// https://stackoverflow.com/questions/61561991/919b-nth-numbers-having-digit-sum-as-10-codeforces
int NthPerfectNumberDP(int n, int sum)
{
    int l = 0; // length of numbers

    // let see in which range does n lies
    while (CountOfNumbersWithLengthAndSum(l, 10) < n)
    {
        l++;
    }

    int number = 0;
    int digit = 0;
    int marked_off = 0;
    int s = sum;

    // now we know it must be a number with length l
    while (l > 0)
    {
        for (int i = 0; i < 10; i++)
        {
            // set the first digit and find the count for remaining permutation
            // when two-digits remain, selecting the first of two results in only
            // single permutation as the second digit can only have one value
            int count = CountOfNumbersWithLengthAndSum(l - 1, s - i);
            if (marked_off + count < n)
            {
                // the required number still exists outside the range of numbers formed
                // with the starting digit i
                marked_off += count; // mark off count terms
            }
            else //(marked_off + count >= n)
            {
                // the required number falls within the range of numbers formed
                // with the starting digit i
                digit = i;
                number = number * 10 + digit;
                l--;
                s -= i;
                break;
            }
        }
    }

    return number;
}

TEST(NthPerfectNumberBrute, TestCase1)
{
    EXPECT_EQ(NthPerfectNumberBrute(1), 19);
    EXPECT_EQ(NthPerfectNumberBrute(2), 28);
    EXPECT_EQ(NthPerfectNumberBrute(20), 208);
    EXPECT_EQ(NthPerfectNumberBrute(1000), 100036);
}

TEST(CountOfNumbersWithLengthAndSum, TestCase2)
{
    EXPECT_EQ(CountOfNumbersWithLengthAndSum(0, 0), 1); // TODO: study why l=0,s=0 return 1 is valid?
    EXPECT_EQ(CountOfNumbersWithLengthAndSum(1, 0), 1);
    EXPECT_EQ(CountOfNumbersWithLengthAndSum(1, 10), 0);
    EXPECT_EQ(CountOfNumbersWithLengthAndSum(1, 9), 1);
    EXPECT_EQ(CountOfNumbersWithLengthAndSum(2, 10), 9);
    EXPECT_EQ(CountOfNumbersWithLengthAndSum(3, 10), 63);
}

TEST(NthPerfectNumberDP, TestCase1)
{
    // EXPECT_EQ(NthPerfectNumberDP(1, 10), 19);
    // EXPECT_EQ(NthPerfectNumberDP(2, 10), 28);
    EXPECT_EQ(NthPerfectNumberDP(20, 10), 208);
    EXPECT_EQ(NthPerfectNumberDP(24, 10), 244);
    // EXPECT_EQ(NthPerfectNumberDP(70, 10), 208);
    // EXPECT_EQ(NthPerfectNumberDP(1000, 10), 100036);
}