#include <bits/stdc++.h>

#define debug(x) cout << "> " << #x << " = " << x << endl;
#define debugat(arr, at) cout << "> " << #arr << "[" << at << "] = " << arr[at] << endl;

using namespace std;

/* DFS Spanning tree == the tree that "maps" DFS path;
 *                      It forms a tree because each vertex is visited only once so is every edge(u, v).
                        The spanning trees of every connected component of a graph forms a spanning forest.
 *  
 *  Most of the properties bellow are easy to see if you remember that G = (V, E) is an UNDIRECTED graph. Keep that in mind.
 *  
 * num[u] = marks the time that u was first discovered in dfs;
 * low[u] = let v be some u's neighbor, i.e, there is an edge(u, v),
 *          low[u] = num[u] when u is first discovered;  
 *          low[u] = min(low[u], low[v]) such that v is NOT u's parent
 *          so, low[u] is the lowest num[v] such that v is reachable from u without using the edge (u, parent[u]);  
 *  
 *  Base case: u is root;  
 *      let c1 and c2 such that there are edges (u, c1), (u, c2);
 *      if c1 is not reachable from c2, without using the root as a vertex, 
 *      then the root is an articulation point. This base case is easy to calculate inside the recursion.  
 *  
 * let v be some u's neighbor;  
 * if num[u] <= low[v], u is an articulation point;
 *      This means that vertex v cannot reach some vertex w, without using vertex u, such that w was discovered before u;
 *      Removing u from the graph, there will be no path for every vertex w to v, such that num[w] < num[u]
 *      , disconnecting the graph;
 *      So, v needs u.
 *  
 * if num[u] == low[v], there is a cycle between u and v;  
 *      let u = parent[v], for simplicity;
 *      this means that v can reach u without using the edge(u, v);
 *      so the cycle is : go to u from v, without using edge(u, v);  
 *      now use the edge(u, v) to complete the cycle;
 *      
 *      This is important because although u is an articulation vertex,
 *      removing the edge(u, v) will not disconnected the graph, because v have at least other path to go back to u;  
 *  
 * if num[u] < low[v],  (u, v) is a brige;
 *      since num[u] < low[v], v can't even return to vertex u (it's parent) without using the edge(u, v);
 *      so, removing the edge(u, v), v will be disconnected, disconnecting the graph.
 */

const int N = 12345;
const int UNVISITED = -1;

int V, E;
vector< vector<int> > adj;

int num[N], low[N], parent[N];
bool articulation_vertex[N];

void dfs(int u, int &dfs_time, int root, int &root_children) {
    num[u] = low[u] = ++dfs_time;
    for(int v : adj[u]) {
        if(num[v] == UNVISITED) {
            parent[v] = u;
            if(u == root)           // for the second time this is true, it means that the vertex v, from the first time of this case,
                ++root_children;    // didn't visit the vertex v of this second case;

            dfs(v, dfs_time, root, root_children);
            if(num[u] <= low[v])
                articulation_vertex[u] = true;
            if(num[u] < low[v])
                printf("edge (%d, %d) is a bridge\n", u, v);
            low[u] = min(low[u], low[v]);
        }
        if(v != parent[u]) {
            low[u] = min(low[u], low[v]);
        }
    }
//    printf("%d = (%d, %d)\n", u, num[u], low[u]);
}

int main() {

    // G must be a connected, undirected graph
    scanf("%d %d", &V, &E);
    adj.resize(V + 5);

    for(int i = 0; i < E; ++i) {
        int u, v;
        scanf("%d %d", &u, &v);
        adj[u].push_back(v);
        adj[v].push_back(u); // since G is undirected
    }

    memset(num, -1, sizeof num);
    memset(articulation_vertex, 0, sizeof articulation_vertex);
    memset(parent, 0, sizeof parent);

    int dfs_time = 0, root_children = 0,
        root = 0;
    dfs(0, dfs_time, root, root_children);
    articulation_vertex[root] = root_children > 1;

    for(int i = 0; i < V; ++i)
        debugat(articulation_vertex, i);

   return 0;
}
