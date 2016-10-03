// SPOJ POSTERS - Election Posters

#include <bits/stdc++.h>

#define debug(x) cout << "> " << #x << " = " << x << endl;
#define debug_at(arr, at) cout << "> " << #arr << "[" << at << "] = " << arr[at] << endl;
#define debug_pair(p) cout << "> " << #p << " = (" << p.first << ", " << p.second << ")" << endl;

using namespace std;

typedef pair<int, int> ii;

const int N = 1e7 + 50;

inline int left(int i) { return 2 * i; }
inline int right(int i) { return left(i) + 1; }

struct Node {
    int value;
    int lazy;
    
    Node(int vvalue = 0, int llazy = 0) : value(vvalue), lazy(llazy) {}
};

int n;
Node st[4 * N];

inline void propagate(int p, int value, int l, int r) {
    if(l != r) {
        st[left(p)].lazy = value;
        st[right(p)].lazy = value;
    }
}

inline void update(int a, int b, int color, int p = 1, int l = 0, int r = n - 1) {
    if(st[p].lazy != 0) {
        st[p].value = st[p].lazy;
        propagate(p, st[p].value, l, r);
        st[p].lazy = 0;
    }

    if(r < a or b < l) {
        return;
    }
    if(l >= a and r <= b) {
        st[p].value = color;
        propagate(p, color, l, r);
    }
    else {
        int mid = (l + r) / 2;
        update(a, b, color, left(p), l, mid);
        update(a, b, color, right(p), mid + 1, r);
    }
}

inline int query(int i, int p = 1, int l = 0, int r = n - 1) {
    if(i < l or r < i) {
        return -1;
    }

    int &value = st[p].value;
    int &lazy = st[p].lazy;

    if(lazy != 0) {
        return lazy;
    }
    else if(l == r) {
        return value;
    }
    else {
        int mid = (l + r) / 2;
        int q1 = query(i, left(p), l, mid);
        int q2 = query(i, right(p), mid + 1, r);
        return max(q1, q2);
    }
}

inline int solve() {
    set<int> colors;
    for(int i = 0; i < n; ++i) {
        int color = query(i);
        colors.insert(color);
    }

    int size = colors.size();
    assert(size > 0);

    if(*colors.begin() == 0) {
        --size;
    }
    return size;
}

int main() {

    int tests;
    scanf("%d", &tests);

    for(int t = 1; t <= tests; ++t) {
        int qq;
        scanf("%d", &qq);

        vector<ii> queries;
        n = 0;
        for(int q = 0; q < qq; ++q) {
            int a, b;
            scanf("%d %d", &a, &b);
            queries.push_back(ii(a - 1, b - 1));

            n = max(n, b);
        }

        memset(st, 0, sizeof st);

        int color = 1;
        for(ii q : queries) {
            int a = q.first, b = q.second;
            update(a, b, color);
            color++;
        }

        int ans = solve();
        printf("%d\n", ans);
    }

	return 0;
}
