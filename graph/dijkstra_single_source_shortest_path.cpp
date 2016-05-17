#include <bits/stdc++.h>

#define debug(x) cout << "> " << #x << " = " << x << endl;
#define debugat(arr, at) cout << "> " << #arr << "[" << at << "] = " << arr[at] << endl;

using namespace std;

/* 
 *  Dijkstra algorithm, solves the soungle source shortest path problem
 *    
 *  Intuition:    
 *  d(u, v) = shortest path from u to v;
 *  We want to calculate the shortest path from u, to v;   
 *  Assume that we calculated that the current shortest path to v is W and W is not d(u, v)
 *  We must use other vertices k, such that the current distance to k from source is less then W;
 *  So we explore all path's using k that have distance less than W;
 *  If we find another path to v with total weight less than W, we repeat the process, until we can't make the path to v shorter
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
    priority_queue<ii, vector<ii>, greater<ii> > pq;
    pq.push(ii(0, source));
    while(!pq.empty()) {
        ii top = pq.top();
        pq.pop();
        int w = top.first, u = top.second;
        // if(u == destionation) return dist[destination]; // optional
        for(ii e : adj[u]) {
            if((w + e.second) < dist[e.first]) {
                dist[e.first] = w + e.second;
                parent[e.first] = u;
                pq.push(ii(dist[e.first], e.first));
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
