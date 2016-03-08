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

const int N = 1234;

vector< vector<int> > adjList; // adjacency list representation.
bool visited[N];

void dfs(int u) {
    visited[u] = true;
    for(int v : adjList[u]) {
        if(!visited[v]) {
            printf("%d -> %d\n", u, v);
            dfs(v);
        }
    }
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
    dfs(source);

    return 0;
}
