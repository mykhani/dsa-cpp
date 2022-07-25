/*
 * strings.h
 *
 *  Created on: 29 Jun 2021
 *      Author: ykhan
 */

#ifndef STRINGS_STRINGS_H_
#define STRINGS_STRINGS_H_

#include <vector>
#include <string>
#include <utility>
#include <unordered_map>
/*
 * Character encodings:
 * ASCII: 8-bit (only 128 English characters, extended ASCII has 256)
 * Unicode UTF-16: 16-bit (international characters supported)
 * The first 128 character encodings are same in both SCII and Unicode.
 */

/*
 * Overview of pattern searching algorithms:
 * m => pattern length
 * n => text length
 * criteria: 1 <= m <= n
 *
 * Naive:
 * O((n-m+1)*m): When characters of the pattern repeat (worst case all characters are same)
 * when all characters of the pattern are distinct: O(n)
 * NO PREPROCESSING
 *
 * Rabin Karp:
 * O((n-m+1)*m) : But better than naive on average
 * PREPROCESS PATTERN
 * Compute a hash of the pattern, see if a window matches the hash of the pattern only
 * then compare the window with the text.
 *
 * KMP:
 * O(n)
 * PREPROCESS PATTERN
 * Creates LPS array from the pattern (removes redundancies from the pattern)
 * LPS stands for Longest Prefix which is also suffix
 *
 * Suffix Tree:
 * O(m) // search complexity
 * PREPROCESS TEXT O(n)
 */

std::vector<std::pair<char, int>> frequencyOfCharactersLowercaseString(
		std::string s);

// Time O(n), space O(1)
bool isPalindrome(const std::string& s);

// Time O(n + m), space O(1)
// n is length of s1, m is length of s2
// O(n + m) because there are m comparisons being done inside the for loop
bool isSubsequence(const std::string& s1, const std::string& s2);

// returns the first index of the substring found
std::pair<int, int> findSubstring(const std::string& s,
		const std::string& pattern);

// Return a list of indices matching the pattern
// Time O((n-m+1)*m), space O(1)
std::vector<int> findPatternNaive(const std::string& text,
		const std::string& pattern);

// Return a list of indices matching the pattern which is distinct
// Time O(n), space O(1)
std::vector<int> findPatternDistinct(const std::string& text,
		const std::string& pattern);

// Return a list of indices matching the pattern
// Time O(m*(n-m)), space O(1)
std::vector<int> findPatternRabinCarp(const std::string& text,
		const std::string& pattern);

// Return a list of indices matching the pattern
// Knuth-Morris-Prat algorithm (using lps array)
// Time O(n), space O(m)
std::vector<int> findPatternKMP(const std::string& text,
		const std::string& pattern);

// check if two strings are rotations of each other
bool checkRotation(const std::string& s1, const std::string& s2);

// two strings are anagrams if they are permutations of each other
// and frequency of each character is also same
// e.g silent and listen are anagrams
// Time O(n), space O(1) // 256 chars
bool isAnagram(const std::string& s1, const std::string& s2);

// check if a pattern (or its permutation) exists inside the text (should be consecutive)
// Time O(n), space O(1)
bool anagramSearch(const std::string& text, const std::string& pattern);

// find the lexicographic rank of a string
// lexicographic rank: arrange the letters in ascending order,
// the rank is the number of permutation that matches the string
int lexicographicRank(const std::string& s);

// index of leftmost repeating character in a string
// Time O(n), space O(1)
int leftMostRepeating(const std::string& s);

// return the index of left-most non-repeating character
int leftMostNonRepeating(const std::string& s);

std::string reverseWords(std::string s);

/*
 * Longest prefix which is also suffix without any overlap
 * Input : aabcdaabc
 Output : 4
 The string "aabc" is the longest
 prefix which is also suffix.

 Input : abcab
 Output : 2

 Input : aaaa
 Output : 2
 */
// see https://leetcode.com/problems/implement-strstr/discuss/13160/detailed-explanation-on-building-up-lps-for-kmp-algorithm
int longestPrefixSuffix(std::string s);

// find the length of longest substring with distinct characters
int longestSubstringWithDistinctChars(const std::string& s);
#endif /* STRINGS_STRINGS_H_ */
