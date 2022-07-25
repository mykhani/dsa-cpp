#include "hashing.h"

DirectAddressTable::DirectAddressTable(int start, int end)
    : tbl(end - start + 1, false), offset{start} {}

void DirectAddressTable::insert(int key) {
    if (key - offset < 0 || key - offset >= tbl.size()) {
        throw std::runtime_error("DAT: insert failed, key outside bounds");
    }
            
    tbl[key - offset] = true;
}

void DirectAddressTable::remove(int key) {
    if (key - offset < 0 || key - offset >= tbl.size()) {
        throw std::runtime_error("DAT: remove failed, key outside bounds");
    }
        
    tbl[key - offset] = false;
}

bool DirectAddressTable::search(int key) {
    if (key - offset < 0 || key - offset >= tbl.size()) {
        throw std::runtime_error("DAT: search failed, key outside bounds");
    }
        
    return tbl[key - offset];
}

HashTableChaining::HashTableChaining(int _bucketSize)
    : buckets(_bucketSize, nullptr), bucketSize{_bucketSize} {}

HashTableChaining::~HashTableChaining() {
    // free up chain lists
    for (int i = 0; i < buckets.size(); i++) {
        Node *head = buckets[i];
        if (head == nullptr)
            continue;
        
        Node* next = nullptr;
        for (Node *iter = head; iter; iter = next) {
            next = iter->next;
            delete iter;
        }
    }
}

void HashTableChaining::insert(int key) {
    int index = key % bucketSize;
    Node **head = &buckets[index];
    
    if (*head == nullptr) {
        *head = new Node{key};
    } else {
        // check if the value already exists
        for (Node* iter = *head; iter; iter = iter->next) {
            if (iter->val == key) {
                return;
            }
        }
        
        Node *newNode = new Node{key};
        newNode->next = (*head)->next;
        (*head)->next = newNode;
    }
}

void HashTableChaining::remove(int key) {
    int index = key % bucketSize;
    
    Node **head = &buckets[index];
    
    if (*head == nullptr)
        return;
    
    Node* prev{nullptr};
    Node* curr;
    for (curr = *head; curr; curr = curr->next) {
        if (curr->val == key) {
            // if it is the head node
            if (prev == nullptr) {
                Node* oldHead = curr;
                Node* newHead = curr->next;
                *head = newHead;
                delete oldHead;
            } else {
                Node* next = curr->next;
                prev->next = next;
                delete curr;
                curr = next;
                break;
            }
        }
    }
    
    // head, prev, next, 
    
    return;
}

bool HashTableChaining::search(int key) {
    int index = key % bucketSize;
    Node *head = buckets[index];
    
    for (Node* iter = head; iter; iter = iter->next) {
        if (iter->val == key) {
            return true;
        }
    }
    
    return false;
}

// Time O(n), space O(n)
int countDistinctElements(const vector<int>& vec) {
//	std::unordered_set<int> distinct;
//	for (auto && i : vec) {
//		// no need, insert already takes care of adding unique only
//		//if (distinct.find(i) == distinct.end())
//		distinct.insert(i);
//	}
// even more concise
	std::unordered_set<int> distinct{vec.begin(), vec.end()};

	return distinct.size();
}

// Time O(n), space O(n)
vector<std::pair<int, int> > getFrequency(const vector<int> &vec) {
	vector<std::pair<int, int>> result;
	std::unordered_map<int, int> freq;
	for (const auto& i : vec) {
		freq[i]++;
	}
	for (auto &&[num, count] : freq) {
		result.emplace_back(num, count);
	}
	return result;
}

// Time O(m + n), Space O(min(m, n))
// distinct elements common to both arrays
vector<int> intersectionUnsorted(const vector<int> &a, const vector<int> &b) {

	vector<int> result;

	// we need to store the shorter array in a set
	if (a.size() > b.size())
		return intersectionUnsorted(b, a);

	std::unordered_set<int> s;

	for (const auto& i : a) {
		s.insert(i);
	}

	for (const auto& i : b) {
		// if element of b is also part of a, add it to the result
		if (s.find(i) != s.end()) {
			result.push_back(i);
			// remove the element from set to avoid duplicates
			s.erase(i);
		}
	}

	return result;
}

// distinct elements that exist in both arrays
// Time O(m + n), Space O(m + n))
vector<int> unionUnsorted(const vector<int> &a, const vector<int> &b) {
	// union of two sets is the distinct elements that are
	// Steps
	// 1. Create a set
	// 2. Put all elements of a in set (only distinct are added to the set)
	// 3. Put all elements of b in set

	// 1. Create a set. 2. put all elements of array a in set
	std::unordered_set<int> s{a.begin(), a.end()};


	// 3. Add only those member of b which are not in the set
	for (const auto& i : b) {
		s.emplace(i);
	}

	return std::vector<int>{s.begin(), s.end()};
}

std::pair<int, int> findPairWithSumUnsorted(const vector<int> &vec, int sum) {
	// For each element i , check if value (sum - i) exists inside the set
	std::unordered_set<int> s;

	for (const auto& first : vec) {
		auto second = s.find(sum - first);
		if (second != s.end())
			return {first, *second};

		s.emplace(first);
	}

	return {-1, -1};
}
// check if a subarray (consecutive elements) exists with sum 0 in an usorted array
// Time O(n), space O(n)
bool subarrayWithZeroSumExists(const vector<int> &vec) {
	// Idea
	// let say array elements are frm vec[0], vec[1],...vec[n - 1]
	// If there is a region or subarray withi vec with sum = 0
	// then that region won't have any effect on the prefix sum
	// and means the prefix sum calculated at at some index i
	// would be equal to prefix sum calculated at index < i

	int currPrefixSum = 0;
	std::unordered_set<int> prevPrefixSums;

	for (const auto& i : vec) {
		currPrefixSum += i;
		// if currPrefix sum is 0 or the value has been seen before
		if (currPrefixSum == 0 || prevPrefixSums.find(currPrefixSum) != prevPrefixSums.end())
			return true;

		prevPrefixSums.emplace(currPrefixSum);
	}

	return false;
}

bool subarrayWithSumExists(const vector<int> &vec, int sum) {
	// find prefix sum - sum:
	int prefixSum = 0;
	std::unordered_set<int> prevPrefixSums;

	for (const auto& i : vec) {
		prefixSum += i;
		if (prefixSum == sum)
			return true;
		if (prevPrefixSums.find(prefixSum - sum) != prevPrefixSums.end())
			return true;

		prevPrefixSums.emplace(prefixSum);
	}

	return false;
}

// Time O(n), Space O(n)
std::pair<int, int> longestSubarrayWithSum(const vector<int> &vec, int sum) {
	std::unordered_map<int, int> prevPrefixSums;
	std::unordered_map<int, std::pair<int, int>> ranges;

	int prefixSum = 0;

	for (int i = 0; i < vec.size(); i++) {
		prefixSum += vec[i];
		if (prefixSum == sum) {
			std::pair<int, int> range{0, i};
			ranges.emplace(i + 1, range);
		}
		auto it = prevPrefixSums.find(prefixSum - sum);
		if (it != prevPrefixSums.end()) {
			const auto&[pSum, endIndex] = *it;
			std::pair<int, int> range{endIndex + 1, i};
			ranges.emplace(i - endIndex, range);
		}

		prevPrefixSums.emplace(prefixSum, i);
	}

	int maxSize = 0;
	for (const auto&[size, range] : ranges) {
		maxSize = std::max(maxSize, size);
	}

	return maxSize > 0 ? ranges[maxSize] : std::pair<int, int>{-1, -1};
}

std::pair<int, int> longestSubarrayWithEqualZeroesOnes(const vector<int> &vec) {
	/* Idea:
	 * We need a hashing mechanism that can detect 0 and 1 balance/imbalance
	 * we keep track of the current prefixHash
	   * if it is balanced (contains equal number of 0s and 1s) we store the start and end index
	   * if unbalanced, we look for the previously stored hash that will make it balanced
	 */
	//             <hash, endIndex>
	// represent 0 by -1 and 1 by 1

	std::unordered_map</*hash*/int, /*endIndex*/int> prevHash;
	std::unordered_map</*size*/int, /*interval*/std::pair<int, int>> intervals;

	int hash = 0;

	for (int i = 0; i < vec.size(); i++) {
		hash += (vec[i] == 1 ? 1 : -1);
		// balanced hash
		if (hash == 0) {
			std::pair<int, int> interval{0, i};
			int size = i + 1;
			intervals.emplace(size, interval);
		}

		auto it = prevHash.find(hash);
		if (it != prevHash.end()) {
			const auto&[hash, endIndex] = *it;
			std::pair<int, int> interval{endIndex + 1, i};
			int size = i - endIndex;
			intervals.emplace(size, interval);
		}
		prevHash.emplace(hash, i);
	}

	// find the maxSize
	int maxSize = 0;

	for (const auto&[size, interval] : intervals) {
		maxSize = std::max(maxSize, size);
	}

	return maxSize > 0 ? intervals[maxSize] : std::pair<int, int>{-1, -1};
}

std::pair<int, int> longestCommonSubarrayWithGivenSum(const vector<int> &a, const vector<int> &b) {
	/* Idea
	 *
	 *     			    a = 1 0 1 0  0 1 1
	 *     			    b = 0 0 1 1  1 0 0
	 * prefixDiffAB (A-B) = 1 1 1 0 -1 0 1
	 * At each prefixDiffAB calculation, store it in hash. If the value at index is 0,
	 * the interval from 0 to i constitutes the given sum. If not 0, try to find the prefix
	 * diff in hashed values. If found at endIndex j, the indices from j + 1 to i
	 * constitute the given sum. To see if it works for the reversed valus i.e.
	 *     			    a =  0   0  1 1  1 0  0
	 *     			    b =  1   0  1 0  0 1  1
	 * prefixDiffAB (A-B) = -1  -1 -1 0  1 0 -1
	 * You can see that a same prefixDiffAB exists for multiple indices, therefore
	 * use unordered_multimap to store indices along the prefixDiffAB value they
	 * produce and chose the smallest index out of the available indices
	 *
	 */

	// use the smaller as the size
	int size = a.size() > b.size() ? a.size() : b.size();

	std::unordered_multimap<int, int> prevPrefixDiffAB; //  <prefixDiffAB, endIndex>
	std::unordered_map<int, std::pair<int, int>> intervals; // <length, interval>
	int prefixDiffAB = 0;

	for (int i = 0; i < size; i++) {
		prefixDiffAB = a[i] - b[i];
		if (prefixDiffAB == 0) {
			int start = 0;
			int end = i;
			int length = end - start + 1;
			std::pair<int, int> interval{start, end};
			intervals.emplace(length, interval);
		}

		auto it = prevPrefixDiffAB.find(prefixDiffAB);
		if ( it != prevPrefixDiffAB.end()) {
			// get all indices that produce the prefixDiff
			auto range = prevPrefixDiffAB.equal_range(prefixDiffAB);
			// chose smallest index, first
			int start = range.first->second + 1;
			int end = i;
			int length = end - start + 1;
			std::pair<int, int> interval{start, end};
			intervals.emplace(length, interval);
		}

		prevPrefixDiffAB.emplace(prefixDiffAB, i);
	}

	int maxlen = 0;

	for (const auto&[len, interval] : intervals) {
		maxlen = std::max(maxlen, len);
	}

	return maxlen > 0 ? intervals[maxlen] : std::pair<int, int>{-1, -1};
}

vector<int> longsetSubsequence(const vector<int> &vec) {
	std::unordered_set<int> set;
	vector<int> sequence {};
	vector<int> longestSequence {};

	// put all elements in set first to enable of of order lookup
	for (const auto& i : vec) {
		set.emplace(i);
	}

	// start a sequence from value v for which v - 1 is not found in the set
	int maxlen = 0;
	int len;

	for (const auto& i : vec) {
		// find the leftmost value of a sequence
		if (set.find(i - 1) == set.end()) {
			sequence.push_back(i);
			len = 1;
			int next = 1;
			// find consecutive elements
			while (set.find(i + next) != set.end()) {
				sequence.push_back(i + next);
				next++;
			}

			if (len > maxlen) {
				longestSequence = sequence;
				maxlen = len;
			}
			// reset the sequence
			sequence.clear();
		}
	}

	return longestSequence;
}

std::vector<int> countDistinctElementsPerWindow(const vector<int> &vec, int k) {
	// e.g vec = {1, 2, 3, 3, 4} and k = 3, return {3, 2, 2}

	// we need to maintain the count of distinct elements per window
	std::unordered_map<int, int> freq; // <value, count>
	vector<int> result;

	for (int i = 0; i < k; i++) {
		freq[vec[i]]++;
	}

	result.push_back(freq.size());

	for (int i = k; i < vec.size(); i++) {
		freq[vec[i - k]]--;
		if (freq[vec[i - k]] == 0)
			freq.erase(vec[i - k]);

		freq[vec[i]]++;

		result.push_back(freq.size());

	}

	return result;
}

std::vector<int> moreThanNByKOcurrences(const vector<int> &vec, int k) {
	std::unordered_map<int, int> freq; // <value, occurrences>
	vector<int> result;
	int n = vec.size();

	// O(n)
	for (const auto& i : vec) {
		freq[i]++;
	}

	// O(n)
	for (const auto&[value, count] : freq) {
		if (count > n / k) {
			result.emplace_back(value);
		}
	}

	return result;
}
