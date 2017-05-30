// SPOJ: NHAY - A Needle in the Haystack
#include <bits/stdc++.h>

#define fori(i, ini, lim) for(int i = int(ini); i < int(lim); i++)
#define ford(i, ini, lim) for(int i = int(ini); i >= int(lim); i--)

#define debug(x) cout << "> " << #x << " = " << x << endl;
#define debug_at(arr, at) cout << "> " << #arr << "[" << at << "] = " << arr[at] << endl;
#define debug_pair(p) cout << "> " << #p << " = (" << p.first << ", " << p.second << ")" << endl;

using namespace std;

string text;
string pat;
int n, m;

inline vector<int> build_borders() {
    vector<int> borders(m + 1);
    borders[0] = -1;

    int i = 0;
    int b = -1;
    while(i < m) {
        while((b >= 0) and pat[i] != pat[b]) {
            b = borders[b];
        }
        ++i;
        ++b;
        borders[i] = b;
    }
    return borders;
}

inline void kmp() {
    n = text.size();
    m = pat.size();
    if(m > n) return;

    vector<int> border = build_borders();
    int i = 0;
    int j = 0;
    while(i <= (n - m)) {
        while(j < m and pat[j] == text[i + j]) {
            ++j;
        }
        if(j == m) {
            cout << i << "\n";
        }
        i += (j - border[j]);
        j = max(border[j], 0);
    }
}

int main() {
    ios_base::sync_with_stdio(false);

    for(int t = 1; cin >> m; ++t) {
        cin >> pat;
        cin >> text;

        if(t > 1) cout << "\n";
        kmp();
    }

	return 0;
}
