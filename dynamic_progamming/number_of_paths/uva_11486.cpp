#include <bits/stdc++.h>

#define fori(i, ini, lim) for(int i = int(ini); i < int(lim); i++)
#define ford(i, ini, lim) for(int i = int(ini); i >= int(lim); i--)

#define debug(x) cout << "> " << #x << " = " << x << endl;
#define debug_at(arr, at) cout << "> " << #arr << "[" << at << "] = " << arr[at] << endl;
#define debug_pair(p) cout << "> " << #p << " = (" << p.first << ", " << p.second << ")" << endl;

using namespace std;

const int N = 37;

inline int is(int mask, int i) {
    return mask & (1 << i);
}

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

inline matrix matrix_mult(const matrix &a, const matrix &b) {
    int n = a.size(),
        p = b[0].size(),
        m = a[0].size();
    matrix res(n, vector<ll>(p));
    
    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < p; ++j) {
            for(int k = 0; k < m; ++k) {
                ll sum = prod(a[i][k], b[k][j]);
                res[i][j] = add(res[i][j], sum);
            }
        }
    }
    return res;
}

inline matrix power(matrix a, ll b) {
    int n = a.size();
    matrix res(n, vector<ll>(n));
    for(int i = 0; i < n; ++i)
        res[i][i] = 1;
    while(b) {
        if(b & 1)
            res = matrix_mult(res, a);
        a = matrix_mult(a, a);
        b >>= 1;
    }
    return res;
}

inline void print(const matrix &B) {
    cout << "B =" << endl;
    for(vi vec : B) {
        for(ll k : vec) {
            cout << k << ' ';
        }
        cout << '\n';
    }
    cout << "\n";
}

map<int, vector<int> > mp;
map<int, int> id;

matrix M;
void gen_adj(const int source, const int cur, const int at) {
    if(at == 4) {
        if(mp.find(cur) != mp.end()) {
            M[id[source]][id[cur]] = 1;
        }
        return;
    }
    int bit = mp[source][at];
    if(bit < 6) {
        int add = cur | (1 << (bit + 1));
        if(add != cur) {
            gen_adj(source, add, at + 1);
        }
    }
    if(bit > 0) {
        int add = cur | (1 << (bit - 1));
        if(add != cur) {
            gen_adj(source, add, at + 1);
        }
    }
}

void gen() {
    M = matrix(N, vi(N));
    int available = 0;
    fori(i, 0, 1 << 7) {
        if(__builtin_popcount(i) == 4) {
            for(int j = 0; j < 7; ++j) {
                if(is(i, j)) {
                    mp[i].push_back(j);
                }
            }
            id[i] = available++;
        }
    }
    for(auto p : mp) {
        gen_adj(p.first, 0, 0);
    }
}

ll n;
ll solve(const vi &vec) {
    if(n == 1) {
        return 1;
    }

    matrix P = power(M, n - 1);

    ll ans = 0;
    int source = 0;
    fori(i, 0, 7) {
        if(vec[i]) {
            source |= (1 << (6 - i));
        }
    }
    int u = id[source];
    for(auto p : mp) {
        int v = id[p.first];
        ans = add(ans, P[u][v]);
    }
    return ans;
}

int main() {
    ios_base::sync_with_stdio(false);

    gen();
    int tests;
    cin >> tests;

    fori(t, 0, tests) {
        cin >> n;
        vector<ll> vec(7);
        for(ll &k : vec) {
            cin >> k;
        }
        ll ans = solve(vec);
        cout << ans << '\n';
    }

    return 0;
}
