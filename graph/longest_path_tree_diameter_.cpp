#include <bits/stdc++.h>

#define debug(x) cout << "> " << #x << " = " << x << endl;
#define debugat(arr, at) cout << "> " << #arr << "[" << at << "] = " << arr[at] << endl;

/* Longest-Path problem
 * The longest path in a general graph G(V, E) is NP-Hard;
 * If the graph is a tree (undirected, acyclic, connected graph);
 * There is a linear solution
 *
 * Let T = (V, E) be a tree
 * 1) Run BFS from a random node 'w'. Find the furthermost node from 'w', call it 'u';
 * 2) Run BFS from the node 'u'. Find the furthermost node from 'u', let's call it 'v';
 * 3) The dist between 'u', and 'v' is a longest-path in T. (There can more than one longest path).
 *
 * The proof is tedious as fuck (a.k.a left as an exercise to the reader) but is proven by contradiction
 * Link to the proof: https://www.quora.com/How-does-following-algorithm-for-finding-longest-path-in-tree-work
 */

using namespace std;

const int N = 1234;

vector< vector<int> > adjList; // directed graph representation of a tree
int dist[N];         // A tree is acyclic but the above representation cointains cycles. This array will prevent them.

int bfsFurthermost(int source, int &maxDistance) { // returns the furthermost node from souce;
                                                    // maxDistance is the dist between those nodes;
    memset(dist, 0, sizeof dist);
    maxDistance = dist[source] = 0;

    int u = source;
    queue<int> q;
    q.push(source);

    while(!q.empty()) {
        int next = q.front();
        q.pop();
        for(int v : adjList[next]) {
            if(!dist[v]) {
                q.push(v);
                dist[v] = dist[next] + 1;
                if(dist[v] > maxDistance) {
                    maxDistance = dist[v];
                    u = v;
                }
            }
        }
    }
    return u;
}

int treeLongestPath(int source) {
    int maxDistance = -1;                       // source can by any node in the tree;
    int u = bfsFurthermost(source, maxDistance);
    int v = bfsFurthermost(u, maxDistance);
    return maxDistance;                         // path u -> v is a longest path in the tree;
}

int main() {
    ios_base::sync_with_stdio(false);

    int v, e;
    while(cin >> v >> e) {
        int source; // source is arbitrary
        adjList.clear();
        adjList.resize(v + 10);
        for(int i = 0; i < e; ++i) {
            int u, v;
            cin >> u >> v;
            source = u;
            adjList[u].push_back(v);
            adjList[v].push_back(u);
        }
        cout << "Longest path in the tree = " << treeLongestPath(source) << "\n";
    }
    return 0;
}
