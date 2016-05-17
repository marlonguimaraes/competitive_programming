#include <bits/stdc++.h>

#define debug(x) cout << "> " << #x << " = " << x << endl;
#define debugat(arr, at) cout << "> " << #arr << "[" << at << "] = " << arr[at] << endl;

using namespace std;

/* 
 *  Bellman-Ford's algorithm, solves the single-source-shortest-paths 
 *  Unlike Dijkstra, this algorithm works well with negative edges and negative cycles.
 *  
 *  Bellman-Ford's algorithm exploits the path-relaxation property, where 
 *  for any shortest path p = <v0, v1, ..., vk>,
 *  relaxing edges (v0, v1), (v1, v2), ..., (vk-1, vk), will calculate the shortest path from v0 to vk correctly.
 *   
 *  Proof by induction:
 *  
 *  Let v.d be the shortest path from source to vertice v
 *  Base case:
 *     Let v.d = INFINITY, if v is != source;
 *     Let v.d = 0,        if v is == source;
 *  For the path<v0> the base case works fine; 
 *  Inductive step:
 *  Assume that after relaxing edges (v0, v1), ..., (vk-2, vk-1) the shortest path source -> vk-1 is correctly calculate;
 *  Relaxing vertice (vk-1, vk) will calculate the shortest path for vk, since by your hypothesis, the shortest path to vk used vertice vk-1;
 *  And, by the optimal substructure property of shortest path, it must use the shortest path to vk-1, which was assumed to be calculated correctly
 *  Note that, for any graph, a simple path has at most |V| - 1 edges.
 *  
 *  Bellman-Ford algorithm will relax all vertices (|V| - 1) times, which will calculate all shortest paths due to path-relaxation property 
 *  Dectecting a negative cycle: note that shortest path's with negative cycles is not well defined since you can always make the path smaller,
 *                               so the path-weight would be -INFINITY  
 *                               This happens because we can make always relax some edge (u, v) making the path-weight to v smaller,
 *                               doing this arbitraly, we can "reach" infinity.
 *  Bellman-Ford exploit this property as follows:
 *                              After (|V| - 1) relaxations, if we can still make the path to v smaller, relaxing some edge (u, v)
 *                              there must be a cycle, because we could do it again forever. 

 */

const int N = 12345;
const int INF = (1 << 29);

typedef pair<int, int> ii;
typedef pair<int, ii> tri;

vector< vector<ii> > adj;

int V, E;
int dist[N], parent[N], cycle_at;

void init_bellman_ford(int source) {
    for(int u = 1; u <= V; ++u) {
        dist[u] = INF;
        parent[u] = -1;
    }
    dist[source] = 0;
    parent[source] = source;
    cycle_at = -1;
}

bool relax(int u, int v, int w) {
    if((dist[u] + w) < dist[v]) {
        dist[v] = dist[u] + w;
        parent[v] = u;
        return true;
    }
    return false;
}

bool bellman_ford(int source) {
    init_bellman_ford(source);
    for(int i = 1; i <= (V - 1); ++i) {
        for(int u = 1; u <= V; ++u) {
            for(ii e : adj[u]) {
                relax(u, e.first, e.second);
            }
        }
    }
    for(int u = 1; u <= V; ++u) {
        for(ii e : adj[u]) {
            if(relax(u, e.first, e.second)) {
                cycle_at = e.first;
                return false;
            }
        }
    }
    return true;
}

void printDist(int source) {
    for(int u = 1; u <= V; ++u) {
        printf("Shortest path from source to %d, [%d] -> [%d] = %d\n", u, source, u, dist[u]);
    }
}

void printPath(int u, vector<bool> &vis) {
    if(parent[u] == u or vis[u])
        printf(" %d", u);
    else {
        vis[u] = true;
        printPath(parent[u], vis);
        printf(" %d", u);
    }
}

int main() {

    // G is directed, weighted, graph
    scanf("%d %d", &V, &E);

    adj.resize(V + 5);
    for(int i = 0; i < E; ++i) {
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);
        adj[u].push_back(ii(v, w));
    }

    vector<bool> vis(V + 5);
    int source = 1;
    if(!bellman_ford(source)) {
        puts("There is a negative cycle");
        printPath(cycle_at, vis);
        puts("");
    }
    else {
        printDist(source);
        printPath(4, vis);
        puts("");
    }
   return 0;
}
