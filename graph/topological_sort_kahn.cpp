#include <bits/stdc++.h>

#define debug(x) cout << "> " << #x << " = " << x << endl;
#define debugat(arr, at) cout << "> " << #arr << "[" << at << "] = " << arr[at] << endl;

/* TOPOLOGICAL SORT
 * Given DAG (Directed Acyclic Graph) G = (V, E);
 * Topological sort is a linear ordering of all vertices of V such that for every edge (u, v), u must become BEFORE v in the ordering.
 * Every DAG has at least one topological sort.
 * Cyclic graphs contain no topological sort.

 * Let in(u) be the indegree of vertex u.
 * Supose G = (V, E) is a dag, i.e it has at least one topological sort
 * So, there will be at least one vertex u such that in(u) = 0;
 * Kahn's algorithm:
 * Put all vertices u such that in(u) = 0 in a queue (or priority queue if you want the lexicographical order);
 * For every vertex u in the queue:
 *
 * 1) remove the front (top) element. Call it u;
 * 2) put u in a container. This container will be the final odering of vertices.
 * 3) For every neighbor v of u, decrease it's indegree by one;
 * 4) If in(v) becomes 0, enqueue v;
 * 5) Go to step 1) until the queue is not empty.
 *
 * If size of the container is different of |V|, then the graphs contains a cycle;
 *
*/


using namespace std;

const int N = 123;

int v, e;
int in[N];
vector< vector<int> > adj;

vector<int> kahn_sort() {
    priority_queue< int, vector<int>, greater<int> > nextVertex;
    for(int i = 1; i <= v; ++i) { // vertices are 1 indexed, [1, |V|]
        if(in[i] == 0) {
            nextVertex.push(i);
        }
    }
    vector<int> sorted;
    while(!nextVertex.empty()) {
        int u = nextVertex.top();
        nextVertex.pop();
        sorted.push_back(u);
        for(int v : adj[u]) {
            --in[v];
            if(in[v] == 0) {
                nextVertex.push(v);
            }
        }
    }
    return sorted;
}

int main() {
    ios_base::sync_with_stdio(false);
    while(cin >> v >> e) {
        adj.clear();
        adj.resize(v + 10);
        memset(in, 0, sizeof in);
        for(int i = 0; i < e; ++i) {
            int u, v;
            cin >> u >> v;
            adj[u].push_back(v);
            ++in[v];
        }

        vector<int> sorted = kahn_sort();

        for(int k : sorted) {
            cout << k << " ";
        }
        cout << "\n";
    }
    return 0;
}
