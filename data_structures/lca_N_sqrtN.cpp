#include <bits/stdc++.h>

#define debug(x) cout << "> " << #x << " = " << x << endl;
#define debugat(arr, at) cout << "> " << #arr << "[" << at << "] = " << arr[at] << endl;
#define debugpair(p) cout << "> " << #p << " = " << "(" << p.first << ", " << p.second << ")" << endl;

using namespace std;

// LCA - Lowest Common Ancestor;
// LCA(u, v) = deepest (farest from the root) node such that u and v are descendants;
// we define parent[u] as u's father, and parent[root] == root;
// we define level[u] as u's level in the tree;

// Naive LCA <O(1), O(N)> preprocessing time, query time;

/*
* while(u != v) {
*     if(level[u] > level[v]) {
*         u = parent[u];
*     }
*     else {
*         v = parent[v];
*     }
* }
* return u;
*/

// There is a tree with height n - 1 and n nodes in the worst case

// Sqrt Decomposition, <O(n), O(sqrt(n))>
// If a tree has height H, we can divide it in sections of size sqrt(H):

// Section 0 : responsable for nodes with height in the interval [0, sqrt(H) - 1];
// Section 1 : responsable for nodes with height in the interval [sqrt(H), 2 * sqrt(H) - 1;
// Section i : responsable for nodes with height in the interval [i * sqrt(H), (i + 1) * sqrt(H) - 1];

// We're going to navigate in those sections in a botton up way. To do so, each node is going to point to a node in the section immediately above it.
// P[i] = i's ancestor node in the last level of the section immediately above i's section;
// we define P[i] = 1 for every node in the first section (0);
// For nodes in the first level of it's section, we define P[i] = parent[i];
// For the left nodes, P[i] = P[parent[i]];

// For the query(LCA(u, v)) if P[u] == P[V], then the LCA(u, v) must be P[u] or someother node between u, v, and P[u] = P[v];
// if LCA(u, v) == P[u] there is nothing to prove.
// if LCA(u, v) != P[u], we know for sure that there is a path (u, P[u]) and (v, P[v]), since it was the first node, from botton up,
// that have equals P[i], we now that LCA can't be above that. Otherwise you could just make LCA = P[u] and have a contradiction.
// So now we just scan nodes from u, v to P[u] and take the first common ancestor that appear from botton up as the LCA of u and v.

// If P[u] != P[v] it's ease to see that LCA(u, v) == LCA(P[u], v) or LCA(u, P[v]) depending on who is farest from the root.

const int N = 123456;

int parent[N], P[N], level[N];

vector<vector<int> > adj;

inline void bfs_level(int root) {
    memset(level, -1, sizeof level);
    level[root] = 0;

    queue<int> q;
    q.push(root);
    parent[root] = root;

    while(!q.empty()) {
        int u = q.front();
        q.pop();
        for(int v : adj[u]) {
            if(level[v] == -1) {
                level[v] = level[u] + 1;
                parent[v] = u;
                q.push(v);
            }
        }
    }
}

void dfs(int u, int n_square) {
    if(level[u] < n_square) {
        P[u] = 1;
    }
    else if(level[u] % n_square == 0) {
        P[u] = parent[u];
    }
    else {
        P[u] = P[parent[u]];
    }
    for(int v : adj[u])
        if(P[v] == -1)
            dfs(v, n_square);
}

inline int lca(int u, int v) {
    while(P[u] != P[v]) {
        if(level[u] > level[v])
            u = P[u];
        else
            v = P[v];
    }
    while(u != v) {
        if(level[u] > level[v])
            u = parent[u];
        else
            v = parent[v];
    }
    return u;
}

inline void init_lca(int root, int n) {
    int n_square = sqrt(n);
    bfs_level(root);

    memset(P, -1, sizeof P);
    dfs(root, n_square);
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
