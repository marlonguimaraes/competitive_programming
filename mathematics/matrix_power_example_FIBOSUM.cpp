// SPOJ: FIBOSUM

#include <bits/stdc++.h>

#define debug(x) cout << "> " << #x << " = " << x << endl;
#define debug_at(arr, at) cout << "> " << #arr << "[" << at << "] = " << arr[at] << endl;
#define debug_pair(p) cout << "> " << #p << " = (" << p.first << ", " << p.second << ")" << endl;

using namespace std;

typedef long long ll;
typedef vector<vector<ll> > matrix;

const ll MOD = 1e9 + 7;

inline ll add(ll a, ll b) {
    a += b;
    if(a >= MOD)
        a -= MOD;
    return a;
}

inline ll sub(ll a, ll b) {
    a -= b;
    if(a < 0)
        a += MOD;
    return a;
}

inline ll mult(ll a, ll b) {
    return (a * b) % MOD;
}

inline matrix mult(const matrix&A, const matrix& B) {
    const int n = A.size();
    const int p = A[0].size();
    const int m = B[0].size();

    matrix res(n, vector<ll>(m));
    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < m; ++j) {
            for(int k = 0; k < p; ++k) {
                ll next = mult(A[i][k], B[k][j]);
                res[i][j] = add(res[i][j], next);
            }
        }
    }
    return res;
}

inline matrix power(matrix A, int b) {
    matrix res(A.size(), vector<ll>(A.size()));
    for(int i = 0; i < (int) A.size(); ++i) res[i][i] = 1;

    while(b > 0) {
        if(b & 1)
            res = mult(res, A);
        A = mult(A, A);
        b >>= 1;
    }

    return res;
}

inline ll Sn(int n) {
    if(n == 1) return 0;

    matrix T = {{1, 1, 0},
                {0, 1, 1},
                {0, 1, 0}};
    matrix M = {{0},
                {1},
                {0}};
    matrix res = power(T, n - 1);
    res = mult(res, M);
    ll ans = res[0][0];
    
    return ans;
}

inline ll query(int a, int b) {
    ll res = Sn(b);
    if(a > 1)
        res = sub(res, Sn(a - 1));
    return res;
}

int main() {

    int tests;
    scanf("%d", &tests);

    for(int t = 1; t <= tests; ++t) {
        int a, b;
        scanf("%d %d", &a, &b);
        ++a;
        ++b;
        ll ans = query(a, b);
        printf("%lld\n", ans);
    }

	return 0;
}
