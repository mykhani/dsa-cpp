/*
 * strings_tests.cpp
 *
 *  Created on: 16 Jul 2021
 *      Author: ykhan
 */

#include "../src/strings/strings.h"
#include <gtest/gtest.h>

TEST(Strings, FrequencyCharsLowercaseTest) {
	std::string s = "geeksforgeeks";
	auto result = frequencyOfCharactersLowercaseString(s);

	std::vector<std::pair<char, int>> expected = {{'e', 4}, {'f', 1}, {'g', 2},
			{'k', 2}, {'o', 1}, {'r', 1}, {'s', 2}, };

	EXPECT_EQ(result, expected);
}

TEST(Strings, PalindromeTest) {
	std::string s{"ABCDCBA"};
	bool result = isPalindrome(s);
	EXPECT_EQ(result, true);

	s = "ABBA";
	result = isPalindrome(s);
	EXPECT_EQ(result, true);

	s = "geeks";
	result = isPalindrome(s);
	EXPECT_EQ(result, false);
}

TEST(Strings, SubsequenceTest) {
	std::string s1{"ABCD"};
	std::string s2{"AD"};
	bool result = isSubsequence(s1, s2);
	EXPECT_EQ(result, true);

	s1 = "ABCDE";
	s2 = "AED";
	result = isSubsequence(s1, s2);
	EXPECT_EQ(result, false);

}

TEST(Strings, FindSubstringTest) {
	std::string s{"hello"};

	std::pair<int, int> result = findSubstring(s, "h");
	std::pair<int, int> expected{0, 0};
	EXPECT_EQ(result, expected);

	result = findSubstring(s, "hell");
	expected = {0, 3};
	EXPECT_EQ(result, expected);

	result = findSubstring(s, "hej");
	expected = {-1, -1};
	EXPECT_EQ(result, expected);

	result = findSubstring(s, "l");
	expected = {2, 2};
	EXPECT_EQ(result, expected);

	result = findSubstring(s, "jello");
	expected = {-1, -1};
	EXPECT_EQ(result, expected);

	result = findSubstring(s, "hello");
	expected = {0, 4};
	EXPECT_EQ(result, expected);
}

TEST(Strings, AnagramTest) {
	std::string s1{""};
	std::string s2{""};

	EXPECT_EQ(isAnagram(s1, s2), true);

	s1 = "";
	s2 = "";

	EXPECT_EQ(isAnagram(s1, s2), true);

	s1 = "listen";
	s2 = "silent";

	EXPECT_EQ(isAnagram(s1, s2), true);

	s1 = "aaacb";
	s2 = "cabaa";

	EXPECT_EQ(isAnagram(s1, s2), true);

	s1 = "aab";
	s2 = "bab";

	EXPECT_EQ(isAnagram(s1, s2), false);
}

TEST(Strings, AnagramSearchTest) {
	std::string text{"geeksforgeeks"};
	std::string pattern{"frog"};

	EXPECT_EQ(anagramSearch(text, pattern), true);

	text = "geeksforgeeks";
	pattern = "rseek";

	EXPECT_EQ(anagramSearch(text, pattern), false);
}

TEST(Strings, LexicographicRankTest) {
	std::string text{"STRING"};

	EXPECT_EQ(lexicographicRank(text), 598);
}

TEST(Strings, LeftmostRepeatingTest) {
	std::string s{"geeksforgeeks"};
	int result = leftMostRepeating(s);
	EXPECT_EQ(result, 0);

	s = "abbcc";
	result = leftMostRepeating(s);
	EXPECT_EQ(result, 1);

	s = "abcd";
	result = leftMostRepeating(s);
	EXPECT_EQ(result, -1);
}

TEST(Strings, LeftmostNonRepeatingTest) {
	std::string s = "geeksforgeeks";
	int result = leftMostNonRepeating(s);
	EXPECT_EQ(result, 5);

	s = "abcabc";
	result = leftMostNonRepeating(s);
	EXPECT_EQ(result, -1);

	s = "apple";
	result = leftMostNonRepeating(s);
	EXPECT_EQ(result, 0);
}

TEST(Strings, ReverseWordsTest) {
	std::string s = "welcome to gfg";
	auto result = reverseWords(s);
	EXPECT_EQ(result, "gfg to welcome");

	s = "I love coding";
	result = reverseWords(s);
	EXPECT_EQ(result, "coding love I");

	s = "abc";
	result = reverseWords(s);
	EXPECT_EQ(result, "abc");
}

TEST(Strings, FindPatternNaiveTest) {
	std::string text = "AAAAA";
	std::string pattern = "AAA";

	auto result = findPatternNaive(text, pattern);
	std::vector<int> expected = {0, 1, 2};

	EXPECT_EQ(result, expected);
}

TEST(Strings, FindPatternDistinctTest) {
	std::string text = "ABCABCDABCD";
	std::string pattern = "ABCD";

	std::vector<int> expected = {3, 7};
	auto result = findPatternDistinct(text, pattern);

	EXPECT_EQ(result, expected);
}

TEST(Strings, FindPatternRabinCarpTest) {
	std::string text = "AAAAA";
	std::string pattern = "AAA";

	auto result = findPatternRabinCarp(text, pattern);
	std::vector<int> expected = {0, 1, 2};

	EXPECT_EQ(result, expected);
}

TEST(Strings, FindPatternKMPTest) {
	std::string text = "ABABCABABAAD";
	std::string pattern = "ABABA";

	auto result = findPatternKMP(text, pattern);
	std::vector<int> expected = {5};

	EXPECT_EQ(result, expected);
}

TEST(Strings, CheckRotationsTest) {
	std::string s1 = "ABCD";
	std::string s2 = "CDAB";

	auto result = checkRotation(s1, s2);

	EXPECT_EQ(result, true);

	s1 = "ABAB";
	s2 = "ABBA";

	result = checkRotation(s1, s2);

	EXPECT_EQ(result, false);
}

TEST(Strings, LongestPrefixSuffixTest) {
	std::string text = "AAACAAAA";
	int length = longestPrefixSuffix(text);

	EXPECT_EQ(length, 3);
}

TEST(Strings, LongestDistinctSubstringTest) {
	std::string s;
	EXPECT_EQ(longestSubstringWithDistinctChars(s), 0);

	s = "abaacdbab";
	EXPECT_EQ(longestSubstringWithDistinctChars(s), 4);

	s = "abcdabc";
	EXPECT_EQ(longestSubstringWithDistinctChars(s), 4);

	s = "aaa";
	EXPECT_EQ(longestSubstringWithDistinctChars(s), 1);
}
