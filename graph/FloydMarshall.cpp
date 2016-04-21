// Floyd-Algorithm: solves all pairs shortest paths in O(n^3)

/* INTUITION:
 *
 *  Consider all paths from i to j which intermediate vertex from the set {1, 2, ..., k}
 *  If the path from i to j uses no intermediate vertex at all, k = 0, i.e it's an edge (i, j) e E;
 *    
 *  Let p be the minimum weight path between all paths from i to j using some vertex u as an intermediate vertex;
 *  If u is not k:
 *      So u < k, therefore the vertex u used in the minimum weight path is in the set {1, 2, ..., k - 1}
 *  If u is k: (k is the intermediate vertex in the path p with minimum weight;
 *      If u = k, then path p can be decomposed in two paths;
 *      p = path(i, k) ~ path(k, j);
 *      Consider the path(i, k). This must be the minimum weight path from i to k;
 *      Samething for the path(k, j);
 *      So, 2 subproblems arise: path(i, k) and path(k, j);
 *      path(i, k) uses only intermediate vertex in set (1, 2, ..., k - 1), otherwise it would use k twice;
 *      Samething for path(k, j);
 *
 *  DP solution:
 *  let f(k, i, j) be the minimum weight path from i to j using vertices from (1, 2, ..., k) as intermediate vertices;
 *  the solution to our problem would be f(k = n, i, j) considering all possible intermediate vertices;
 *  Note that f(0, i, j) no intermediate vertices are used, so the solution must be edge(i, j) if it exists;
 *
 *  back to f(k, i, j) = f(k - 1, i, j) if k is not an intermediate vertex which produces the minimum weight path
 *                                     between all vertices in {1, 2, ..., k},
 *                                     therefore, the vertex which produces can only be in set {1, 2, ..., k - 1}
 *
 *          f(k, i, j) = f(k - 1, i, k) + f(k - 1, k, j) if k when used as an intermediate vertex from path i, j,
 *                                                       produces a minimum weight path between all possible vertices in set (1, 2, ..., k);
 *          If so, two subproblems arise: what is the best path for i to k? and from k to j?
 *          I don't know, but the solution for i to k must not use k as an intermediate vertex, otherwise it wouldn't be optmal;
 *          So the solution for i to k bust use only vertices in set {1, 2, ..., k - 1};
 *          Samething for j to k;
 *
 *          How do you know if k is or isn't the best intermediate vertex?
 *          DP gives 0 fucks, just calculate the best of the two options;
 *          f(k, i, j) = min(f(k - 1, i, j), f(k - 1, i, k) + f(k - 1, k, j));
 *
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
