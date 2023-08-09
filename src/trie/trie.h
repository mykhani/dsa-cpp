#ifndef TRIE_H_
#define TRIE_H_

#include <vector>
#include <memory>

using namespace std;

/*
  Trie is efficient for the following operations on words in a
  dictionary:
  1. Search
  2. Insert
  3. Delete
  4. Prefix search (finding all words that begin with a prefix)
  5. Lexicographical ordering (alphabetical order) of words
*/

struct TrieNode
{
    vector<std::shared_ptr<TrieNode>> children; // for 26 lower-case alphabets
    bool isEnd{false};

    TrieNode() : children(26, nullptr) {}
};

class Trie
{
private:
    std::shared_ptr<TrieNode> root{make_shared<TrieNode>()};

public:
    void Insert(const std::string &s);
    bool Search(const std::string &s);
    void Delete(const std::string &s);
    vector<std::string> GetAllWords();
};

int CountDistinctRowsInBinaryMatrix(const vector<vector<int>> matrix);

#endif