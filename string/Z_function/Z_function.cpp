// SPOJ: NHAY - A Needle in the Haystack
#include <bits/stdc++.h>

#define fori(i, ini, lim) for(int i = int(ini); i < int(lim); i++)
#define ford(i, ini, lim) for(int i = int(ini); i >= int(lim); i--)

#define debug(x) cout << "> " << #x << " = " << x << endl;
#define debug_at(arr, at) cout << "> " << #arr << "[" << at << "] = " << arr[at] << endl;
#define debug_pair(p) cout << "> " << #p << " = (" << p.first << ", " << p.second << ")" << endl;

using namespace std;

inline vector<int> z_function(const string &s) {
    int n = s.size();
    vector<int> z(n);
    int l = 0;
    int r = 0;
    for(int i = 1; i < n; ++i) {
        if(i <= r) {
            z[i] = min(z[i - l], r - l + 1);
        }
        while((i + z[i]) < n and (s[i + z[i]] == s[z[i]])) {
            ++z[i];
        }
        if(r < (i + z[i] - 1)) {
            l = i;
            r = i + z[i] - 1;
        }
    }
    return z;
}

int n, m;
string pat, text;

// Z-function application: string matching
inline void solve() {
    vector<int> z = z_function(pat + "#" + text);
    fori(i, m + 1, z.size()) {
        if(z[i] == m) {
            int at = i - (m + 1);
            cout << at << "\n";
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);

    for(int t = 1; cin >> m; ++t) {
        cin >> pat;
        cin >> text;

        if(t > 1) cout << "\n";

        solve();
    }

	return 0;
}

