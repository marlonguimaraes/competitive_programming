// SPOJ GSS3 - Can you answer these queries III
#include <bits/stdc++.h>

#define debug(x) cout << "> " << #x << " = " << x << endl;
#define debug_at(arr, at) cout << "> " << #arr << "[" << at << "] = " << arr[at] << endl;
#define debug_pair(p) cout << "> " << #p << " = (" << p.first << ", " << p.second << ")" << endl;

using namespace std;

inline int pLeft(int i) { return (i << 1); }
inline int pRight(int i) { return (pLeft(i) + 1); }


typedef long long ll;

const int N = 50500;
const ll INF = -(1LL << 60); // Negative infinity.

struct Node {
    ll prefix,
       suffix,
       sum,
       best;

    Node(ll PREFIX = INF,
         ll SUFFIX = INF,
         ll SUM = INF,
         ll BEST = INF) : prefix(PREFIX),
                          suffix(SUFFIX),
                          sum(SUM),
                          best(BEST) {}
};


inline Node combine(Node left, Node right) {
    if(left.sum == INF) return right;
    if(right.sum == INF) return left;

    ll newPre = max(left.prefix, left.sum + right.prefix);
    ll newSuffix = max(right.suffix, right.sum + left.suffix);
    ll newSum = left.sum + right.sum;
    ll newBest = max({left.best, right.best, left.suffix + right.prefix});
    
    Node res(newPre, newSuffix, newSum, newBest);
    return res;
}

Node st[4 * N];
int arr[N];
int n;

inline void build(int p = 1, int l = 1, int r = n) {
    if(l == r) {
        st[p] = Node(arr[l], arr[l], arr[l], arr[l]);
        return;
    }

    int mid = (l + r) / 2;
    build(pLeft(p), l, mid);
    build(pRight(p), mid + 1, r);

    Node pl = st[pLeft(p)];
    Node pr = st[pRight(p)];
    st[p] = combine(pl, pr);
}

inline Node query(const int a, const int b, int p = 1, int l = 1, int r = n) {
    if(r < a or b < l) return Node();
    if(a <= l and r <= b) return st[p];

    int mid = (l + r) / 2;
    Node pl = query(a, b, pLeft(p), l, mid);
    Node pr = query(a, b, pRight(p), mid + 1, r);

    Node res = combine(pl, pr);
    return res;
}

inline void update(const int at, int p = 1, int l = 1, int r = n) {
    if(at < l or at > r) return;

    if(l == r) {
        st[p] = Node(arr[l], arr[l], arr[l], arr[l]);
    }
    else {
        int mid = (l + r) / 2;
        update(at, pLeft(p), l, mid);
        update(at, pRight(p), mid + 1, r);

        Node pl = st[pLeft(p)];
        Node pr = st[pRight(p)];
        st[p] = combine(pl, pr);
    }
}

int main() {

    scanf("%d", &n);
    for(int i = 1; i <= n; ++i)
        scanf("%d", arr + i);

    build();

    int queries;
    scanf("%d", &queries);
    for(int q = 1; q <= queries; ++q) {
        int type;
        scanf("%d", &type);

        if(type == 0) { // Makes arr[at] = newVal
            int at, newVal;
            scanf("%d %d", &at, &newVal);
            arr[at] = newVal;
            update(at);
        }
        else { // Maximum Subarray sum inside [a, b]
            int a, b;
            scanf("%d %d", &a, &b);
            Node res = query(a, b);
            ll ans = res.best;

            printf("%lld\n", ans);
        }
    }

	return 0;
}
