// SPOJ - RANGESUM
#include <bits/stdc++.h>

#define debug(x) cout << "> " << #x << " = " << x << endl;
#define debug_at(arr, at) cout << "> " << #arr << "[" << at << "] = " << arr[at] << endl;
#define debug_pair(p) cout << "> " << #p << " = (" << p.first << ", " << p.second << ")" << endl;

using namespace std;

typedef long long ll;

const int N = 1e5 + 23;
const int M = 2 * N + 23;

inline int lsb(int i) {
    return (i & (-i));
}

int first;
inline int ith(int i) {
    return first + i - 1;
}

int n;

ll ft[M];

inline ll sum(int b) {
    ll res = 0LL;
    while(b) {
        res += ft[b];
        b -= lsb(b);
    }
    return res;
}

inline ll sum(int a, int b) {
    return sum(b) - sum(a - 1);
}

inline void update(int i, ll k) {
    while(i < M) { ft[i] += k; i += lsb(i);
    }
}

inline void add(ll k) {
    --first;
    update(first, k);
}

int main() {

    first = N + 1;

    scanf("%d", &n);
    for(int i = 1; i <= n; ++i) {
        ll next;
        scanf("%lld", &next);

        update(ith(i), next);
    }

    int queries;
    scanf("%d", &queries);
    for(int q = 1; q <= queries; ++q) {
        int op;
        scanf("%d", &op);

        if(op == 1) {
            int a, b;
            scanf("%d %d", &a, &b);

            a = ith(a);
            b = ith(b);
            ll ans = sum(a, b);
            printf("%lld\n", ans);
        }
        else {
            ll k;
            scanf("%lld", &k);
            add(k);
        }
    }

	return 0;
}
