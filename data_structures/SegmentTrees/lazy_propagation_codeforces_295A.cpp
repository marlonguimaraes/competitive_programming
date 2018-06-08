// Problem link: http://codeforces.com/contest/295/problem/A
#include <bits/stdc++.h>

#define fori(i, ini, lim) for(int i = int(ini); i < int(lim); i++)
#define ford(i, ini, lim) for(int i = int(ini); i >= int(lim); i--)

#define debug(x) cout << "> " << #x << " = " << x << endl;
#define debug_at(arr, at) cout << "> " << #arr << "[" << at << "] = " << arr[at] << endl;
#define debug_pair(p) cout << "> " << #p << " = (" << p.first << ", " << p.second << ")" << endl;

using namespace std;

typedef long long ll;
typedef pair<int, int> ii;
typedef tuple<int, int, ll> iii;

inline int left(int i) {
    return 2 * i;
}

inline int right(int i) {
    return left(i) + 1;
}

const int N = 1e5 + 23;
const int M = 4 * N;

int n, m, k;
iii queries[N];

void print(int p, int l, int r) {
    debug(p);
    debug(l);
    debug(r);
    puts("\n\n");
}

inline void check(ll st[M], ll lazy[M], int p, int l, int r) {
    if(lazy[p]) {
        st[p] += (lazy[p] * (ll)(r - l + 1LL));
        if(l != r) {
            lazy[left(p)] += lazy[p];
            lazy[right(p)] += lazy[p];
        }
        lazy[p] = 0;
    }
}


inline void update(ll st[M], ll lazy[M],
                   const int a, const int b, const ll val,
                   const int p = 1, const int l = 1, const int r = N - 1) {
    check(st, lazy, p, l, r);
    if(r < a or b < l) return;

    if(l >= a and r <= b) {
        lazy[p] = val;
        check(st, lazy, p, l, r);
    }
    else {
        int mid = (l + r) / 2;
        update(st, lazy, a, b, val,
               left(p), l, mid);
        update(st, lazy, a, b, val,
               right(p), mid + 1, r);
    }
}

inline ll query(ll st[M], ll lazy[M],
                   const int a, const int b,
                   const int p = 1, const int l = 1, const int r = N - 1) {
    check(st, lazy, p, l, r);
    ll res = 0;
    if(r < a or b < l) return res;

    if(l >= a and r <= b) {
        res = st[p];
    }
    else {
        int mid = (l + r) / 2;
        res += query(st, lazy, a, b,
               left(p), l, mid);
        res += query(st, lazy, a, b,
               right(p), mid + 1, r);
    }
    return res;
}

ll arr[N];
ll apply[M], apply_lazy[M];
ll st[M], st_lazy[M];

int main() {

    scanf("%d %d %d", &n, &m, &k);
    fori(i, 1, n + 1) {
        scanf("%lld", &arr[i]);
    }
    fori(i, 1, m + 1) {
        int l, r;
        ll val;
        scanf("%d %d %lld", &l, &r, &val);

        queries[i] = make_tuple(l, r, val);
    }
    fori(i, 1, k + 1) {
        int a, b;
        scanf("%d %d", &a, &b);

        update(apply, apply_lazy, a, b, 1);
    }
    fori(i, 1, m + 1) {
        ll count = query(apply, apply_lazy, i, i);
        int l, r;
        ll val;
        tie(l, r, val) = queries[i];

        ll add = count * val;
        update(st, st_lazy, l, r, add);
    }

    fori(i, 1, n + 1) {
        ll ans = arr[i] + query(st, st_lazy, i, i);
        if(i > 1) putchar(' ');
        printf("%lld", ans);
    }
    puts("");

    return 0;
}
