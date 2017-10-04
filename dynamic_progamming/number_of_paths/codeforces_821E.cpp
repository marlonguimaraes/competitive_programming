#include <bits/stdc++.h>

#define fori(i, ini, lim) for(int i = int(ini); i < int(lim); i++)
#define ford(i, ini, lim) for(int i = int(ini); i >= int(lim); i--)

#define debug(x) cout << "> " << #x << " = " << x << endl;
#define debug_at(arr, at) cout << "> " << #arr << "[" << at << "] = " << arr[at] << endl;
#define debug_pair(p) cout << "> " << #p << " = (" << p.first << ", " << p.second << ")" << endl;

using namespace std;

typedef long long ll;
typedef vector<ll> vi;
typedef vector<vi> matrix;

const ll MOD = 1e9 + 7;

inline ll add(ll a, ll b) {
    a += b;
    if(a >= MOD)
        a -= MOD;
    return a;
}

inline ll prod(ll a, ll b) {
    return (a * b) % MOD;
}

const int N = 17;

inline matrix mult(const matrix &a, const matrix &b) {
    matrix res(N, vi(N));
    fori(i, 0, N) {
        fori(j, 0, N) {
            fori(k, 0, N) {
                ll sum = prod(a[i][k], b[k][j]);
                res[i][j] = add(res[i][j], sum);
            }
        }
    }
    return res;
}

inline matrix power(matrix a, ll b) {
    matrix res(N, vi(N));
    fori(i, 0, N) {
        res[i][i] = 1;
    }
    while(b > 0) {
        if(b & 1) {
            res = mult(res, a);
        }
        a = mult(a, a);
        b >>= 1;
    }
    return res;
}

void print(const matrix &M) {
    fori(i, 0, N) {
        fori(j, 0, N) {
            cout << M[i][j] << ' ';
        }
        cout << '\n';
    }
    cout << "\n";
}

ll k;
matrix M;

inline void update(int c = 0) {
    fori(i, 0, N) {
        if(i) {
            M[i][i - 1] = 1;
        }
        if((i + 1) < N) {
            M[i][i + 1] = 1;
        }
        M[i][i] = 1;
    }
    fori(i, 0, N) {
        fori(j, 0, N) {
            if(i > c or j > c) {
                M[i][j] = 0;
            }
        }
    }
}

matrix res;
void init() {
   M = matrix(N, vi(N));
   res = M;
   fori(i, 0, N) {
       res[i][i] = 1;
   }
}

int main() {
    ios_base::sync_with_stdio(false);

    init();

    int n;
    cin >> n >> k;
    ll acc = 0;
    fori(i, 0, n) {
        ll a, b, c;
        cin >> a >> b >> c;
        if(acc == k) {
            continue;
        }

        update(c);

        ll diff = b - a;
        if((acc + diff) > k) {
            diff = (k - acc);
        }

        matrix P = power(M, diff);
        res = mult(res, P);
        acc += diff;
    }

    ll ans = res[0][0];
    cout << ans << "\n";

    return 0;
}
