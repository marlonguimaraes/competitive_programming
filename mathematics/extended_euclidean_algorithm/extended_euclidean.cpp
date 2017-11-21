typedef long long ll;
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
