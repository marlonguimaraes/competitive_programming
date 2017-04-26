//problem link: https://csacademy.com/contest/round-25/#task/min-ends-subsequence

#include <bits/stdc++.h>

#define fori(i, ini, lim) for(int i = int(ini); i < int(lim); i++)
#define ford(i, ini, lim) for(int i = int(ini); i >= int(lim); i--)

#define debug(x) cout << "> " << #x << " = " << x << endl;
#define debug_at(arr, at) cout << "> " << #arr << "[" << at << "] = " << arr[at] << endl;
#define debug_pair(p) cout << "> " << #p << " = (" << p.first << ", " << p.second << ")" << endl;

using namespace std;

const int N = 1e5 + 23;

int n;
int arr[N];
int ft[N];

inline int lsb(int i) {
    return (i & (-i));
}

inline void update(int i, int val) {
    while(i < N) {
        ft[i] += val;
        i += lsb(i);
    }
}

inline int sum(int i) {
    int res = 0;
    while(i) {
        res += ft[i];
        i -= lsb(i);
    }
    return res;
}

inline int solve() {
    fori(i, 1, n + 1) {
        update(i, 1);
    }

    int l = 1;
    int r = n;
    int ans = 0;
    while(l < r) {
        int mini = min(arr[l], arr[r]);
        int next = 2 + sum(mini - 1);
        ans = max(ans, next);

        if(arr[l] < arr[r]) {
            update(arr[l], -1);
            ++l;
        }
        else {
            update(arr[r], -1);
            --r;
        }
    }
    return ans;
}

int main() {
    ios_base::sync_with_stdio(false);

    cin >> n;

    fori(i, 1, n + 1)
        cin >> arr[i];

    int ans = solve();
    cout << ans << "\n";

	return 0;
}
