/*
 * strings.cpp
 *
 *  Created on: 29 Jun 2021
 *      Author: ykhan
 */

#include "strings.h"
#include <climits>
#include <algorithm>
#include <unordered_map>
#include "../recursion/recursion.h"

using namespace std;

#define CHAR 256

std::vector<std::pair<char, int>> frequencyOfCharactersLowercaseString(
		std::string s) {
	// there could be only 26 lower case characters
	std::vector<int> freq(26, 0);

	for (const auto &c : s) {
		int offset = c - 'a';
		freq[offset]++;
	}

	std::vector<std::pair<char, int>> result;
	for (int i = 0; i < freq.size(); i++) {
		if (freq[i] > 0) {
			result.push_back({'a' + i, freq[i]});
		}
	}

	return result;
}

bool isPalindrome(const std::string& s) {
	int left = 0;
	int right = s.length() - 1;

	while (left < right) {
		if (s[left] != s[right]) {
			return false;
		}
		left++;
		right--;
	}

	return true;
}

bool isSubsequence(const std::string& s1, const std::string& s2) {
	// pick the smaller of the two
	if (s1.length() < s2.length()) {
		return isSubsequence(s2, s1);
	}

	int matchIdx = 0;

	for (int i = 0; i < s1.length() && matchIdx < s2.length(); i++) {
		if (s1[i] == s2[matchIdx]) {
			matchIdx++;
		}
	}

	return matchIdx == s2.size();
}

// O(n)
std::pair<int, int> findSubstring(const std::string& s,
		const std::string& pattern) {
	// using sliding window method
	int start = -1;
	int end = -1;
	int matchIdx = 0;
	int matchLength = pattern.length();

	for (int i = 0; i < s.length(); i++) {
		if (s[i] == pattern[matchIdx]) {
			if (start == -1) // first character matched
				start = i;

			matchIdx++;
		} else { // reset
			matchIdx = 0;
			start = -1;
		}

		if (start >= 0 && i - start + 1 == matchLength) {
			end = i;
			break;
		}
	}

	return {start, end};
}

// Time O(n) space O(1)
std::vector<int> findPatternDistinct(const std::string& text,
		const std::string& pattern) {
	std::vector<int> result;

	int m = pattern.length();
	int n = text.length();

	for (int i = 0; i <= n - m;) {
		int j;

		for (j = 0; j < m; j++) {
			if (text[i + j] != pattern[j]) {
				break;
			}
		}

		if (j == m) {
			result.push_back(i);
		}

		if (j == 0) {
			i++;
		} else {
			i += j;
		}
	}

	return result;
}

// Time O((n-m+1)*m), space O(1)
std::vector<int> findPatternNaive(const std::string& text,
		const std::string& pattern) {
	std::vector<int> result;

	int m = pattern.length();
	int n = text.length();

	// To search for pattern AA (m=2) in text AAAA (n=4)
	// We need to perform (n-m+1) comparisons i.e. AA AA AA
	for (int i = 0; i < n - m + 1; i++) {
		int j;
		for (j = 0; j < m; j++) {
			if (text[i + j] != pattern[j]) {
				break;
			}
		}

		if (j == m) {
			// match found
			result.push_back(i);
		}
	}

	return result;
}

bool isAnagram(const std::string& s1, const std::string& s2) {
	if (s1.length() != s2.length())
		return false;
	// To store 256 ASCII characters
	std::vector<int> freq(256, 0);

	for (int i = 0; i < s1.size(); i++) {
		freq[s1[i]]++;
		freq[s2[i]]--;
	}

	for (int i = 0; i < freq.size(); i++) {
		if (freq[i] != 0)
			return false;
	}

	return true;
}

int leftMostRepeating(const std::string& s) {
	// traverse string from the right
	// maintain the count of character or visited status
	// if count becomes greater than 1 or visited is true,
	// select as possible result
	std::vector<bool> visited(256, false);
	int result = -1;

	for (int i = s.length() - 1; i >= 0; i--) {
		if (visited[s[i]])
			result = i;
		else
			visited[s[i]] = true;
	}

	return result;
}

int leftMostNonRepeating(const std::string& s) {

	// status of the character
	// -1: not visited
	// -2: repeated
	// positive value: index
	int status[256];

	std::fill(status, status + 256, -1);

	for (int i = 0; i < s.length(); i++) {
		if (status[s[i]] == -1) {
			status[s[i]] = i;
		} else {
			status[s[i]] = -2;
		}
	}
	// pick the minium index
	int result = INT_MAX;
	for (int i = 0; i < 256; i++) {
		if (status[i] >= 0) {
			result = std::min(result, status[i]);
			break;
		}
	}

	return result == INT_MAX ? -1 : result;
}

void reverseString(std::string& s, int start, int end) {
	while (start < end) {
		std::swap(s[start], s[end]);
		start++;
		end--;
	}
}

std::string reverseWords(std::string s) {
	int idx = 0;

	reverseString(s, 0, s.length() - 1);

	for (int i = 0; i < s.length(); i++) {
		if (s[i] == ' ') {
			reverseString(s, idx, i - 1);
			idx = i + 1;
		}
	}

	if (idx < s.length()) {
		reverseString(s, idx, s.length() - 1);
	}

	return s;
}

std::vector<int> findPatternRabinCarp(const std::string& text,
		const std::string& pattern) {

	// This alogrithm maintains a rolling hash function and compares
	// the piece from text with a pattern only when its hash matches
	// the hash of the pattern
	// The simplest form of calculating hash is XOR but it is not
	// effective as two different strings but with repeated
	// characters e.g. aaaa & bbbbb will have the same hash
	// Another hash function of simply adding the ASCII values is
	// also not effective as all permutations of the pattern
	// will have same hash, e.g. for pattern abc, cba, cab both
	// will match. So a better hashing function is the weighted
	// sum of characters. Consider a weight factor d = 5, and pattern
	// length l = 4 for pattern abcd for text = acdabcd
	// the hash of first pattern length slice acda can be calculated as
	// h_0 = 5^3 * a + 5^2* c + 5^1 * d + a
	// To find the rolling hash for character i, we can use this formula
	// h_i = d*(h_i-1 - text[i-1]*d^(l-1)) + text[i+m-1]
	// e.g for above example
	// h_1 = 5^3  * c + 5^2 * d + 5 * a + b = 5(h_0 - 5^3 * a) + b
	// i.e. first remove the hash of the first element of the previous
	// window, then multiply by d to shift left and then add the last
	// item of new window

	std::vector<int> result;
	int n = text.length();
	int m = pattern.length();
	int d = 256; // 8-bit extended ASCII chars

	int patternHash = 0;
	int textHash = 0;

	int factor = 1;
	int limit = 101; // modulo to limit the powers of d to a valid range to avoid overflows

	// d^(m-1)
	for (int i = 1; i <= m - 1; i++) {
		factor = (factor * d) % limit; // m = 3 => factor = d^2 i.e. 1, d, d^2
	}

	for (int i = 0; i < m; i++) {
		patternHash = (patternHash * d + pattern[i]) % limit;
		textHash = (textHash * d + text[i]) % limit;
	}

	for (int i = 0; i <= n - m; i++) {
		if (patternHash == textHash) {
			int j;
			for (j = 0; j < m; j++) {
				if (text[i + j] != pattern[j]) {
					break;
				}
			}
			if (j == m) {
				result.push_back(i);
			}
		}

		// update hash for next window
		// if there is not next window then skip
		// no next window if current window is final,
		// in this case, i points to the last element
		// of the previous window or the previous
		// element of the first element of last window
		// first element of last window is n - m
		// so i must be less than n - m
		if (i < n - m) {
			textHash = (d * (textHash - factor * text[i]) + text[i + m])
					% limit;

			if (textHash < 0)
				textHash += limit; // make negative value positive e.g -3 % 10 == -3 + 10 % 10
		}
	}

	return result;
}

static std::vector<int> createLps(const std::string& s) {
	int n = s.length();
	std::vector<int> lps(n, 0);

	int i = 1;
	int len = 0;

	lps[0] = 0;

	while (i < n) {
		if (s[i] == s[len]) {
			len++;
			lps[i] = len;
			i++;
		} else {
			if (len == 0) {
				lps[i] = 0;
				i++;
			} else {
				len = lps[len - 1];
			}
		}
	}

	return lps;
}

std::vector<int> findPatternKMP(const std::string& text,
		const std::string& pattern) {

	std::vector<int> result; // indices

	int m = pattern.length();
	int n = text.length();
	int i = 0;
	int j = 0;

	std::vector<int> lps = createLps(text);

	while (i < n) {
		if (text[i] == pattern[j]) {
			i++;
			j++;

			if (j == m) {
				result.push_back(i - j);
				j = lps[j - 1];
			}
		} else {
			if (j == 0) {
				i++;
			} else {
				j = lps[j - 1];
			}
		}
	}

	return result;
}

bool checkRotation(const std::string& s1, const std::string& s2) {
	// find the first matching characters
	int len1 = s1.length();
	int len2 = s2.length();

	if (len1 != len2)
		return false;

	return (s1 + s1).find(s2) != std::string::npos;

// works but need more testing
//	int first = -1;
//
//	for (int i = 0; i < len1; i++) {
//		if (s1[i] == s2[0]) {
//			first = i;
//			break;
//		}
//	}
//
//	if (first < 0)
//		return false;
//
//	int j;
//
//	for (j = 0; j < len1; j++) {
//		if (s1[(j + first) % len1] != s2[j]) {
//			break;
//		}
//	}
//
//	return j == len1;
}

bool anagramSearch(const std::string& text, const std::string& pattern) {
	bool lut[256] = {false};

	for (int i = 0; i < pattern.length(); i++) {
		lut[pattern[i]] = true;
	}

	int count = 0;

	for (int j = 0; j < text.length(); j++) {
		if (lut[text[j]]) {
			count++;
			if (count == pattern.length()) {
				break;
			}
		} else {
			count = 0;
		}
	}

	return count == pattern.length();
}

static int factorial(int n) {
	int result = 1;

	while (n > 0) {
		result *= n;
		n--;
	}

	return result;
}

int lexicographicRank(const std::string& s) {
	int count[CHAR]{0};
	int prefixCount[CHAR]{0};
	int lowerPermutations = 0;
	int m = s.length();
	int factorialComputed = factorial(m);

	for (int i = 0; i < m; i++) {
		int index = s[i];
		count[index]++;
	}
	// S : 83
	// T : 84
	// R : 82
	// I : 73
	// N : 78
	// G : 71
	// 6 5 4 3 2 1
	for (int i = 1; i < CHAR; i++) {
		prefixCount[i] = prefixCount[i - 1] + count[i - 1];
	}

	for (int i = 0; i < m; i++) {
		int index = s[i];
		int lessThan = prefixCount[index];
		factorialComputed /= m - i;
		lowerPermutations += (lessThan * factorialComputed);
		// reduce count
		for (int j = index + 1; j < CHAR; j++) {
			prefixCount[j]--;
		}
	}

	return lowerPermutations + 1;
}

/*
 * Longest prefix which is also suffix without any overlap
 * Input : aabcdaabc
 * Output : 4
 * The string "aabc" is the longest
 * prefix which is also suffix.

 * Input : abcab
 * Output : 2

 * Input : aaaa
 * Output : 2
 */
// Time O(n/2) ~ O(n), space O(1)
int longestPrefixSuffix(std::string s) {

	int n = s.length();
	std::vector<int> lps(n, 0);

	lps[0] = 0;

	int i = 1;
	int len = 0;

	while (i < n) {
		if (s[i] == s[len]) {
			len++;
			lps[i] = len;
			i++;

		} else {
			if (len == 0) {
				lps[i] = 0;
				i++;
			} else {
				len = lps[len - 1];
			}
		}
	}

	return lps[n - 1];
}

int longestSubstringWithDistinctChars(const std::string& s) {
	std::unordered_map<char, int> traversed;

	int maxCount = 0;
	int begin = 0;
	int i = 0;

	while (i < s.length()) {
		char c = s[i];
		auto found = traversed.find(c);
		if (found != traversed.end() && found->second >= begin) {
			begin = found->second + 1;
		}
		traversed[c] = i;
		maxCount = std::max(maxCount, i - begin + 1);
		i++;
	}

	return maxCount;
}
