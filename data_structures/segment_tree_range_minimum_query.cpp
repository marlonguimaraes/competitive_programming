/* Segment Tree represents the interval [0, n - 1] as a binary tree;
 * Each node represent some interval inside the array;
 * Node 1, the root is responsable for interval [0, n - 1]
 * consider some node p, responsable for interval [l, r]
 * if l == r, this node p is a leaf;
 * else, it's left childrem is node (2 * p), responsable for the interval (l, (l + r) / 2);
 * it's right childrem is node (2 * p + 1), responsable for the interval ((l + r) / 2 + 1, r);
 * that's the basic structre of segment tree.
 * the information that each node will keep depends on the nature of the problem

 * consider the RMQ (range minimum query) problem;
 * let p be the current node, responsable for interval [l, r];
 * the minimum element in the range is the minimum between it's twos childs;
 * 
 * The RSQ (range sum query) problem:
 * let p be the current node, responsable for interval [l, r];
 * the minimum element in the range is the sum of it's twos childs;
 */ 
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
    if(i > r or j < l) return -1;       // if this interval is completly outside, then there is no need to go deeper on this branch
    if(l >= i and r <= j) return st[p]; // if this interval is completly inside the range query, it's value is already known by the segment tree

                                        // in case of overlapping intervals, the search must continue;
                                        // the worst case scenario, the search will reach the leaf
    int p1 = rmq(left(p), l, (l + r) / 2, i, j);
    int p2 = rmq(right(p), (l + r) / 2 + 1, r, i, j);
    
    if(p1 == -1) return p2;
    if(p2 == -1) return p1;

    return (v[p1] >= v[p2]) ? p1 : p2;
}

int main() {

    int n, q;
    scanf("%d %d", &n, &q);

    for(int i = 0; i < n; ++i) scanf("%d", v + i);

    build(1, 0, n - 1);
    for(int i = 0; i < q; ++i) {
        int a, b;
        scanf("%d %d", &a, &b);
        printf("rmq(%d, %d) = %d\n", a, b, rmq(1, 0, n - 1, a, b));
    }

    return 0;
}
