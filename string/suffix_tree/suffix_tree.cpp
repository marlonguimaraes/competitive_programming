#include <bits/stdc++.h>

#define fori(i, ini, lim) for(int i = int(ini); i < int(lim); i++)
#define ford(i, ini, lim) for(int i = int(ini); i >= int(lim); i--)

#define debug(x) cout << "> " << #x << " = " << x << endl;
#define debug_at(arr, at) cout << "> " << #arr << "[" << at << "] = " << arr[at] << endl;
#define debug_pair(p) cout << "> " << #p << " = (" << p.first << ", " << p.second << ")" << endl;

using namespace std;

typedef long long ll;
typedef pair<int, int> ii;

const int N = 1e5;

map<int, char> trie[N];

inline bool add(const string &s, int &available) {
    int cur = 0;
    bool added = false;
    for(char c : s) {
        auto at = trie[cur].find(c);
        if(at != trie[cur].end()) {
            cur = at->second;
        }
        else {
            trie[cur][c] = available;
            cur = available;
            available++;
            added = true;
        }
    }
    return added;
}

inline bool present(const string &s) {
    int cur = 0;
    for(char c : s) {
        auto at = trie[cur].find(c);
        if(at != trie[cur].end()) {
            cur = at->second;
        }
        else {
            return false;
        }
    }
    return true;
}

inline void print(int cur, int level) {
    for(auto p : trie[cur]) {
        char c = p.first;
        int id = p.second;
        cout << string(2 * level, ' ');
        cout << c << '\n';
        print(id, level + 1);
    }
}

int main() {
    ios_base::sync_with_stdio(false);

    int n = 100;
    int m = 3;
    srand(time(nullptr));
    string str(n, 0);

    for(int i = 0; i < n; i++) {
        str[i] = 'a' + (rand() % 2);
    }
    debug(str);

    int available = 1;
    for(int i = n - m; i >= 0; i--) {
        string sub = str.substr(i, m);
        bool added = add(sub, available);
    }
    cout << "\n\n";
    cout << "suffix tree =\n";
    print(0, 0);

    return 0;
}
