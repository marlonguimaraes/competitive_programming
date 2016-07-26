#include <bits/stdc++.h>

#define debug(x) cout << "> " << #x << " = " << x << endl;
#define debugat(arr, at) cout << "> " << #arr << "[" << at << "] = " << arr[at] << endl;
#define debugpair(p) cout << "> " << #p << " = " << "(" << p.first << ", " << p.second << ")" << endl;

using namespace std;

// LCA - Lowest Common Ancestor;
// LCA(u, v) = deepest (farest from the root) node such that u and v are descendants;
// we define parent[u] as u's father, and parent[root] == root;
// we define height[u] as u's height in the tree;

// for queries LCA(u, v)
// if height[u] == height[v]:
// we can prove that LCA(u, v) = ancestor(u, x) = ancestor(v, x) for minimum x in interval[0, height[u]], 
// ancestor(u, k) = k'th ancestor of u.

// if u == v, we have x = 0, which is minimum in interval, lca(u, v) if u == v is u;
// if u != v but height[u] == height[v]
// we can add 1 to x and check if ancestor(u, x) == ancestor(v, x). The first x that equation true is the value we're looking for.
// proof is by contradiction;
// we shall then meta-binary-search x's value;

// If height[u] != height[v], assuming height[u] < height[v]:
// there is some k such that height[v] - l = height[u];
// we shall then meta-binary-search k's value;

// let's define P[i][j] as the 2 ^ (j) ancestor of node i;
// note that P[i][0] = P[i][2 ^ 0] = P[i][1] = parent[i];
// Using the fact that 2 ^ (n - 1) + 2 ^ (n - 1) = 2 ^ n
// we can write P[i][j] = P[P[i][j - 1][j - 1] since P[i][j - 1] points to the 2 ^ (j - 1) ancestor, and doing the same for that ancestor,
// we point to P[i][j];

// To finally calculate LCA(u, v) such that height[u] == height[v] we make some observations;
// LCA(u, v) = ancestor(u, x) = ancestor(v, x) for minimum x;
// To calculate x we'll use pre-calculated values for P[u][i] being the 2 ^ i'th ancestor of u;
/*
 *   for(i = log2(height[u]); i >= 0; --i) {
 *       if(P[u][i] != P[v][i]) {            // If P[u][i] == P[v][i] we probably took a node much higher in the tree;
 *            u = P[u][i];                   // Which is probably not the actual LCA(u, v);
 *            v = P[v][i];                   // Note that for bigger values of i, P[u][i] will still be equal to P[u][i],
 *                                           // since we're taking an even higher ancestor, so we don't need to verify bigger values of i;
 *                                           // If P[u][i] != P[v][i] them we definetly can go 2 ^ i nodes higher in the tree, and it wont
 *                                           // be an ancestor of both u and v;
 *                                           // We can reach P[u][i] == P[v][i] eventually for some i because we're lookin for x in ancestor(u, x)
 *                                           // There is always a solution, and since x is in a integer, it can be represented as sum of
 *                                           // powers of two. When we make u = P[u][i] we're acctualy subtracting a power of two (2 ^ i)
 *                                           // in the initial value of x, trying it to make it smaller as possible.
 *       }
 *   }
 */

const int N = 123456;
const int LOG_N = log2(N);

int parent[N], P[N][LOG_N], height[N];

vector<vector<int> > adj;

inline void bfs_height(int root) {
    memset(height, -1, sizeof height);
    height[root] = 0;

    queue<int> q;
    q.push(root);
    parent[root] = root;

    while(!q.empty()) {
        int u = q.front();
        q.pop();
        for(int v : adj[u]) {
            if(height[v] == -1) {
                height[v] = height[u] + 1;
                parent[v] = u;
                q.push(v);
            }
        }
    }
}

inline void init_lca(int root, int n) {
    bfs_height(root);
    memset(P, -1, sizeof P);
    for(int u = 1; u <= n; ++u)
        P[u][0] = parent[u];
    for(int j = 1; (1 << j) < n; ++j) {
        for(int u = 1; u <= n; ++u) {
            if(P[u][j - 1] != -1) {
                P[u][j] = P[P[u][j - 1]][j - 1];
            }
        }
    }
}

inline int lca(int u, int v) {
    if(height[u] > height[v])
        swap(u, v);
    int log_v = log2(height[v]);
    for(int i = log_v; i >= 0; --i) {
        if((height[v] - (1 << i)) >= height[u]) { // if height[ancestor(v, 2 ^ i)] >= height[u], then you can move node v higher;
            v = P[v][i];
        }
    }
    if(u == v)
        return u;
    log_v = log2(height[v]);
    for(int i = log_v; i >= 0; --i) {
        if(P[v][i] != -1 and P[u][i] != P[v][i]) { // If P[u][i] == P[v][i], this node may be much higher in the tree than the actual LCA(u, v)
            u = P[u][i];
            v = P[v][i];
            // now u and v point to their 2 ^ i ancestor;
        }
    }
    return parent[u];
}

int main() {

    // G = (V, E) is assumed to be a tree;
    int V, q;
    scanf("%d %d", &V, &q);
    adj.resize(V + 5);

    int E = V - 1;
    for(int i = 0; i < E; ++i) {
        int u, v;
        scanf("%d %d", &u, &v);
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    
    int root = 1;
    init_lca(root, V);
    // q queries;
    for(int i = 0; i < q; ++i) {
        int u, v;
        scanf("%d %d", &u, &v);
        int lca_uv = lca(u, v);
        printf("lca(%d, %d) = %d\n", u, v, lca_uv);
    }
    return 0;
}
