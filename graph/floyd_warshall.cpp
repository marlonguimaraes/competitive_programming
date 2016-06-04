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
 *  CONSTRUCTING THE OPTMAL PATH;
 *      Consider the predescedor matrix pi(i, j, k) which is the predecessor of vertex j,
 *      in the shortest path from i to j, using only intermediate vertices in the set (i, .., k);
 *      
 *      Base case:
 *      pi(i, j, 0) = NULL, if there is no edge from i to j;
 *      pi(i, j, 0) = i, if there is an edge (i, j) or i == j;
 *
 *      pi(i, j, k) = pi(i, j, k - 1), if f(i, j, k) <= f(i, k, k - 1) + f(k, j, k - 1);
 *      pi(i, j, k) = pi(k, j, k - 1)  othwerwise;      
 *      
*/

#include <bits/stdc++.h>

#define MAX 100
#define INF (1 << 29)

#define debug(x) cout << "> " << #x << " = " << x << "\n";

using namespace std;

typedef vector<vector<int> > matrix;

int V, E;

void initFloydWarshallDist(matrix &dist) {
    dist.assign(V + 5, vector<int>(V + 5, INF));
    for(int i = 1; i <= V; ++i)
        dist[i][i] = 0;         // this DOES NOT consider selfloops!
}

void initFloydWarshallParent(matrix &parent, matrix &dist) {
    parent.resize(V + 5, vector<int>(V + 5));
    for(int i = 1; i <= V; ++i) {
        for(int j = 1; j <= V; ++j) {
            if(i == j or dist[i][j] == INF) {   // i == j or there is no edge (i, j)
                parent[i][j] = 0;
            }
            else {
                parent[i][j] = i;               // there is an edge(i, j);
                                                // you must handle multiedge before;
            }
        }
    }
}

void floydWarshall(matrix &dist, matrix &parent) {
    for(int k = 1; k <= V; ++k) {
        for(int i = 1; i <= V; ++i) {
            for(int j = 1; j <= V; ++j) {
                if((dist[i][k] + dist[k][j]) < dist[i][j]) {  // min(not using vertex k, using vertex k);
                    dist[i][j] = dist[i][k] + dist[k][j];
                    parent[i][j] = parent[k][j];            // predecessor of [i][j] using vertex k as an intermediate vertex
                }
            }
        }
    }
}

void printPath(int i, int j, const matrix &parent) {
    if(i != j) printPath(i, parent[i][j], parent);
    printf(" %d", j);
}

int main() {
    while(cin >> V >> E) {
        matrix dist,            // [i][j] = shortest distance from i to j;
               parent;          // predecessor matrix

        initFloydWarshallDist(dist);

        for(int i = 0; i < E; ++i) {
            int u, v, w;
            cin >> u >> v >> w;
            dist[u][v] = w;
        }

       initFloydWarshallParent(parent, dist);

        int source = 1, target = 4;
        floydWarshall(dist, parent);
        printf("distance[%d][%d] = %d\n", source, target, dist[source][target]);
       printf("path = ");
       printPath(source, target, parent);
       puts("");
    }
    
    return 0;
}
