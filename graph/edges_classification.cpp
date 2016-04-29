#include <bits/stdc++.h>

#define debug(x) cout << "> " << #x << " = " << x << endl;
#define debugat(arr, at) cout << "> " << #arr << "[" << at << "] = " << arr[at] << endl;

using namespace std;

/* DFS algorithm allow us to classification edges in the graph G = (V, E);
 * Since DFS will at least check all edges (u, v) in E, each of them can be classified.
 *
 * Let's first classify each vertex in dfs() execution order.
 *
 * UNVISTED = vertices that were not found yet;
 * EXPLORED = this vertex was found, but it hasn't check or visited all of it's neighbors;
 * VISITED  = this vertex and all of it's neighbors were visited;
 *
 * Tree Edge (EXPLORED - UNVISITED), (u, v)
 *      v was just discovered by u. This edge (u, v) will be an edge in the tree that DFS will make (spanning tree);
 *
 * Back Edgee (EXPLORED - EXPLORED);
 *      u is going to vertex v, which is still being explored. This is a cycle.
 *      Bidirectional edges (u, v) (v, u) may not be considered back edges depending on the application.
 *
 * Forward/Cross edges (EXPLORED - VISITED)
 *      u is going to some vertex that has already been VISITED. This is a cycle.
 */

const int N = 12345;

enum {UNVISITED, EXPLORED, VISITED};

int V, E;
vector< vector<int> > adj;
int dfsState[N],
    parent[N];

void dfs(int u) {
    dfsState[u] = EXPLORED;
    for(int v : adj[u]) {
        printf("edge(%d, %d) is a ", u, v);
        switch(dfsState[v]) {
            case UNVISITED:
                printf("tree edge.\n");
                parent[v] = u;
                dfs(v);
                break;
            case EXPLORED:
                printf("%s.\n", v != parent[u] ? "back edge" :  "bidirectional edge");
                break;
            case VISITED:
                printf("Forward/Cross edge.\n");
                break;
        }
    }
    dfsState[u] = VISITED; // Finished visiting u's neighbors, so it becomes VISISTED;
                           // Of course, all u's neighbors will become visisted first;
}

int main() {

    scanf("%d %d", &V, &E);
    adj.resize(V + 5);

    for(int i = 0; i < E; ++i) {
        int u, v;
        scanf("%d %d", &u, &v);
        adj[u].push_back(v);
    }

    memset(dfsState, 0, sizeof dfsState);
    for(int u = 1; u <= V; ++u) {
        if(dfsState[u] != VISITED) {
            parent[u] = u;
            dfs(u);
        }
    }
    return 0;
}
