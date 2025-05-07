#include <iostream>
#include <memory>
#include <string>
using namespace std;

const int ALPHABET_SIZE = 26;

class TrieNode {
public:
    TrieNode* children[ALPHABET_SIZE];
    bool isEndOfWord;

    TrieNode() {
        isEndOfWord = false;
        for (int i = 0; i < ALPHABET_SIZE; i++)
            children[i] = nullptr;
    }

    ~TrieNode() {
        for (int i = 0; i < ALPHABET_SIZE; i++)
            delete children[i];
    }
};

class Trie {
private:
    TrieNode* root;

    bool deleteHelper(TrieNode* node, const string& key, int depth) {
        if (!node) return false;

        if (depth == key.length()) {
            if (!node->isEndOfWord) return false;
            node->isEndOfWord = false;

            for (int i = 0; i < ALPHABET_SIZE; i++)
                if (node->children[i]) return false;

            return true;
        }

        int index = key[depth] - 'a';
        if (deleteHelper(node->children[index], key, depth + 1)) {
            delete node->children[index];
            node->children[index] = nullptr;

            if (!node->isEndOfWord) {
                for (int i = 0; i < ALPHABET_SIZE; i++)
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

    void insert(const string& key) {
        TrieNode* curr = root;
        for (char ch : key) {
            if (!isalpha(ch)) continue; // Only lowercase letters
            int index = tolower(ch) - 'a';
            if (!curr->children[index])
                curr->children[index] = new TrieNode();
            curr = curr->children[index];
        }
        curr->isEndOfWord = true;
    }

    bool search(const string& key) {
        TrieNode* curr = root;
        for (char ch : key) {
            if (!isalpha(ch)) return false;
            int index = tolower(ch) - 'a';
            if (!curr->children[index])
                return false;
            curr = curr->children[index];
        }
        return curr->isEndOfWord;
    }

    void deleteWord(const string& key) {
        deleteHelper(root, key, 0);
    }
};

class TrieManager {
private:
    Trie trie;

    void insertWord() {
        string word;
        cout << "Enter word to insert: ";
        cin >> word;
        trie.insert(word);
        cout << "Inserted.\n";
    }

    void searchWord() {
        string word;
        cout << "Enter word to search: ";
        cin >> word;
        if (trie.search(word))
            cout << "Word found!\n";
        else
            cout << "Word NOT found!\n";
    }

    void deleteWord() {
        string word;
        cout << "Enter word to delete: ";
        cin >> word;
        trie.deleteWord(word);
        cout << "Deleted if existed.\n";
    }

public:
    void run() {
        int choice;
        while (true) {
            cout << "\n1. Insert\n2. Search\n3. Delete\n4. Exit\nEnter your choice: ";
            cin >> choice;

            switch (choice) {
                case 1: insertWord(); break;
                case 2: searchWord(); break;
                case 3: deleteWord(); break;
                case 4: cout << "Goodbye!\n"; return;
                default: cout << "Invalid choice. Try again.\n";
            }
        }
    }
};

int main() {
    TrieManager manager;
    manager.run();
    return 0;
}
