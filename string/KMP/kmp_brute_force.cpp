#include <bits/stdc++.h>

#define fori(i, ini, lim) for(int i = int(ini); i < int(lim); i++)
#define ford(i, ini, lim) for(int i = int(ini); i >= int(lim); i--)

#define debug(x) cout << "> " << #x << " = " << x << endl;
#define debug_at(arr, at) cout << "> " << #arr << "[" << at << "] = " << arr[at] << endl;
#define debug_pair(p) cout << "> " << #p << " = (" << p.first << ", " << p.second << ")" << endl;

using namespace std;

int brute_force(const string &text, const string &pat) {
    int n = text.size();
    int m = pat.size();
    int occ = 0; // number ocurrences of pat in text
    if(m > n) {
        return occ;
    }

    int i = 0;
    while(i <= (n - m)) {
        int j = 0;
        for(j = 0; j < m; ++j) {
            if(text[i + j] != pat[j]) {
                break;
            }
        }
        if(j == m) {
            ++occ;
        }
    }
    return occ;
}

int main() {
    ios_base::sync_with_stdio(false);

	return 0;
}
