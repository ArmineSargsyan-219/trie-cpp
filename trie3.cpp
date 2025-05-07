#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cctype>

const int ALPHABET_SIZE = 26;

class TrieNode {
public:
    TrieNode* children[ALPHABET_SIZE];
    bool isEndOfWord;

    TrieNode() {
        isEndOfWord = false;
        for (int i = 0; i < ALPHABET_SIZE; ++i)
            children[i] = nullptr;
    }

    ~TrieNode() {
        for (int i = 0; i < ALPHABET_SIZE; ++i)
            delete children[i];
    }
};

class Trie {
private:
    TrieNode* root;
    std::vector<std::string> words; 

public:
    Trie() {
        root = new TrieNode();
    }

    ~Trie() {
        delete root;
    }

    void insert(const std::string& word) {
        TrieNode* curr = root;
        for (char ch : word) {
            if (!std::isalpha(ch)) continue;
            int index = std::tolower(ch) - 'a';
            if (!curr->children[index])
                curr->children[index] = new TrieNode();
            curr = curr->children[index];
        }
        curr->isEndOfWord = true;
        words.push_back(word);
    }

    bool startsWith(const std::string& prefix) {
        TrieNode* curr = root;
        for (char ch : prefix) {
            if (!std::isalpha(ch)) return false;
            int index = std::tolower(ch) - 'a';
            if (!curr->children[index])
                return false;
            curr = curr->children[index];
        }
        return true;
    }

    void printShortestAndLongest() {
        if (words.empty()) {
            std::cout << "No words inserted.\n";
            return;
        }

        std::vector<std::string> shortest;
        std::vector<std::string> longest;

        int minLen = words[0].length();
        int maxLen = words[0].length();

        shortest.push_back(words[0]);
        longest.push_back(words[0]);

        for (size_t i = 1; i < words.size(); ++i) {
            int len = words[i].length();

            if (len < minLen) {
                minLen = len;
                shortest.clear();
                shortest.push_back(words[i]);
            } else if (len == minLen && shortest.size() < 2) {
                shortest.push_back(words[i]);
            }

            if (len > maxLen) {
                maxLen = len;
                longest.clear();
                longest.push_back(words[i]);
            } else if (len == maxLen && longest.size() < 2) {
                longest.push_back(words[i]);
            }
        }

        std::cout << "\nShortest word(s): ";
        for (const auto& word : shortest)
            std::cout << word << " ";

        std::cout << "\nLongest word(s): ";
        for (const auto& word : longest)
            std::cout << word << " ";

        std::cout << "\n";
    }
};

int main() {
    Trie trie;
    int n;

    std::cout << "Enter number of words: ";
    std::cin >> n;

    std::cout << "Enter the words:\n";
    for (int i = 0; i < n; ++i) {
        std::string word;
        std::cin >> word;
        trie.insert(word);
    }

    trie.printShortestAndLongest();

    return 0;
}
