#include <bits/stdc++.h>

#define debug(x) cout << "> " << #x << " = " << x << endl;
#define debugat(arr, at) cout << "> " << #arr << "[" << at << "] = " << arr[at] << endl;
#define debugpair(p) cout << "> " << #p << " = " << "(" << p.first << ", " << p.second << ")" << endl;

using namespace std;

typedef long long ll;

const int MOD = 1000000007LL; 

inline ll add(ll a, ll b) {
    a += b;
    if(a >= MOD)
        a -= MOD;
    return a;
}

inline ll mult(ll a, ll b) {
    return (a * b) % MOD;
}

inline ll power(ll a, ll b) {
    ll res = 1LL;
    while(b > 0LL) {
        if(b & 1)
            res = mult(res, a);
        b >>= 1LL;
        a = mult(a, a);
    }
    return res;
}

inline ll mod_inverse(ll a) {
    return power(a, MOD - 2LL);
}

int main() {
    ios_base::sync_with_stdio(false);
    ll a, b;
    while(cin >> a >> b) {
        cout << power(a, b) << "\n";
    }
    return 0;
}
