#include <bits/stdc++.h>

#define debug(x) cout << "> " << #x << " = " << x << endl;
#define debugat(arr, at) cout << "> " << #arr << "[" << at << "] = " << arr[at] << endl;

/* BIPARTITE CHECK
 *
 * A graph G = (V, E) is bipartite if
 *       V = U (union) V, U (intersection) V = 0 (null set);
 *       and for every edge(u, v) in E
 *          u is inside U and v is inside V
 *              or
 *          v is inside U and u is inside V
 *
 *  Basically, if you color each vertex with one of two colors, such that two neighbors don't share the same color, the graph is bipartite;
 *
 *  ALGORITHM
 *
 *  1) for some vertex u, and for every vertex v which is u's neighbor
 *     2) if v is already painted:
 *          if u and v doesn't have oposite colors, return false;
 *     3) if v isn't painted yet:
 *          paint v with u's oposite color and call 1) with v; 
 *  4) If the algorithm hasn't returned false, the graph is bipartite;
 */

using namespace std;

const int N = 123;

int V, E;
int color[N];
vector< vector<int> > adj;

bool isBipartite(int u, int c) { // u = current vertex, v's color;
    color[u] = c;
    for(int v : adj[u]) {
        if(color[v] == -1 and !isBipartite(v, 1 - c)) // Check if painting v with oposite color (1 - c) the graph is still bipartite;
            return false;                             // v hasn't been painted yet
        else if(color[u] == color[v])                 // u and v have equal colors;
            return false;
    }
    return true;                                      // didn't fail any check, so it's a valid graph
}

int main() {
    ios_base::sync_with_stdio(false);
    while(cin >> V >> E) {
        adj.clear();
        adj.resize(V + 10);
        memset(color, -1, sizeof color);

        for(int i = 0; i < E; ++i) {
            int u, v;
            cin >> u >> v;
            adj[u].push_back(v);
        }

        bool ans = isBipartite(1, 1);   // If the graph is disconnected, a loop variant will be necessary;
                                        // Paint vertex 1 with color 1. Any other color would be equally valid.
        cout << "G = (V, E) is ";
        if(!ans) cout << "not ";
        cout << "bipartite\n";
    }
    return 0;
}
