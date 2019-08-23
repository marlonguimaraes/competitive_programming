#include <bits/stdc++.h>

#define fori(i, ini, lim) for(int i = int(ini); i < int(lim); i++)
#define ford(i, ini, lim) for(int i = int(ini); i >= int(lim); i--)

#define debug(x) cout << "> " << #x << " = " << x << endl;
#define debug_at(arr, at) cout << "> " << #arr << "[" << at << "] = " << arr[at] << endl;
#define debug_pair(p) cout << "> " << #p << " = (" << p.first << ", " << p.second << ")" << endl;

using namespace std;

typedef long long ll;
typedef pair<int, int> ii;

const int ALPHABET_SIZE = 26;

inline int cint(char c) {
    return c - 'a';
}

struct TrieNode {
    TrieNode *child[ALPHABET_SIZE];
    string word;

    TrieNode() : child(), word() {}
};

class Trie {
private:

    void destroy(TrieNode *node) {
        if(node == nullptr) {
            return;
        }
        for(int i = 0; i < ALPHABET_SIZE; i++) {
            destroy(node->child[i]);
        }
        delete node;
    }

public:
    TrieNode *root;

    Trie() {
        root = new TrieNode;
    }

    inline void insert(const string &str) {
        TrieNode *node = root;
        for(const char &c : str) {
            const int id = cint(c);
            if(node->child[id] == nullptr) {
                node->child[id] = new TrieNode;
            }
            node = node->child[id];
        }
        node->word = str;
    }

    inline bool contains(const string &str) {
        TrieNode *node = root;
        for(const char &c : str) {
            const int id = cint(c);
            if(node->child[id] == nullptr) {
                return false;
            }
            node = node->child[id];
        }
        return node->word.size();
    }

    ~Trie() {
        destroy(root);
    }
};

int main() {

    const vector<string> dict = {
        "ab",
        "bb",
        "bbab",
        "cba",
        "cbb",
        "cbb",
    };

    const vector<pair<string, bool>> test_cases = {
        {"d", 0},
        {"efg", 0},
        {"ab", 1},
        {"bb", 1},
        {"bbab", 1},
        {"cba", 1},
        {"cbb", 2},
        {"a", 0},
        {"bba", 0},
        {"cbc", 0},
    };

    Trie trie = {};
    for(const string &str : dict) {
        trie.insert(str);
    }

    for(const auto &p : test_cases) {
        assert(trie.contains(p.first) == p.second);
    }
    cout << "ALL TESTS PASSED" << endl;

    return 0;
}
