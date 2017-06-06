#include <bits/stdc++.h>

#define fori(i, ini, lim) for(int i = int(ini); i < int(lim); i++)
#define ford(i, ini, lim) for(int i = int(ini); i >= int(lim); i--)

#define debug(x) cout << "> " << #x << " = " << x << endl;
#define debug_at(arr, at) cout << "> " << #arr << "[" << at << "] = " << arr[at] << endl;
#define debug_pair(p) cout << "> " << #p << " = (" << p.first << ", " << p.second << ")" << endl;

using namespace std;

const int N = 123;

int V, E;

vector<vector<int> > adj;
int cap[N][N];

bool vis[N];
int parent[N];

int source, sink;

/* if calc == true, visit() calculates the minimum capacity in the path from source to sink
 * in the residua network
 * if calc == false, visit() updates the edges in that path, according to f
 */

inline void visit(int v, int &f, bool calc) {
    if(v != source) {
        int u = parent[v];
        if(calc) {
            f = min(f, cap[u][v]);
        }
        else {
            // The following lines are the most important in the max-flow implementation
            cap[u][v] -= f;
            cap[v][u] += f;

            /* cap[u][v] represents the current capacity from vertex u to vertex v.
             * Suppose capacity(u, v) = 20 in the original graph.
             * This means that we can push 20 more flow in (u, v).
             * Suppose we push 7 flow units in (u, v)
             * Now cap[u][v] = 20 - 7 = 13, since now we can only push 13 more units.
             * However, the back edge (v, u), in the residual network, now have 7 more capacity.
             * This means that we can revert some (or all) of 7 units in (v, u) and send them to another vertex.

             * These two lines are important because it doesn't matter if (u, v) is a reverse edge or a direct edge
             * If we reduce the capacity from an edge (reverse or direct) by pushing flow through it
             * we have to reduce the capacity in that direction and increase the capacity in the opposite direction.
             */
        }
        visit(u, f, calc);
    }
}

inline int augmenting_path() {
    memset(parent, -1, sizeof parent);
    memset(vis, 0, sizeof vis);

    vis[source] = true;
    parent[source] = source;

    queue<int> q;
    q.push(source);
    bool found = false;

    // Finds an augmenting path
    while(!q.empty()) {
        int u = q.front();
        q.pop();

        if(u == sink) {
            found = true;
            break;
        }

        for(int v : adj[u]) {
            if(cap[u][v] > 0 and !vis[v]) {
                vis[v] = true;
                parent[v] = u;
                q.push(v);
            }
        }
    }

    if(!found) return 0;
    int f = 1 << 30;

    visit(sink, f, true); // Finds the minimum capacity between edges in the residual network
    visit(sink, f, false); // Update capacities according to minimum capacity found
    return f;
}

inline int max_flow() {
    int f = 0;

    while(true) {
        int ap = augmenting_path();
        if(ap == 0) break; // No more augmenting paths. Ford fulkerson is done.

        f += ap;
    }
    return f; // Max flow since there were no more augmenting paths.
}

int main() {

    for(int t = 1; (scanf("%d", &V), V > 0); ++t) {
        scanf("%d %d %d", &source, &sink, &E);
        adj.clear();
        adj.resize(N);
        memset(cap, 0, sizeof cap);

        fori(i, 0, E) {
            int u, v, c;
            scanf("%d %d %d", &u, &v, &c);

            // Graph is undirected
            adj[u].push_back(v);
            adj[v].push_back(u);

            // Important observation: if there are multiple edges (u, v), you just sum the capacities (don't take the max of those!)
            cap[u][v] += c;
            cap[v][u] += c;
        }

        int ans = max_flow();
        printf("Network %d\n", t);
        printf("The bandwidth is %d.\n", ans);
        puts("");

    }
    return 0;
}
