#include <vector>

// Backtracking is relevant to problems where permutations are generated
// Adding a check in advance before making a permutations and so on
// cut downs the amount of work to be done.
// Make permutations of string exluding pattern "AB"
std::vector<std::string> PermutationsExcluding(std::string& s);