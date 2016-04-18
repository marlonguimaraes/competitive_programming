#include <bits/stdc++.h>

#define debug(x) cout << "> " << #x << " = " << x << endl;
#define debugat(arr, at) cout << "> " << #arr << "[" << at << "] = " << arr[at] << endl;

/* TOPOLOGICAL SORT
 * Given DAG (Directed Acyclic Graph) G = (V, E);
 * Topological sort is a linear ordering of all vertices of V such that for every edge (u, v), u must become BEFORE v in the ordering.
 * Every DAG has at least one topological sort.
 * Cyclic graphs contain no topological sort.

 * Find one topological sort using dfs:
 * Start from some node u. Run dfs on it;
 * After all neighbors of u has been visited, add u in a stack;
 * Repeat the process recursively for all u's neighbors;
 * This will produce a path p such that for every edge (x, y) on p, x appears before y.
 * Note that this is according to the topological sort definition but it's possible that
 * there is some node w in the path p such that some of it's predecessors are not in path p.
 * The algorithm will try to run dfs on each vertex, if the predecessors were not discovered in the first run
 * they will be discovered in the near future, and will be aded AFTER the current solution for the sort.
 * Therefore the result will be valid.

 * The solution is the stack in reverse oder.
 */

using namespace std;

const int N = 123;

int v, e;
bool vis[N];
vector< vector<int> > adj;

void dfs_topological(int u, vector<int> &sorted) {
    vis[u] = true;
    for(int v : adj[u])
        if(!vis[v])
            dfs_topological(v, sorted);
    sorted.push_back(u);
}

int main() {
    ios_base::sync_with_stdio(false);
    while(cin >> v >> e) {
        adj.clear();
        adj.resize(v + 10);
        memset(vis, 0, sizeof vis);
        for(int i = 0; i < e; ++i) {
            int u, v;
            cin >> u >> v;
            adj[u].push_back(v);
        }

        vector<int> sorted;
        for(int i = 1; i <= v; ++i) {
            if(!vis[i])
                dfs_topological(i, sorted);
        }
        for(auto it = sorted.rbegin(); it != sorted.rend(); ++it) {
            cout << *it << " ";
        }
        cout << "\n";
    }
    return 0;
}
