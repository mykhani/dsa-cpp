#ifndef HASHING_H
#define HASHING_H

#include <utility>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
/*
 Hashing mainly used to implement:
 * Dictionaries (key - values)
 * Sets
 Hashing advantages:
 * Search O(1)
 * Insert O(1)
 * Delete O(1)

 How does it compare with:
 Unsorted arrays:
 * Search O(n)
 * Insert O(1) // insert at end
 * Delete O(1) // just mark element as deleted (no need to adjust array)

 Sorted arrays:
 * Search O(logn)
 * Insert O(n)
 * Delete O(n)

 Self balance binary search trees (AVL and RB)
 * Search O(logn)
 * Insert O(logn)
 * Delete O(logn)

 * Hash table is good for finding exact match
 * Not good for cases where:
 * you need less than or greater than keys (use BST)
 * you need elements as sorted (use BST)

 Hashing applications:
 * Dictionaries
 * Database indexing
 * Cryptography
 * Caches
 * Symbol table in compiler/interpreters
 * Routers
 * Getting data from databases

 Hash function: convert a large value into a small value that can be
 used as an index

 Requirements for a hash function:
 * Everytime a hash function is applied to a key, it must generate the same hash value (index?) 
 * Should generate values from 0 to m - 1 where m is the size of hash table
 * Should be fast. O(1) for integers and O(len) for strings of length len
 * Should uniformly distribute large keys into hash table slots (to make sure each go into
 its own slot. Difficult to achieve and there would be cases where different keys result
 into a same hash value, which is called a collision.

 Example hashing functions:
 * hash(large_key) = large_key % m where m is the size of hash table. Ideally m is chosen
 as a prime number (less common factors) close to the size of hash table. Other bad
 value of m is 10^n e.g. 10^3. Here, the hash function only checks last 3 digits.
 or m = 2^3, where it checks only last 3 bits in the binary representation

 * for strings, weighted sum: str = "abcd";
 hash(str) = (str[0] * x^0 + str[1] * x^1 + str[2] * x^2....) % m;
 where x can be any numbe e.g. x = 33;

 if simple sum is used i.e. sum ASCII values of all characters and then take modulo m,
 there is a problem i.e. hash for "abcd" and "dcba" or any other permutation would be same.
 That is why weighted sum is used.

 * universal hashing
 You have a group of hash functions, and each time you pick one of them randomly.
 There is no pattern of data for which it will not result in uniform distribution

 Hashing collisions:
 * If we know keys in advance, then we can use perfect hashing (advanced technique)
 * If we do not know keys in advance, then we use one of the following:
 * Chaining // maintain an array of linkedlist. Each slot is a linkedlist
 that contains collided keys
 * Open Addressing:
 * Linear probing
 * Quadratic probing
 * Double hashing

 Chaining Performance:
 m = number of slots in hash table
 n = number of keys to be inserted
 load factor (alpha) = n / m; (C++ allows to set load factor for unordered_set, unordered_map)
 load factor determines how big you want your hash table to be. It is a trade-off between
 space and time. A higher load factor means smaller m (inversely proportional). smaller m
 means more collisions and hence, more time

 Expected chain length = n / m = load factor (alpha) (assuming an uniform distribution i.e. every key is equally likely
 to go into other slot i.e. probability for a key to to occupy any slot out of m slots is 1 / m)
 So the number of keys in a particular slot is n / m);

 Worst case: all keys go into a same slot.

 Expected time to search: O(1 + alpha). O(1) to find the slot and O(alpha) to search through the chain
 Expected time to insert/delete: O(1 + alpha)

 All the above works if the hashing function generates keys with uniform distribution

 Options of datastructures to implement chaining
 * linkedlist   
 * search O(l), insert/delete O(l)
 * not cache friendly
 * extra overhead for storing next pointers

 * vector (Dynamic arrays)
 * search O(l), insert O(l), delete O(l)
 * cache friendly

 * Self-balancing BST (AVL or RB)
 * search O(logl), insert O(logl), delete O(logl)
 * not cache friendly
 
 */
#include <vector>
#include <type_traits>
#include <iostream>
#include <stdexcept>

using namespace std;
/* 
 Drawbacks of using direct address table
 * array size could be very large
 * doesn't work when keys are floating points or strings
 */
class DirectAddressTable {
	vector<bool> tbl;
	int offset;
public:
	DirectAddressTable(int start, int end);
	void insert(int key);
	void remove(int key);
	bool search(int key);
};

struct Node;

struct Node {
	int val;
	Node *next { nullptr };

	Node(int _val) :
			val { _val } {
		cout << "Creating node with val: " << val << endl;
	}
	~Node() {
		cout << "Deleting node with val: " << val << endl;
	}
};

// Hashtable with chaining to handle collisions
class HashTableChaining {
	vector<Node*> buckets;
	int bucketSize;
public:
	HashTableChaining(int _bucketSize);
	~HashTableChaining();
	void insert(int key);
	void remove(int key);
	bool search(int key);
};

// Open addressing is another method to handle collisions
// Requirements: no of slots >= number of keys (or items) to be inserted
// Benefit: cache friendly

// multiple implementations of open-addressing:
// * linear probing - linearly search for the next empty spot after a collision is detected
// * quadratic probing - next probed position is the square of the collision.
//                       e.g if collision happens at position cur, then for 1st, 2nd and 3rd collision,
//                       probed positions are next cur + 1, cur + 4, cur + 9
//                       or hash(cur, i) for i >=1, cur + i^2
// * double hashing

enum class SlotStatus {
	EMPTY, OCCUPIED, DELETED
};

template<typename Key>
class HashTableOpenAddressing {
protected:
	int slots;
	vector<Key> values;
	vector<SlotStatus> slotStatus;
	int used = 0;

public:
	HashTableOpenAddressing(int _slots) :
			slots { _slots }, values(_slots, Key { }),
			slotStatus(_slots, SlotStatus::EMPTY), used {0} {}

	int hash(Key k);
	void insert(Key key);
	void remove(Key key);
	bool search(Key key);

	virtual int probe(Key key, bool search = false) = 0;

	virtual ~HashTableOpenAddressing() = default;
};

template<typename Key>
inline int HashTableOpenAddressing<Key>::hash(Key k) {
	// TODO: check if Key type is int
//	return k % HashTableOpenAddressing<Key>::slots;
	// slots is not detected without this-> prefix
	// see https://stackoverflow.com/questions/1120833/derived-template-class-access-to-base-class-member-data
	return k % this->slots;
}

template<typename Key>
inline void HashTableOpenAddressing<Key>::insert(Key key) {
	if (this->used == this->slots)
		return;

	int slot = probe(key); // linear or quadratic probing

	if (slot >= 0) {
		this->values[slot] = key;
		this->slotStatus[slot] = SlotStatus::OCCUPIED;
		this->used++;
	}
}

template<typename Key>
inline void HashTableOpenAddressing<Key>::remove(Key key) {
	int slot = probe(key, true);

	if (slot >= 0) {
		this->slotStatus[slot] = SlotStatus::DELETED;
		this->used--;
	}
}

template<typename Key>
inline bool HashTableOpenAddressing<Key>::search(Key key) {
	int slot = probe(key, true);

	if (slot >= 0)
		return true;

	return false;
}

// Linear probing
// problem with linear probing is clusters
// to spread out these clusters, use quadratic probing (instead of searching consecutive
// positions, search every next, fourth, 9th i.e i^2 element
// The disadvantage of quadratic probing is that it might miss empty
// slots even if they are available
// Mathematically, it has been proven that to not skip any empty
// slots using quadratic probing,s
// if load factor < 0.5 and number of slots m is a prime number, only
// then quadratic probing guarantees that it won't skip any empty slots
// lf = entries / m; so m should be > double the entries for quadratic
// probing to work
// quadratic probing also has secondary clusters but it is still better than
// clusters using linear probing
template<typename Key>
class HashTableOpenAddressingLinearProbing: public HashTableOpenAddressing<Key> {

public:
	virtual int probe(Key key, bool search = false) override;

	// inherit ctor
	using HashTableOpenAddressing<Key>::HashTableOpenAddressing;

};

template<typename Key>
inline int HashTableOpenAddressingLinearProbing<Key>::probe(Key key,
		bool search) {
	//
	int i = 0;
	int start = this->hash(key);
	int pos = start + i;

	// if we are searching for a key, terminate search when key is found or an empty slot is encountered
	if (search) {
		do {
			if (this->slotStatus[pos] == SlotStatus::EMPTY)
				return -1;

			// Either occupied or deleted
			if (this->values[pos] == key) {
				if (this->slotStatus[pos] != SlotStatus::DELETED) {
					return pos;
				} else {
					return -1;
				}
			}

			i++;
			pos = (start + i) % this->slots;

		} while (this->slotStatus[pos] != SlotStatus::EMPTY && pos != start);
		// we are looking for a free position (empty or deleted)
	} else {
		do {
			if (this->slotStatus[pos] == SlotStatus::EMPTY
					|| this->slotStatus[pos] == SlotStatus::DELETED) {
				return pos;
			}
			// slot status occupied
			// if key already exists, return
			if (this->values[pos] == key)
				return -1;

			i++;
			pos = (start + i) % this->slots;

		} while (pos != start);
	}

	return -1;
}

template<typename Key>
class HashTableOpenAddressingQuadraticProbing: public HashTableOpenAddressing<
		Key> {
public:
	virtual int probe(Key key, bool search = false) override;

	// inherit ctor
	using HashTableOpenAddressing<Key>::HashTableOpenAddressing;

};

template<typename Key>
inline int HashTableOpenAddressingQuadraticProbing<Key>::probe(Key key,
		bool search) {
	//
	int i = 0;
	int start = this->hash(key);
	int pos = start + i;

	// if we are searching for a key, terminate search when key is found or an empty slot is encountered
	if (search) {
		do {
			if (this->slotStatus[pos] == SlotStatus::EMPTY) {
				return -1;
			}
			// Either occupied or deleted
			if (this->values[pos] == key) {
				if (this->slotStatus[pos] != SlotStatus::DELETED) {
					return pos;
				} else {
					return -1;
				}
			}

			i++;
			pos = (start + i * i) % this->slots;

		} while (this->slotStatus[pos] != SlotStatus::EMPTY && pos != start);
		// we are looking for a free position
	} else {
		do {
			if (this->slotStatus[pos] == SlotStatus::EMPTY
					|| this->slotStatus[pos] == SlotStatus::DELETED) {
				return pos;
			}

			i++;
			pos = (start + i * i) % this->slots;

		} while (pos != start);
	}

	return -1;
}

template<typename Key>
class HashTableOpenAddressingDoubleHashing: public HashTableOpenAddressing<Key> {
public:
	virtual int probe(Key key, bool search = false) override;
	int hash2(Key k);
	// inherit ctor
	using HashTableOpenAddressing<Key>::HashTableOpenAddressing;

};

template<typename Key>
inline int HashTableOpenAddressingDoubleHashing<Key>::hash2(Key k) {
	// Goal is to return an offset value that is prime with respect to
	// total slots. Since by design we chose the value of total slots
	// to be a prime number, I guess any number less than total slots
	// should do the job.
	// TODO: verify this assumption
	int offset = this->slots - 1;
	// hash2 function should never return 0 to
	// prevent looping probing at same position forever)

	// k % offset return values in the range
	// [0 ... offset - 1]

	// the below expression converts that range to values from
	// [offset ... 1]
	return offset - (k % offset);
}

template<typename Key>
inline int HashTableOpenAddressingDoubleHashing<Key>::probe(Key key,
		bool search) {
	//
	int i = 0;
	int start = this->hash(key);
	int offset = this->hash2(key);
	// the return value of offset or hash2(key) should be prime with
	// respect to total slots i.e. it must not be divisible by total slots
	// Lets say total slots = 7 and offset = 4 and start = 0
	// (0 * 4) % 7 = 0
	// (1 * 4) % 7 = 4
	// (2 * 4) % 7 = 1
	// (3 * 4) % 7 = 5
	// (4 * 4) % 7 = 2
	// (5 * 4) % 7 = 6
	// (6 * 4) % 7 = 3

	// this makes the probe sequence kind of a pseudo random sequence
	// for each collision, the sequence is generated based on the key (seed)

	// this randomization prevents clustering
	// i.e. not a fixed general formula same for all keys

	// we can re-generate that sequence when we want to perform a lookup
	// using key as the seed value

	int pos = (start + i * offset) % this->slots; // initially pos = start for i = 0

	// if we are searching for a key, terminate search when key is found or an empty slot is encountered
	if (search) {
		do {
			if (this->slotStatus[pos] == SlotStatus::EMPTY) {
				return -1;
			}
			// Either occupied or deleted
			if (this->values[pos] == key) {
				if (this->slotStatus[pos] != SlotStatus::DELETED) {
					return pos;
				} else {
					return -1;
				}
			}

			i++;
			pos = (start + i * offset) % this->slots;

		} while (this->slotStatus[pos] != SlotStatus::EMPTY && pos != start);
		// we are looking for a free position
	} else {
		do {
			if (this->slotStatus[pos] == SlotStatus::EMPTY
					|| this->slotStatus[pos] == SlotStatus::DELETED) {
				return pos;
			}

			i++;
			pos = (start + i * offset) % this->slots;

		} while (pos != start);
	}

	return -1;
}

// return the count of distinct elements
int countDistinctElements(const vector<int>& vec);

// return the frequency of elements
vector<std::pair<int, int>> getFrequency(const vector<int>& vec);

// intersection of two unsorted arrays
vector<int> intersectionUnsorted(const vector<int>& a, const vector<int>& b);

// union of two unsorted arrays
vector<int> unionUnsorted(const vector<int>& a, const vector<int>& b);

// find a pair with a given sum
std::pair<int, int> findPairWithSumUnsorted(const vector<int>& vec, int sum);

// see if a subarray with sum 0 exists
bool subarrayWithZeroSumExists(const vector<int>& vec);

// see if a subarray with a given sum exists
bool subarrayWithSumExists(const vector<int>& vec, int sum);

// return the starting and ending index of the maxmium subarray with the given sum
std::pair<int, int> longestSubarrayWithSum(const vector<int>& vec, int sum);

// return the starting and ending index of the longest subarray with equal number
// of 0's and 1's
std::pair<int, int> longestSubarrayWithEqualZeroesOnes(const vector<int>& vec);

// return the longest common array with same sum in two arrays
std::pair<int, int> longestCommonSubarrayWithGivenSum(const vector<int>& a, const vector<int>& b);

// find the longest subsequence in the form x, x+1, x+2, ...x + i with these elements
// appearing in any order
vector<int> longsetSubsequence(const vector<int>& vec);

// return a vector containing count of distinct elements per window
std::vector<int> countDistinctElementsPerWindow(const vector<int>& vec, int k);

std::vector<int> moreThanNByKOcurrences(const vector<int>& vec, int k);
#endif
