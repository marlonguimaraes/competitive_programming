#include <bits/stdc++.h>

#define fori(i, ini, lim) for(int i = int(ini); i < int(lim); i++)
#define ford(i, ini, lim) for(int i = int(ini); i >= int(lim); i--)

#define debug(x) cout << "> " << #x << " = " << x << endl;
#define debug_at(arr, at) cout << "> " << #arr << "[" << at << "] = " << arr[at] << endl;
#define debug_pair(p) cout << "> " << #p << " = (" << p.first << ", " << p.second << ")" << endl;

#define gcd __gcd

using namespace std;

typedef long long ll;
const ll INF = (1LL << 31) - 1;

const int N = 1e7;
const ll M = 1e10;

inline int randint() {
    int a = rand();
    a <<= 15;
    a += rand();
    return a;
}

inline ll randll() {
    ll a = randint();
    a <<= 30;
    a += randint();
    return a;
}

// returns a positive integer congruent to a mod m
ll mod(ll a, ll m) {
    a = a % m;
    while(a < 0) {
        a += m;
    }
    return a;
}

ll add(ll a, ll b, ll m) {
    a += b;
    if(a >= m) {
        a -= m;
    }
    return a;
}

// calculates (a * b) % m, 1 <= a, b, m <= 10^18, O(log(b))
ll mult(ll a, ll b, ll m) {
    a = mod(a, m);
    b = mod(b, m);
    if(b > a) swap(a, b);
    if(a <= INF) return (a * b) % m;

    ll res = 0;
    while(b) {
        if(b & 1) {
            res = add(res, a, m);
        }
        a = (2LL * a) % m;
        b >>= 1;
    }
    return res;
}

ll exp(ll a, ll b, const ll m) {
    ll res = 1;
    while(b) {
        if(b & 1LL) {
            res = mult(res, a, m);
        }
        b >>= 1;
        a = mult(a, a, m);
    }
    return res;
}

// miller rabin
inline bool probably_prime(ll n) {
    if(n <= 1) {
        return false;
    }
    if(!(n & 1)) {
        return n == 2;
    }
    ll d = n - 1;
    ll s = 0;
    while(!(d & 1)) {
        d >>= 1;
        s++;
    }
    bool ret = true;
    for(ll i = 3; i <= min(20LL, n - 1); i++) {
        bool cur = false;
        if(exp(i, d, n) == 1) {
            cur = true;
        }
        else {
            for(ll j = 0; j <= s - 1; j++) {
                if(exp(i, (1LL << j) * d, n) == n - 1) {
                    cur = true;
                    break;
                }
            }
        }
        ret *= cur;
    }
    return ret;
}

// Xk+1 = (Xk^2 + c) mod n
inline ll f(ll x, ll c, ll n) {
    x = mult(x, x, n);
    x = add(x, c, n);
    return x;
}

// You can run this funtion more than once since initial values are random.
ll rho(const ll &n) {
    if(n % 2 == 0) return 2;

    const ll c = mod(randll(), n);
    ll x = mod(randll(), n); // BE CAREFUL: RAND_MAX may be small
    ll y = x;

    ll d = 1;
    do {
        x = f(x, c, n);
        y = f(y, c, n);
        y = f(y, c, n);

        d = gcd(llabs(x - y), n);
    } while(d == 1 and x != y); // Floyd's cycle-finding algorithm.
    return d;
}

// Pollard's rho may be slow for big primes, so it's wiser to check if N is not a prime first.
// Also, if N is not very big (N <= 10^9) it may be faster to use a deterministic algorithm
void factorize(const ll &n, map<ll, int> &factors) {
    if(n == 1LL) {
        return;
    }
    if(probably_prime(n)) {
        factors[n]++;
    }
    else {
        const ll fac = rho(n);
        factorize(fac, factors);
        factorize(n / fac, factors);
    }
}

int main() {
    srand(time(NULL)); // IMPORTANT: don't forget this

    ll n;
    while(scanf("%lld", &n) == 1) {
        map<ll, int> factors;
        factorize(n, factors);

        ll res = 1;
        for(auto p : factors) {
            res = (res * (p.second + 1));
        }
        printf("%lld\n", res);
    }
    return 0;
}

