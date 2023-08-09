#include <gtest/gtest.h>
#include <trie/trie.h>

TEST(Trie, TrieInsertAndSearchTest)
{
    Trie t;

    t.Insert("bad");
    t.Insert("bat");
    t.Insert("geek");
    t.Insert("geeks");
    t.Insert("cat");
    t.Insert("cut");
    t.Insert("zoo");

    EXPECT_EQ(t.Search("bad"), true);
    EXPECT_EQ(t.Search("bat"), true);
    EXPECT_EQ(t.Search("geek"), true);
    EXPECT_EQ(t.Search("gee"), false);
    EXPECT_EQ(t.Search("cater"), false);
}

TEST(Trie, TrieDeleteTest)
{
    Trie t;

    t.Insert("bad");
    t.Insert("bat");
    t.Insert("geek");
    t.Insert("geeks");
    t.Insert("cat");
    t.Insert("cut");
    t.Insert("zoo");

    t.Delete("bad");
    EXPECT_EQ(t.Search("bad"), false);

    EXPECT_EQ(t.Search("bat"), true);
    t.Delete("bat");
    EXPECT_EQ(t.Search("bat"), false);

    t.Delete("geek");
    EXPECT_EQ(t.Search("geek"), false);
    EXPECT_EQ(t.Search("geeks"), true);

    t.Delete("zoo");
    EXPECT_EQ(t.Search("zoo"), false);
}

TEST(Trie, TrieGetAllWordsTest)
{
    Trie t;

    t.Insert("bad");
    t.Insert("bat");
    t.Insert("geek");
    t.Insert("geeks");
    t.Insert("cat");
    t.Insert("cut");
    t.Insert("zoo");

    vector<string> result = t.GetAllWords();
    vector<string> expected{"bad", "bat", "cat", "cut", "geek", "geeks", "zoo"};

    EXPECT_EQ(result, expected);
}

TEST(Trie, CountDistinctRowsInBinaryMatrixTest)
{
    vector<vector<int>> matrix = {
        {1, 0, 0},
        {1, 1, 1},
        {1, 0, 0},
        {0, 1, 0}};

    int result = CountDistinctRowsInBinaryMatrix(matrix);

    EXPECT_EQ(result, 3);
}