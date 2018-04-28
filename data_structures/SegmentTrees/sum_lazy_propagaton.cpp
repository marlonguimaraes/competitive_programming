#include <bits/stdc++.h> 
#define fori(i, ini, lim) for(int i = int(ini); i < int(lim); i++)
#define ford(i, ini, lim) for(int i = int(ini); i >= int(lim); i--)

#define debug(x) cout << "> " << #x << " = " << x << endl;
#define debug_at(arr, at) cout << "> " << #arr << "[" << at << "] = " << arr[at] << endl;
#define debug_pair(p) cout << "> " << #p << " = (" << p.first << ", " << p.second << ")" << endl;

using namespace std;

const int N = 1000050;

bool start[N];
int st[4 * N];
int lazy[4 * N];

inline void init() {
    memset(st, 0, sizeof st);
    memset(lazy, 0, sizeof lazy);
    memset(start, 0, sizeof start);
}

inline int left(int i) { return 2 * i; }
inline int right(int i) { return 1 + left(i); }

inline int len(int l, int r) {
    return (r - l + 1);
}

inline void propagate(int p, int l, int r) {
    if(lazy[p]) {
        st[p] += (lazy[p] * len(l, r));
        if(l != r) {
            lazy[left(p)] += lazy[p];
            lazy[right(p)] += lazy[p];
        }
        lazy[p] = 0;
    }
}

int query(int a, int b, int p = 1, int l = 0, int r = N - 1) {
    propagate(p, l, r);
    if(r < a or b < l) return 0;
    if(a <= l and r <= b) return st[p];

    int mid = (l + r) / 2;
    int ll = query(a, b, left(p), l, mid);
    int rr = query(a, b, right(p), mid + 1, r);
    return ll + rr;
}

void update(int a, int b, int p = 1, int l = 0, int r = N - 1) {
    propagate(p, l, r);
    if(r < a or b < l) return;
    if(a <= l and r <= b) {
        lazy[p] += 1;
        propagate(p, l, r);
        return;
    }

    int mid = (l + r) / 2;
    update(a, b, left(p), l, mid);
    update(a, b, right(p), mid + 1, r);
    st[p] = st[left(p)] + st[right(p)];
}

inline bool check_update(int a, int b) {
    if(start[a]) return false;
    if(query(a, b) > 0) return false;
    if((b - a) > 1) {
        update(a + 1, b - 1);
    }
    return true;
}

inline void print() {
    int n = 33;
    fori(i, 0, n) {
        printf("%3d", i);
    }
    puts("");

    fori(i, 0, n) {
        printf("%3d", query(i, i));
    }
    puts("");
}

const int M = 1000000;

int main() {

    int n, m;
    int test = 1;
    while(scanf("%d %d", &n, &m), n | m) {
  //      printf("%d %d\n", n, m);
        init();
        bool ans = true;
        fori(i, 0, n) {
            int a, b;
            scanf("%d %d", &a, &b);
 //           printf("%d %d\n", a, b);

            ans = ans and check_update(a, b);
            start[a] = 1;
        }

        fori(i, 0, m) {
            int a, b, l;
            scanf("%d %d %d", &a, &b, &l);
//            printf("%d %d %d\n", a, b, l);

            while(ans and a <= (M)) {
                ans = ans and check_update(a, b);
                start[a] = 1;
                a += l;
                b += l;
                if(b > M) b = M;
            }
        }
        puts(ans ? "NO CONFLICT" : "CONFLICT");
        //print();
        //puts("\n");
        //if(test == 55) {
        //    assert(0);
        //}
        test++;
    }

    return 0;
}
