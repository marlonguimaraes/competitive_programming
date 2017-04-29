#include <bits/stdc++.h>

#define fori(i, ini, lim) for(int i = int(ini); i < int(lim); i++)
#define ford(i, ini, lim) for(int i = int(ini); i >= int(lim); i--)

#define debug(x) cout << "> " << #x << " = " << x << endl;
#define debug_at(arr, at) cout << "> " << #arr << "[" << at << "] = " << arr[at] << endl;
#define debug_pair(p) cout << "> " << #p << " = (" << p.first << ", " << p.second << ")" << endl;

using namespace std;

typedef long long ll;

const int N = 123;

int n;
ll arr[N];

inline ll solve() {
    sort(arr, arr + n);
    ll res = 0;

    fori(i, 0, n - 2) {
        int k = i + 2;
        fori(j, i + 1, n - 1) {
            while((k < n) and ((arr[i] + arr[j]) > arr[k])) {
                ++k;
            }
            res += (k - j - 1);
        }
    }
    return res;
}

int main() {
    ios_base::sync_with_stdio(false);

    cin >> n;
    fori(i, 0, n)
        cin >> arr[i];

    ll ans = solve();
    cout << ans << "\n";

	return 0;
}
