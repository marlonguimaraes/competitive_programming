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

const int N = 1e5 + 23;

inline int lsb(int i) {
    return (i & (-i));
}

inline void update(ll ft[N], int i,  ll val) {
    while(i < N) {
        ft[i] += val;
        i += lsb(i);
    }
}

inline void update(ll ft[N], int l, int r, ll val) {
    update(ft, l, val);
    update(ft, r + 1, -val);
}

inline ll query(ll ft[N], int i) {
    ll sum = 0;
    while(i > 0) {
        sum += ft[i];
        i -= lsb(i);
    }
    return sum;
}


int n, m, k;
ll arr[N];
iii queries[N];
ll apply[N], ft[N];

void print() {
    puts("\n\nAPPLY");
    fori(i, 1, m + 1) {
        debug_at(apply, i);
    }
}

int main() {

    scanf("%d %d %d", &n, &m, &k);

    fori(i, 1, n + 1) {
        scanf("%lld", &arr[i]);
    }

    fori(i, 1, m + 1) {
        int l, r, val;
        scanf("%d %d %d", &l, &r, &val);
        queries[i] = make_tuple(l, r, val);
    }

    fori(i, 0, k) {
        int a, b;
        scanf("%d %d", &a, &b);
        update(apply, a, b, 1);
    }
    fori(i, 1, m + 1) {
        ll count = query(apply, i);
        if(count) {
            int l, r;
            ll val;
            tie(l, r, val) = queries[i];

            update(ft, l, r, val * count);
        }
    }

    fori(i, 1, n + 1) {
        if(i > 1) {
            putchar(' ');
        }
        printf("%lld", arr[i] + query(ft, i));
    }
    puts("");

    return 0;
}
