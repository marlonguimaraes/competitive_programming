// Codeforces problem: (J) http://codeforces.com/gym/101490/attachments
#include <bits/stdc++.h>

#define fori(i, ini, lim) for(int i = int(ini); i < int(lim); i++)
#define ford(i, ini, lim) for(int i = int(ini); i >= int(lim); i--)

#define debug(x) cout << "> " << #x << " = " << x << endl;
#define debug_at(arr, at) cout << "> " << #arr << "[" << at << "] = " << arr[at] << endl;
#define debug_pair(p) cout << "> " << #p << " = (" << p.first << ", " << p.second << ")" << endl;

using namespace std;

typedef pair<int, int> ii;

inline int dist(ii a, ii b) {
    return abs(a.first - b.first) + abs(a.second - b.second);
}

const int N = 123;
ii arr[N];

bool vis[N];
int match[N];

int n;

int aug(int u, int m) {
    if(vis[u]) return 0;
    vis[u] = true;

    fori(v, n + 1, 1 + 2 * n) {
        int d = dist(arr[u], arr[v]);
        if((d <= m) and (match[v] == -1 or aug(match[v], m))) {
            match[v] = u;
            return 1;
        }
    }
    return 0;
}

inline bool can(int m) {
    memset(match, -1, sizeof match);
    int f = 0;
    fori(i, 1, n + 1) {
        memset(vis, 0, sizeof vis);
        f += aug(i, m);
    }
    return f == n;
}

int solve() {
    int l = 0;
    int r = 1e9;
    int res = 0;

    while(l <= r) {
        int mid = l + (r - l) / 2;
        if(can(mid)) {
            res = mid;
            r = mid - 1;
        }
        else {
            l = mid + 1;
        }
    }

    return res;
}

int main() {
    ios_base::sync_with_stdio(false);

    cin >> n;
    fori(i, 1, 1 + 2 * n) {
        cin >> arr[i].first >> arr[i].second;
    }

    int ans = solve();
    cout << ans << '\n';

    return 0;
}
