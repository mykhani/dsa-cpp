#include "bit-magic.h"

#include <stdexcept>
#include <sstream>
#include <iostream>
#include <unordered_map> // hash map O(1) find, insert
#include <cmath>

using namespace std;

// check wether the kth bit is set. O(1)
bool check_bit(int n, int k)
{
    if (k < 1) {
        std::ostringstream oss;
        oss << "checkbit, bit cannot be less than 1";
        throw std::runtime_error(oss.str());
    }
    
    if (k > sizeof(int) * 8) {
        std::ostringstream oss;
        
        oss << "checkbit, kth bit cannot be larger than " << sizeof(int) * 8;
        throw std::runtime_error(oss.str());
    }
    
    // left-shift and right-shift, both are equivalent
//    return n & (1 << k - 1);
    return n >> k - 1 & 0x1;
}

// count the set bits of an integer. O(logn)

class Table {
    int set_count[256];
public:
    static Table& create() {
        static Table table;
        return table;
    }
private:
    Table() {
        cout << "Initializing lookup table for set bits count" << endl;
        set_count[0] = 0;
        for (int i = 1; i < 256; i++) {
            set_count[i] = (i & 0x1) + set_count[i / 2]; // set_count[6] = 0 + set_count[3] -> similar to n / 10 for checking digit
        }
    }
public:
    int operator[](int index) {
        return set_count[index];
    }
};

int count_set_bits(int n)
{
    int count = 0;
    auto&& table = Table::create();
//    Table table = Table::create();
    
    // naive
//    while (n > 0) {
//        if (n & 0x1)
//            count++;
//            
//        n >>= 1;
//    }

    // Brian Kernighan's Algorithm: O(set bits count)
    // if you subtract 1 from a number, all the 0's before the first 1 become 1 and the first 1 becomes 0
    // e.g 15: 1111: 15-1: 1110, 8: 1000 8-1: 0111.
//    while (n > 0) {
//        n = n & (n - 1);
//        count++;
//    }
    // most efficient lookup table
    count += table[0xFF & n >> 24];
    count += table[0xFF & n >> 16];
    count += table[0xFF & n >> 8];
    count += table[0xFF & n];
    
    return count;
}

// check if an integer is a power of 2. O(1)
// 4 100 is yes
// 5 is not
// 2, 4, 8, 16, 32
// only one set bit. if more than one bit set, false
bool isPow2(int n)
{
    // using lookup method works
//    return n > 0 && count_set_bits(n) == 1 ? true: false;
    // but here using the brian-kernighan method is more efficient
    // because we only need to check for 1 set bit and if number becomes
    // zero, it is the only set bit.
    return n > 0 && (n & (n - 1)) == 0;
}


// find odd occurring integer i.e. the integer occuring odd times. 1, 3, 5 etc
int find_odd_occurring(vector<int> vec)
{
    // the unordered_map based solution has O(n) time and O(n) space complexity
    // create a map of number and its count O(n)
    // go through the map and return the first odd occuring element O(n)
//    std::unordered_map<int, int> counter;
//    
//    // O(n)
//    for (auto&& n : vec) {
//        counter[n]++; // O(1)
//    }
//    
//    // O(n)
//    for (auto&& pair : counter) {
////        cout << "Num : " << pair.first << ", count: " << pair.second << endl;
//        if (pair.second & 0x1 == 1) {
//            return pair.first;
//        }
//    }
    
    // efficient method of time complexity O(n) and auxillary space O(1)
    // use XOR operator
    // XOR operator properties
    // x ^ 0 = x
    // x ^ x = 0 (XOR of same pair results in 0)
    // x ^ y = y ^x (XOR is commutative)
    // x ^ (y ^ z) = (x ^ y) ^ z (XOR is associative)
    
    // based on above, just perform XOR of the whole vector, the even
    // occurences will cancel each other out and the remaining integer will be odd occuring
    
    int result = 0; // x ^ 0 = x
    
    for (int i = 0; i < vec.size(); i++) {
        result ^= vec[i];
    }
    
    return result;
}

// Given an array of n number that has values in range [1..n+1]. Every number appears
// exactly once. Hence one number is missing. Find the missing number.
// e.g arr[] = {1, 4, 3}, result = 2
int find_missing_number(vector<int> vec)
{
    int expected_chksum = 0;
    int chksum = 0;
    
    for (int i = 0; i < vec.size(); i++) {
        chksum ^= vec[i];
    }
    
    for (int i = 1; i <= vec.size() + 1; i++) {
        expected_chksum ^= i;
    }
    
    return chksum ^ expected_chksum; // pairs will cancel out, the odd occuring will remain
    
}

// find two odd occurring
vector<int> find_two_odd_occurring(vector<int> vec)
{
    vector<int> result;
    
    // maintain checksum for even and odd numbers
    int chksum_1st = 0; // would contain odd occuring even number
    int chksum_2nd = 0; // would contain odd occuring odd number
    int chksum = 0;
    
    for (int i = 0; i < vec.size(); i++) {
        chksum ^= vec[i];
    }
    
    // find the bit that separates 2 odd occurences
    int separator = chksum & ~(chksum - 1);
    
    for (int i = 0; i < vec.size(); i++) {
        if (vec[i] & separator)
            chksum_1st ^= vec[i];
        else
            chksum_2nd ^= vec[i];
    }
    // find the right-most set bit in the checksum, 
    // since only two numbers are odd, the rest cancel out
    // means chksum = x ^ y, the checksum bit set means the 
    // bit is set in one number and reset in another
    // e.g checksum of 14 and 16, two odd occuring numbers = 0x30
    // 14: 01110
    // 16: 10000
    // 30: 11110 ( right-most set bit is bit 1, so create a group based on the bit 1 being set)

    if (chksum_1st > 0)
        result.push_back(chksum_1st);
    
    if (chksum_2nd > 0)
        result.push_back(chksum_2nd);
        
    return result;
}

vector<std::string> create_powerset(string s)
{
    vector<string> result;
    
//    // naive : O(2^n) time, O(2^n) space
//    std::queue<string> q;
//    
//    
//    q.push("");
//    
//    for (auto&& c : s) {
//        int curSize = q.size();
//        for (int i = 0; i < curSize; i++) {
//            auto&& r = q.front();
//            q.pop();
//        
//            // add back with append
//            q.push(r + c);
//            // add anoter without append
//            q.push(r);
//        }
//    }
//    int size = q.size();
//    for (int i = 0; i < size; i++) {
//        result.push_back(q.front());
//        q.pop();
//    }
//
        // we know that there are 2^n subsets possible.
        // therefore, generate a counter with value from 0 to 2^n - 1
        // e.g for 3 elements, counter ranges from 
        // 0 : 0b000
        // 1 : 0b001
        // 7 : 0b111
        // i.e. subsets are            (0, 0, 0), (0, 0, 1), (0, 1, 0), (0, 1, 1), (1, 0, 0), (1, 0, 1), (1, 1, 0), (1, 1, 1)
        // see how this corresponds to     ""   ,    "c"   ,    "b"   ,    "bc"  ,    "a"   ,    "ac"  ,    "ab"  ,   "abc" 
        // so we can create the string subset by checking which bits are set in the binary representation of the counter value
        int n = s.length();
        int max_value = pow(2, n) - 1; // 2^n - 1
        
        // overall O(2^n * n) time, O(1) space
        for (int counter = 0; counter <= max_value; counter++) { // O(2^n)
            string str = "";
            // check which bits of the counter are set
            for (int pos = 0; pos < n; pos++) { // O(n)
                // append the character corresponding to a set bit
                if (counter & (1 << pos)) {
                    str += s[pos];
                }
            }
            
            result.push_back(str);
        }
        
        return result;
}

int align(int n, int alignment)
{   
    if (n > alignment)
        return n + (n % alignment);
    else {
        return n + (alignment % n);
    }
}

// align power of two
int align_pow2(int n, int pow2)
{
    int mask = (1 << pow2) - 1; // e.g 2^2 = 100 if a number is aligned, it last 2 bits must be 0

    // 100 -> 011
    // lets say 5, 1001 aligned to 4 is 8 -> 1000
    // 11 1011 aligned to 4 is 12 -> 1100
    // 11 + 4 is 15 1111, need to make last 2 bits 0 (100 alignment), use kernighan alogrithm
    
    return (n + mask) & ~(mask);
}

int countLongestSequenceZeroes(int n) {
    int count = 0;
    int max = 0;

    while (n > 0) {
        int bit = 0x1 & n;
        if (bit) {
            count = 0;
        } else {
            count++;
        }

        max = std::max(max, count);
        n >>= 1;
    }
    return max;
}
