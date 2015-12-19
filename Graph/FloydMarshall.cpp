// Floyd-Algorithm: solves all pairs shortest paths in O(n^3)

/* INTUITION:
 *  
 *  There are three options to go to vertex j from vertex i
 *  a) there is no path from i to j;
 *  b) use the edge (i, j), if it exists (not necessarily the shortest path)
 *  c) use some vertex k as an intermediate vertex, so the path would be = i ... -> k -> ... -> j;
 *     NOTE that maybe the edges (i, k) and (k, j) are not used.
 *
 *  the shortest path will be the path dist[i][k] = min(dist[i][k] + dist[k][j]) for all k E {0, 1, ..., V - 1}
 *  base cases: dist[i][j] = weight(i, j),
 *                           or INF if there isn't such an edge;
 *
 *  DP SOLUTION:
 *
 *  sp(i, j, k) = shortest path between i and j using all vertices in {0, 1, ..., k} as intermediate vertex
 *  sp(i, j, -1) = weight(i, j);
 *  sp(i, j, k) = min(sp(i, j, k - 1), sp(i, k, k - 1) + sp(k, j, k - 1));
 *              = min(using vertex k, not using vertex k as intermediate vertex);
 *      
 *  BOTTON UP:
 *      note that the solution for k uses only the information about the table for k - 1, so the problem is solvable O(n ^ 2) in memory
 */

#include <bits/stdc++.h>

#define MAX 100
#define INF (1<<29)

#define debug(x) cout << "> " << #x << " = " << x << "\n";

using namespace std;

int dist[MAX][MAX],                                         // [i][j] = shortest distance from i to j;
    parent[MAX][MAX],                                       // predecessor matrix
    v, e;

void floyd() {
    for(int i = 0; i < v; ++i)
        for(int j = 0; j < v; ++j)
            parent[i][j] = i;                               // base case: predecessor of path [i][j] using no intermediate vertex is i;

    for(int k = 0; k < v; ++k) {
        for(int i = 0; i < v; ++i) {
            for(int j = 0; j < v; ++j) {
                if(dist[i][j] > dist[i][k] + dist[k][j]) {  // min(not using vertex k, using vertex k);
                    dist[i][j] = dist[i][k] + dist[k][j];
                    parent[i][j] = parent[k][j];            // predecessor of [i][j] using vertex k as an intermediate vertex
                                                            // is the predecessor of vertex k
                                                            // We use this because maybe there is no edge (i, k) or
                                                            // there are multiple paths from i to k but only
                                                            // the shortest path from i to k is valid
                }
            }
        }
    }
}

void printPath(int i, int j) {
    if(i != j) printPath(i, parent[i][j]);
    printf(" %d", j);
}

int main() {
    while(cin >> v >> e) {
        memset(dist, 0, sizeof dist);
        for(int i = 0; i < e; ++i) {
            int u, w, length;
            cin >> u >> w >> length;
            dist[u][w] = length;
        }
        for(int i = 0; i < v; ++i) {
            for(int j = 0; j < v; ++j) {
                if(i == j) dist[i][j] = 0;
                else if(!dist[i][j]) dist[i][j] = INF;
            }
        }
        int source = 0, target = 1;
        floyd();
        printf("distance[%d][%d] = %d\n", source, target, dist[0][1]);
        printf("path = ");
        printPath(0, 1);
        puts("");
    }
    
    return 0;
}
