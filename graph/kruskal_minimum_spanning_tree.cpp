#include <bits/stdc++.h>

#define debug(x) cout << "> " << #x << " = " << x << endl;
#define debugat(arr, at) cout << "> " << #arr << "[" << at << "] = " << arr[at] << endl;

using namespace std;

/* 
 * Minimum Spanning Tree (MST)
 * Let G = (V, E) be a connected graph, we define the MST as T = (V, E'), that is a tree with all vertices of G.
 * 
 * Since the MST is not unique, we can define the total weight of some MST T = (V, E)
 * totalWeight(T) = sum of every w(u, v) such that the edge (u, v) is in E, and w(u, v) is the edge's weight.
 * we now define MST as the min(totalWeight(T)) of all spanning tres.
 * The MST is not necessarily unique.
 * 
 * Some definitions to prove Prim's algorith,
 * Cut C = a partition of V = (S, V - S) where S is a subset of V;
 * Crossing edges = edges (u, v) which have endpoints in different set's of a cut (one endpoint is in (S), one endpoint in (V - S)). 
 * A cut respects a set of edges A if there is not any crossing edges in A, with respect to that cut.
 *
 * Light edge = of all crossing edges in a graph, with respect to some cut, the one with lowest weight w(u, v);
 * Safe Edge =  let A be a subset of edges of some MST. A safe edge is a edge (u, v) such that when (u, v) is added to A,
 *   A is still a subset of some MST.
 *
 * Theorem every light edge is a safe edge.
 * Proof: Let G(V, E) be a connected graph, and T = (V, E') be some MST of G.
 *        Let's also construct some T' = (V, A) where A is a subset of E'. T' is a subgraph of T.
 *        Make a cut in T, which respects A.
 *        Let edge (u, v) be a light edge. We have to prove that this edge is safe, i.e, adding it to T' will make T' be inside of some MST.
 *        Since there is no crossing edges in A, there must be some crossing edge in the path (u, v) in T.
 *        Let edge (x, y) be the first crossing edge in the path (u -> v) in T.
 *        Since (u, v) is a light edge, we can create another minimum spanning tree replacing edge (x, y) by edge (u, v);
 *        Because it won't make the answer worse, and the resulting graph will still be a spanning tree.
 */

/* Maximum Spanning Tree
 * Insteading of taking the crossing edge with lowest weight, take the one with highest weight
 */

/* Constructing a Minimum/Maximum Spanning tree
 * Save every edge (u, v) such that u and v are not in the same set, in the sorted order.
 * Run a BFS on that set of edges to construct a MST.
 */

const int N = 12345;

class UFDS {
public:
    int rank[N], parent[N];

    UFDS(int size) {
        memset(rank, 0, sizeof rank);
        for(int i = 1; i <= size; ++i)
            parent[i] = i;
    }

    int getParent(int i) {
        return i == parent[i] ? i : parent[i] = getParent(parent[i]);
    }

    bool sameSet(int i, int j) {
        return getParent(i) == getParent(j);
    }

    void unionSet(int i, int j) {
        if(!sameSet(i, j)) {
            int pi = getParent(i), pj = getParent(j);
            if(rank[pi] > rank[pj]) {
                parent[pj] = pi;
            }
            else {
                parent[pi] = pj;
                if(rank[pi] == rank[pj])
                    ++rank[pj];
            }
        }
    }
};

typedef pair<int, int> ii;
typedef pair<int, ii> tri;

int V, E;

int main() {

    // G must be a connected, undirected graph
    scanf("%d %d", &V, &E);

    vector<tri> edges;
    for(int i = 0; i < E; ++i) {
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);
        edges.push_back(tri(w, ii(u, v)));
    }
    sort(edges.begin(), edges.end());
    UFDS ufds(V);
    int mst_cost = 0;
    for(tri edge : edges) {
        int w = edge.first;
        int u = edge.second.first,
            v = edge.second.second;
        if(!ufds.sameSet(u, v)) {
            ufds.unionSet(u, v);
            mst_cost += w;
        }
    }

    printf("mst_cost = %d\n", mst_cost);

    return 0;
}
