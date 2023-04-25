#include "dp.h"
#include <vector>

using namespace std;

vector<int> memo(100, -1);

// Fibonacci numbers using memoization
int FibonacciMemo(int n) {
    if (memo[n] != -1) {
        return memo[n];
    }

    int ret;

    if (n == 0 || n == 1) {
        ret = n;
    } else {
        ret = FibonacciMemo(n - 2) + FibonacciMemo(n - 1);
    }

    memo[n] = ret;

    return ret;
}

int FibonacciTabulation(int n) {
    vector<int> f(n+1, -1);
    f[0] = 0;
    f[1] = 1;

    for (int i = 2; i <= n; i++) {
        f[i] = f[i - 2] + f[i - 1];
    }

    return f[n];
}

int LongestCommonSubsequenceRecursive(std::string& s1,  std::string& s2, int m, int n) {
    // end condition, if either of string reaches 0 length
    if (m == 0 || n == 0)
        return 0;

    // start either from beginning or end
    // if last character match, add 1 and recursive
    if (s1[m - 1] == s2[n - 1]) {
        return 1 + LongestCommonSubsequenceRecursive(s1, s2, m - 1, n - 1);
    } else {
        // if last character doesn't match then see if second to last character matches the last of the other
        // string e.g. s1 = ABC and s2 = ABD, then check LCS("ABC", AB) and LCS("AB", "ABD");
        return std::max(LongestCommonSubsequenceRecursive(s1, s2, m - 1, n),
                        LongestCommonSubsequenceRecursive(s1, s2, m, n - 1));
    }
}

//
vector<vector<int>> lcs_memo(100, vector<int>(100, -1));

int LongestCommonSubsequenceMemo(std::string& s1,  std::string& s2, int m, int n) {

    if (lcs_memo[m][n] != -1)
        return lcs_memo[m][n];

    else {
        int result;

        // end condition, if either of string reaches 0 length
        if (m == 0 || n == 0) {
            result = 0;
        } else if (s1[m - 1] == s2[n - 1]) {
            result = 1 + LongestCommonSubsequenceRecursive(s1, s2, m - 1, n - 1);
        } else {
            // if last character doesn't match then see if second to last character matches the last of the other
            // string e.g. s1 = ABC and s2 = ABD, then check LCS("ABC", AB) and LCS("AB", "ABD");
            result = std::max(LongestCommonSubsequenceRecursive(s1, s2, m - 1, n),
                            LongestCommonSubsequenceRecursive(s1, s2, m, n - 1));
        }

        lcs_memo[m][n] = result;
        return result;
    }
}

int LongestCommonSubsequenceTabulation(std::string& s1,  std::string& s2, int m, int n) {
    vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));

    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            if (s1[i - 1] == s2[j - 1]) {
                dp[i][j] = 1 + dp[i - 1][j - 1];
            } else {
                dp[i][j] = std::max(dp[i - 1][j], dp[i][j-1]);
            }
        }
    }

    return dp[m][n];
}

int LongestPalindromicSubsequence(std::string& s) {
    // idea is to create a reversed copy of original string
    // and find LCS of original and copy
    std::string reverse(s.rbegin(), s.rend());

    return LongestCommonSubsequenceTabulation(s, reverse, s.length(), reverse.length());

}

int ShortestCommonSupersequence(std::string& s1, std::string& s2) {
    int m = s1.length();
    int n = s2.length();

    int l = LongestCommonSubsequenceTabulation(s1, s2, m, n);

    return l + (m - l) + (n - l);
}

int CoinChangeCount(std::vector<int> coins, int sum) {
    int max_count = 0;

    if (sum == 0)
        return 0;

    for (int i = 0; i < coins.size(); i++) {
        int coin_value = coins[i];

        if (coin_value <= sum) {
            int count = 1 + CoinChangeCount(coins, sum - coin_value);
            max_count = std::max(count, max_count);
        }
    }

    return max_count;
}
