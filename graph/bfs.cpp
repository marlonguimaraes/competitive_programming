#include <bits/stdc++.h>

#define DEBUG
#ifdef DEBUG
    #define debug(x) cout << "> " << #x << " = " << x << endl;
#else
    #define debug(x)
#endif

using namespace std;


/* Breath-first-search, graph traversal algorithm O(V + E);
 * All vertex will be visisted. Consider that u is the current vertex been visited.
 * Bfs will add all vertex directly connect to u that haven't been visited yet in a Queue.
 * The distance for each of those added vertex will be vu.d + 1;
 * This process is repetead until the queue is empty.
 * 
 * Interesting properties:
 * -Bfs will calculated the shortest path from source for every vertex int the graph. 
 * -At any point, the distance from source of all vertex in the queue will have at most 2 different values.
 */

const int N = 1234,
          INF = -1;

vector< vector<int> > adjList;
int dist[N], parent[N];

void bfs(int source) {
    memset(dist, INF, sizeof dist);
    dist[source] = 0;
    parent[source] = source;
    queue<int> q;
    q.push(source);

    while(!q.empty()) {
        int u = q.front();
        q.pop();
        for(int v : adjList[u]) {
            if(dist[v] == INF) {
                dist[v] = dist[u] + 1;
                q.push(v);
                parent[v] = u;
            }
        }
    }
}

void printPath(int source, int target) {
    if(source != target) {
        printPath(source, parent[target]);
    }
    printf("%d -> ", target);
}

int main() {

    int v, e;
    cin >> v >> e;

    adjList.resize(v + 10);

    for(int i = 0; i < e; ++i) {
        int u, w;
        cin >> u >> w;
        adjList[u].push_back(w);
    }

    int source = 1, goal = 4;
    cin >> source >> goal;

    bfs(source);
    printPath(source, goal);
    cout << "\n";
    
    return 0;
}
