#include <iostream>
#include <string>
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

    bool deleteHelper(TrieNode* node, const std::string& key, int depth) {
        if (!node) return false;

        if (depth == key.length()) {
            if (!node->isEndOfWord) return false;
            node->isEndOfWord = false;

            for (int i = 0; i < ALPHABET_SIZE; ++i)
                if (node->children[i]) return false;

            return true;
        }

        int index = std::tolower(key[depth]) - 'a';
        if (deleteHelper(node->children[index], key, depth + 1)) {
            delete node->children[index];
            node->children[index] = nullptr;

            if (!node->isEndOfWord) {
                for (int i = 0; i < ALPHABET_SIZE; ++i)
                    if (node->children[i]) return false;
                return true;
            }
        }
        return false;
    }

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
    }

    bool search(const std::string& word) {
        TrieNode* curr = root;
        for (char ch : word) {
            if (!std::isalpha(ch)) return false;
            int index = std::tolower(ch) - 'a';
            if (!curr->children[index])
                return false;
            curr = curr->children[index];
        }
        return curr->isEndOfWord;
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

    void deleteWord(const std::string& word) {
        deleteHelper(root, word, 0);
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

    int q;
    std::cout << "\nEnter number of queries (prefix checks): ";
    std::cin >> q;

    std::cout << "Enter the prefixes:\n";
    for (int i = 0; i < q; ++i) {
        std::string prefix;
        std::cin >> prefix;
        if (trie.startsWith(prefix))
            std::cout << "YES: At least one word starts with \"" << prefix << "\"\n";
        else
            std::cout << "NO: No word starts with \"" << prefix << "\"\n";
    }

    return 0;
}
