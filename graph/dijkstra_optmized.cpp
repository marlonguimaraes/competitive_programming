#include <bits/stdc++.h>

#define debug(x) cout << "> " << #x << " = " << x << endl;
#define debugat(arr, at) cout << "> " << #arr << "[" << at << "] = " << arr[at] << endl;

using namespace std;

/* 
*/

const int N = 12345;
const int INF = (1 << 29); // worst case = (2 ^ 29) + (2 ^ 29) = (2 ^ 30)

typedef pair<int, int> ii;
typedef pair<int, ii> tri;

vector< vector<ii> > adj;

int V, E;

vector<int> dist;
int parent[N];

int dijkstra(int source, int destination) {
    dist.resize(V + 5, INF);                            // at the end, dist[u] = shortest path from source to u;
    memset(parent, -1, sizeof parent);                  // base case, vertices have no parent;
    dist[source] = 0;                                   // base case = dist[source] = 0;
    set<ii> active_vertices;
    active_vertices.insert(ii(0, source));

    while(!active_vertices.empty()) {
        ii next = *active_vertices.begin();
        active_vertices.erase(active_vertices.begin());
        int w = next.first, u = next.second;
        // if(u == destionation) return dist[destination]; // optional
        for(ii e : adj[u]) {
            if((w + e.second) < dist[e.first]) {
                active_vertices.erase({dist[e.first], e.first});
                active_vertices.insert({w + e.second, e.first});
                dist[e.first] = w + e.second;
                parent[e.first] = u;
            }
        }
    }
    return dist[destination];
}

void printDist(int source) {
    for(int u = 1; u <= V; ++u) {
        printf("Shortest path from [%d] to [%d] = %d\n", source, u, dist[u]);
    }
}

void printPath(int u) {
    if(parent[u] == -1) {
        printf(" %d", u);
    }
    else {
        printPath(parent[u]);
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

    int source = 1, destination = 4;
    dijkstra(source, destination);
    printDist(source);
    printPath(destination);
    puts("");
   return 0;
}
