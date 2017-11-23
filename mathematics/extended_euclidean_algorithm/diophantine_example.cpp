// UVA: 10090
#include <bits/stdc++.h>

#define fori(i, ini, lim) for(int i = int(ini); i < int(lim); i++)
#define ford(i, ini, lim) for(int i = int(ini); i >= int(lim); i--)

#define debug(x) cout << "> " << #x << " = " << x << endl;
#define debug_at(arr, at) cout << "> " << #arr << "[" << at << "] = " << arr[at] << endl;
#define debug_pair(p) cout << "> " << #p << " = (" << p.first << ", " << p.second << ")" << endl;

using namespace std;

typedef long long ll;
typedef pair<ll, ll> ii;

const ll INF = 1LL << 60;

ll ext_gcd(const ll &a, const ll &b, ll &x, ll &y) {
    if(b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    ll x1, y1;
    ll g = ext_gcd(b, a % b, x1, y1);

    const ll q = a / b;
    x = y1;
    y = x1 - y1 * q;
    return g;
}

// If there's no solution, d = -1
inline ii dio(const ll &a, const ll &b, const ll &c, ll &d) {
    ll x0, y0;
    d = ext_gcd(a, b, x0, y0);
    if(c % d) {
        d = -1;
        return ii(0, 0);
    }
    const ll t = c / d;
    return ii(x0 * t, y0 * t);
}

ll n;
ll c[3], m[3];

inline ll cost(ll x, ll y) {
    return x * c[0] + y * c[1];
}

inline ll gety(ll y0, ll d, ll t) {
    return y0 - (m[0] / d) * t;
}

inline ll getx(ll x0, ll d, ll t) {
    return x0 + (m[1] / d) * t;
}

inline ii get_min(ii xy, ll d, ll a, ll b) {
    ll x1 = getx(xy.first, d, a);
    ll y1 = gety(xy.second, d, a);

    ll x2 = getx(xy.first, d, b);
    ll y2 = gety(xy.second, d, b);
    ii res(x1, y1);
    if(cost(x1, y1) > cost(x2, y2)) {
        res = ii(x2, y2);
    }
    return res;
}

inline ii solve() {
    ll d;
    ii xy = dio(m[0], m[1], n, d);
    ii res(-1, -1);
    if(d < 1) {
        return res;
    }
    ll a = ceil(((double) (-xy.first * d)) / m[1]);
    ll b = floor(((double) (xy.second * d)) / m[0]);
    if(a > b) {
        return res;
    }
    return get_min(xy, d, a, b); 
}

int main() {

    while(scanf("%lld", &n), n) {
        fori(i, 0, 2) {
            scanf("%lld %lld", &c[i], &m[i]);
        }
        ii ans = solve();
        if(ans.first != -1) {
            printf("%lld %lld\n", ans.first, ans.second);
        }
        else {
            puts("failed");
        }
    }

    return 0;
}
