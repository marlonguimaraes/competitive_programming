#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<ll, ll> ii;

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

/*
** There will be infinitely many or zero solutions:
** Zero: d is set to -1 (d = -1)
** Infinitely: a particular solution is returned (x', y')
** The set of all solutions (x, y) is difined by:
** x = x' + (b / d) * t
** y = y' - (a / d) * t
** where t is any arbitrary integer
*/

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

int main() {
    return 0;
}
