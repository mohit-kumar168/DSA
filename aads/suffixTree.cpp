// #include <cstddef> // for size_t
#include <iostream>
#include <string>
#include <unordered_map>

using namespace std;

struct TrieNode {
  unordered_map<char, TrieNode *> children;
  bool isEndOfSuffix;

  TrieNode() : isEndOfSuffix(false) {}
};

class SuffixTrie {
private:
  TrieNode *root;

public:
  SuffixTrie() { root = new TrieNode(); }

  // Insert a single suffix into the trie
  void insertSuffix(const string &suffix) {
    TrieNode *current = root;
    for (char c : suffix) {
      if (current->children.find(c) == current->children.end()) {
        current->children[c] = new TrieNode();
      }
      current = current->children[c];
    }
    current->isEndOfSuffix = true;
  }

  // Brute-force construction of suffix trie (O(n^2))
  void bruteForceSuffixTrie(const string &text) {
    for (size_t i = 0; i < text.size(); ++i) {
      insertSuffix(text.substr(i));
    }
  }

  // Search for a pattern in the trie
  bool search(const string &pattern) {
    TrieNode *current = root;
    for (char c : pattern) {
      if (current->children.find(c) == current->children.end())
        return false;
      current = current->children[c];
    }
    return true;
  }

  // Helper function to display suffixes recursively
  void display(TrieNode *node, string prefix) {
    if (node->isEndOfSuffix)
      cout << prefix << endl;

    for (auto &pair : node->children) {
      display(pair.second, prefix + pair.first);
    }
  }

  // Display all suffixes stored in the trie
  void displayAllSuffixes() {
    cout << "All suffixes stored in the Suffix Trie:\n";
    display(root, "");
  }
};

int main() {
  string text;
  cout << "Enter a string: ";
  cin >> text;

  SuffixTrie trie;
  trie.bruteForceSuffixTrie(text);

  cout << "\nSuffix Trie built using brute-force method.\n";
  trie.displayAllSuffixes();

  string pattern;
  cout << "\nEnter a pattern to search: ";
  cin >> pattern;

  if (trie.search(pattern))
    cout << "Pattern found in text.\n";
  else
    cout << "Pattern not found in text.\n";

  return 0;
}
