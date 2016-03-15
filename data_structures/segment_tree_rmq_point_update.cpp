#include <bits/stdc++.h>

#define debug(x) cout << "> " << #x << " = " << x << endl;

using namespace std;

const int N = 1234;

int v[N], st[4 * N];

int n;
int left (int p) { return p << 1; }
int right(int p) { return (p << 1) + 1; }


void build(int p, int l, int r) {
    if(l == r) {
        st[p] = l;
    }
    else {
        build(left(p), l, (l + r) / 2);
        build(right(p), (l + r) / 2 + 1, r);
        int p1 = st[left(p)], p2 = st[right(p)];
        st[p] = (v[p1] >= v[p2]) ? p1 : p2;
    }
}

int rmq(int p, int l, int r, int i, int j) {
    if(i > r or j < l) return -1;
    if(l >= i and r <= j) return st[p];

    int p1 = rmq(left(p), l, (l + r) / 2, i, j);
    int p2 = rmq(right(p), (l + r) / 2 + 1, r, i, j);
    
    if(p1 == -1) return p2;
    if(p2 == -1) return p1;

    return (v[p1] >= v[p2]) ? p1 : p2;
}

void update(int a, int val, int p, int l, int r) { // change element in poistion 'a' to 'val'
    if(l > a or r < a) {                           // going deeper on this node will never reach the node responsable for index a
        return;
    }
    if(l == r) {                                   // this node is definetly responsable for index a;
        v[a] = val;                                // change the element in the original array;
    }
    else {
        update(a, val, left(p), l, (l + r) / 2);
        update(a, val, right(p), (l + r) / 2 + 1, r);
        int p1 = st[left(p)], p2 = st[right(p)];
        st[p] = (v[p1] >= v[p2]) ? p1 : p2;        // since the array is already updated, we can "use" it's value in the array
    }
}

int main() {

    int n, q;
    scanf("%d %d", &n, &q);

    for(int i = 0; i < n; ++i) scanf("%d", v + i);

    build(1, 0, n - 1);

    update(3, 30, 1, 0, n - 1);

    for(int i = 0; i < q; ++i) {
        int a, b;
        scanf("%d %d", &a, &b);
        printf("rmq(%d, %d) = %d\n", a, b, rmq(1, 0, n - 1, a, b));
    }

    return 0;
}
