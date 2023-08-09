#include "trie.h"
#include <string>
#include <stack>
#include <utility>
#include <iostream>
#include <functional>

void Trie::Insert(const std::string &s)
{
    shared_ptr<TrieNode> curr = this->root;

    for (int i = 0; i < s.length(); i++)
    {
        int index = s[i] - 'a';
        if (curr->children[index] == nullptr)
        {
            // shared_ptr<TrieNode> node{new TrieNode};
            auto node = make_shared<TrieNode>();
            curr->children[index] = node;
        }
        curr = curr->children[index];
    }
    curr->isEnd = true;
}

bool Trie::Search(const std::string &s)
{
    shared_ptr<TrieNode> curr = this->root;

    for (const auto &c : s)
    {
        int index = c - 'a';
        if (curr->children[index] == nullptr)
        {
            return false;
        }
        else
        {
            curr = curr->children[index];
        }
    }

    return curr->isEnd;
}

void Trie::Delete(const std::string &s)
{
    shared_ptr<TrieNode> curr = this->root;
    stack<pair<shared_ptr<TrieNode>, int>> traversed;

    for (const auto &c : s)
    {
        int index = c - 'a';
        if (curr->children[index] == nullptr)
        {
            return;
        }
        else
        {
            traversed.push({curr, index});
            curr = curr->children[index];
        }
    }
    if (curr->isEnd)
    {
        curr->isEnd = false;

        /* found word, now delete children without further links */
        while (!traversed.empty())
        {
            auto &[parent, index] = traversed.top();
            traversed.pop();

            auto isPartOfAnotherWord = [](shared_ptr<TrieNode> node)
            {
                for (int i = 0; i < node->children.size(); i++)
                {
                    if (node->children[i] != nullptr)
                    {
                        return true;
                    }
                }
                return false;
            };

            auto node = parent->children[index];

            if (!isPartOfAnotherWord(node))
            {
                parent->children[index] = nullptr;
            }
        }
    }
}

vector<string> Trie::GetAllWords()
{
    vector<string> result;

    function<void(shared_ptr<TrieNode>, string)> helper = [&](shared_ptr<TrieNode> root, string s)
    {
        if (root->isEnd)
        {
            result.push_back(s);
        }

        for (int i = 0; i < root->children.size(); i++)
        {
            if (root->children[i] != nullptr)
            {
                char c = 'a' + i;
                helper(root->children[i], s + c);
            }
        }
    };

    helper(this->root, "");

    return result;
}

// Time O(mn), Space O(mn)
int CountDistinctRowsInBinaryMatrix(const vector<vector<int>> matrix)
{
    struct TrieNodeBinary
    {
        shared_ptr<TrieNodeBinary> children[2]{nullptr};
    };

    struct TrieBinary
    {
        shared_ptr<TrieNodeBinary> root{new TrieNodeBinary};

        bool InsertRow(vector<int> row)
        {
            shared_ptr<TrieNodeBinary> curr = this->root;
            bool isDistinct = false;

            for (int i = 0; i < row.size(); i++)
            { // for each row
                int index = row[i];
                if (curr->children[index] == nullptr)
                {
                    curr->children[index] = make_shared<TrieNodeBinary>();
                    isDistinct = true;
                }
                curr = curr->children[index];
            }
            return isDistinct;
        }
    };

    TrieBinary t;
    int count = 0;

    for (int i = 0; i < matrix.size(); i++)
    {
        bool isDistinct = t.InsertRow(matrix[i]);
        if (isDistinct)
            count++;
    }

    return count;
}
