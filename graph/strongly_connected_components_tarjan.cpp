#include <bits/stdc++.h>

#define debug(x) cout << "> " << #x << " = " << x << endl;
#define debugat(arr, at) cout << "> " << #arr << "[" << at << "] = " << arr[at] << endl;

using namespace std;

/* 
 *  Finding Strongly connected components (SCC), Tarjan's Algorithm;
 *  
 *  The DFS Spanning forest is the heart of tarjan's algorithm.
 *  It will use the forest to discover all kind's of paths (u -> v), going to v
 *  and exploit back edges to discover the paths           (v -> u), returning to u;     
 *  
 *  Intuition:  
 *      Once DFS spanning tree is built, we know that every node u is connected to all vertices in it's subtrees.  
 *      So the path (u, v), where u is the subtree root, for every v u's subtree is immediate.
 *      For the case (v, u), we'll need back edges (edges that go back on the tree).        
 *      The back edges will form a cycle, and a maximal cycle (SCC) is what we're looking for.
 *      
 *      Back edge returning to some ancestor in the subtree (case 1)
 *          Let u be the ancestor of some node v in the spanning tree.
 *          Let (v, u) be a back edge.
 *          u, v, and all vertices in between the path (u -> v) in the tree belong to the SCC.
 *          This is true because if there is a path (u -> v) and a path (v -> u), u and v must be belong the same SCC.
 *
 *      Back edge returning to a different subtree (case 2)
 *          Let r the root of some subtree and u be in this subtree.
 *          Let (u, v) be an edge such that v is not in r's subtree.
 *          If there is a path (v -> u) then u, v will be in the same SCC. 
 *          This case is trickier to verify since the spanning tree doesn't reveal that immediatly.
 *
 *          Let num[u] = n, where u is a vertex, and n is the n'th vertex that DFS visited. This marks the time that u was first discovered.   
 *          let low[u] = num[u], when u it's discovered,
 *              low[u] = min(low[u], low[v]) for every neighbor v of u, such that v is on the **stack**. 
 *                                           this marks the lowest low[v] that u can reach directly or indirectly.
 *
 *          **stack**: Tarjan's algorithm will use a stack to control which vertices will be in the same SCC.
 *          Let's define the root of some SCC as r, such that num[r] = low[r]. This means that r cannot "go back in time" and visit
 *          some vertex v that was discovered before r.
 *          More important, for every vertex u that is in the same SCC as r, they all will have the same low[u] = low[r].
 *          This means that the lowest vertex they can visit is r. That properties is calculated recursivelly inside DFS,
 *          according to the recursive definition of low[u];
 *          So, whenever we find some vertex that after we analying it and it's subtree, and it's low[u] remains equals to num[u],
 *          this vertex is the end of some SCC, therefore every vertex in the stack [u, ...., v] will be in the same scc.
 *          v is the on the top of the stack.
 */

const int N = 12345;
const int UNVISITED = -1;

vector< vector<int> > adj;
int V, E;
int num[N], low[N];
bool on[N];

void scc(int u, int &dfs_time, stack<int> &dfs_stack) {
    num[u] = low[u] = ++dfs_time;           // making it the root of some SCC. Begin of the SCC.
    dfs_stack.push(u);
    on[u] = true;

    for(int v : adj[u]) {
        if(num[v] == UNVISITED)             // gotta visit v first before we analyze u;
            scc(v, dfs_time, dfs_stack);
        if(on[v])                           // trying to merge u with some other SCC which was discovered earlier
            low[u] = min(low[u], low[v]);   
    }
    if(num[u] == low[u]) {                  // Can't merge with another SCC which was discovered earlier. End of the SCC.
        printf("SSC:");
        while(true) {
            int v = dfs_stack.top();        // every vertex in between (u, dfs_stack.top()) are in the same SCC. They all have low[v] = num[u].
            dfs_stack.pop();
            on[v] = false;

            printf(" %d", v);
            if(u == v)
                break;
        }
        puts("");
    }
}

int main() {

    scanf("%d %d", &V, &E);
    adj.resize(V + 5);

    for(int i = 0; i < E; ++i) {
        int u, v;
        scanf("%d %d", &u, &v);
        adj[u].push_back(v);    // G is undirected.
    }

    memset(on, 0, sizeof on);
    memset(num, UNVISITED, sizeof num);
    memset(low, UNVISITED, sizeof low);

    int dfs_time = 0;
    stack<int> dfs_stack;

    for(int i = 1; i <= V; ++i) {
        if(num[i] == UNVISITED)
            scc(i, dfs_time, dfs_stack);
    }
    for(int i = 1; i <= V; ++i) {
        debugat(low, i);
    }

   return 0;
}
