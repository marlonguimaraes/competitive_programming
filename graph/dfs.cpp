#include <bits/stdc++.h>

#define DEBUG
#ifdef DEBUG
    #define debug(x) cout << "> " << #x << " = " << x << endl;
#else
    #define debug(x)
#endif

using namespace std;

// DFS - Depth-first-search
// DFS is backtracking, but never calls the same state twice. It's used to traverse a graph (directed or not)
/* This DFS keeps a global "time". 
 * Every vertex has a first and a second time variables;
 * First = first time this vertex is discovered in the dfs algorithm;
 * Second = after dfs is runnad in each unvisited vertex in adjList of the current the vertex,
 *          the second time is recorded;
 * This technique is useful for more advanced algorithms;
 */

const int N = 1234;

vector< vector<int> > adjList; // adjacency list representation.
int first[N], last[N];
int total;

void dfs(int u) {
    printf(" -> %d", u);

    first[u] = ++total;
    for(int v : adjList[u]) {
        if(first[v] == 0) {
            dfs(v);
        }
    }
    last[u] = ++total;
}

int main() {
    int v, e;
    cin >> v >> e;

    adjList.resize(v + 5);
    for(int i = 0; i < e; ++i) {
        int u, v;
        cin >> u >> v;
        adjList[u].push_back(v); // directed graph
    }

    int source = 1;

    total = 0;
    memset(first, 0, sizeof first);
    memset(last, 0, sizeof last);

    dfs(source);
    printf("\n");

    for(int i = 1; i <= v; ++i) {
        printf("(first, last, %d) = %d, %d\n", i, first[i], last[i]);
    }

    return 0;
}
