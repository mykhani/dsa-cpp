#include <vector>
#include <iostream>
#include <unordered_map>
#include <unordered_set>

#include <gtest/gtest.h>

using namespace std;

/*
At a popular bar, each customer has a set of favorite drinks,
and will happily accept any drink among this set. For example,
in the following situation, customer 0 will be satisfied with
drinks 0, 1, 3, or 6.

preferences = {
    0 : [ 0, 1, 3, 6 ],
    1 : [ 1, 4, 7 ],
    2 : [ 2, 4, 7, 5 ],
    3 : [ 3, 2, 5 ],
    4 : [ 5, 8 ]
}
A lazy bartender working at this bar is trying to reduce his effort
by limiting the drink recipes he must memorize. Given a dictionary
input such as the one above, return the fewest number of drinks he
must learn in order to satisfy all customers.
For the input above, the answer would be 2, as drinks 1 and 5 will satisfy everyone.
*/

/*
  0 1 3 6   1 4 7     2 4 7 5     3 2 5    5 8


0  1  2  3  4  5  6  7  8
0  0     0        0
   1        1        1
      2     2  2     2
      3  3     3
               4        4
               */
vector<int> LazyBartenderMinimumDrinks(vector<vector<int>> preferences, int nCustomers, int nDrinks)
{
    vector<int> result;
    vector<vector<int>> map(nDrinks, vector<int>(nCustomers + 1, 0));

    // O(mn)
    for (int cust = 0; cust < preferences.size(); cust++)
    {
        for (int drinkIdx = 0; drinkIdx < preferences[cust].size(); drinkIdx++)
        {
            int drink = preferences[cust][drinkIdx];
            map[drink][cust] = 1;
        }
    }

    for (int drinkIdx = 0; drinkIdx < map.size(); drinkIdx++)
    {
        int sum = 0;
        for (int custIdx = 0; custIdx < map[drinkIdx].size(); custIdx++)
        {
            sum += map[drinkIdx][custIdx];
        }
        map[drinkIdx][nCustomers] = sum;
    }

    int remaining = nCustomers;

    while (remaining)
    {
        int max_index = 0;
        int max_sum = INT_MIN;
        // greedy, find the drink serving max customers
        for (int drinkIdx = 0; drinkIdx < map.size(); drinkIdx++)
        {
            int sum = map[drinkIdx][nCustomers];
            if (sum > max_sum)
            {
                max_index = drinkIdx;
                max_sum = sum;
            }
        }
        result.push_back(max_index);
        remaining -= max_sum;
        // update the map
        for (int j = 0; j < nCustomers + 1; j++)
        {
            if (map[max_index][j] == 1)
            {
                for (int i = 0; i < nDrinks; i++)
                {
                    if (map[i][j])
                    {
                        map[i][j] = 0;
                        map[i][nCustomers]--;
                    }
                }
            }
        }

        for (int drinkIdx = 0; drinkIdx < map.size(); drinkIdx++)
        {
            int sum = 0;
            for (int custIdx = 0; custIdx < nCustomers; custIdx++)
            {
                sum += map[drinkIdx][custIdx];
            }
            map[drinkIdx][nCustomers] = sum;
        }
    }

    return result;
}

TEST(LazyBartender, TestCase1)
{
    vector<vector<int>> preferences = {
        {0, 1, 3, 6},
        {1, 4, 7},
        {2, 4, 7, 5},
        {3, 2, 5},
        {5, 8}};

    vector<int> result = LazyBartenderMinimumDrinks(preferences, preferences.size(), 9);
    vector<int> expected = {5, 1};
    EXPECT_EQ(result, expected);
}