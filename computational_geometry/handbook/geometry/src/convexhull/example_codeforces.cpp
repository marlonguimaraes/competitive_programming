#include <bits/stdc++.h>

#define fori(i, ini, lim) for(int i = int(ini); i < int(lim); i++)
#define ford(i, ini, lim) for(int i = int(ini); i >= int(lim); i--)

#define debug(x) cout << "> " << #x << " = " << x << endl;
#define debug_at(arr, at) cout << "> " << #arr << "[" << at << "] = " << arr[at] << endl;
#define debug_pair(p) cout << "> " << #p << " = (" << p.first << ", " << p.second << ")" << endl;

using namespace std;

typedef long long ll;
typedef pair<ll, ll> ii;

ll cross(const ii &O, const ii &A, const ii &B){
    return (A.first - O.first) * (B.second - O.second) - (A.second - O.second) * (B.first - O.first);
}

// Codeforces 166B (codeforces.com/problemset/problem/166/B)
// This variation accepts 3 or more collinear points on the same edge of the returned convex hull
vector<ii> convex_hull(vector<ii> P) {
    int n = P.size(),
        k=0;
    vector<ii> H(2 * n);
    sort(P.begin(), P.end());

    for(int i = 0; i < n; ++i) {
        while(k >= 2 && cross(H[k-2], H[k-1], P[i]) < 0) {
            k--;
        }
        H[k++] = P[i];
    }

    for(int i = n - 2, t = k + 1; i >= 0; --i) {
        while(k >= t && cross(H[k-2], H[k-1], P[i]) < 0) {
            k--;
        }
        H[k++] = P[i];
    }
    H.resize(k - 1);
    return H;
}



int main() {
    ios_base::sync_with_stdio(false);

    int n;
    cin >> n;
    vector<ii> A(n);
    vector<ii> all(n);
    fori(i, 0, n) {
        cin >> A[i].first >> A[i].second;
        all[i] = A[i];
    }

    int m;
    cin >> m;
    vector<ii> B(m);
    fori(i, 0, m) {
        cin >> B[i].first >> B[i].second;
        all.push_back(B[i]);
    }
    vector<ii> ch = convex_hull(all);
    sort(ch.begin(), ch.end());
    sort(A.begin(), A.end());
    cout << (ch == A ? "YES" : "NO") << '\n';

    return 0;
}
