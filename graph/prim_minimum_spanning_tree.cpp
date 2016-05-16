#include <bits/stdc++.h>

#define debug(x) cout << "> " << #x << " = " << x << endl;
#define debugat(arr, at) cout << "> " << #arr << "[" << at << "] = " << arr[at] << endl;

using namespace std;

/* 
 *  
 */

const int N = 12345;

typedef pair<int, int> ii;
typedef pair<int, ii> tri;

vector< vector<ii> > adj;
priority_queue<ii, vector<ii>, greater<ii> > pq;
int V, E;
bool onTree[N], parent[N];

void process(int u) {
    onTree[u] = true;
    for(ii e : adj[u]) {
        int v = e.first, w = e.second;
        if(!onTree[v])
            pq.push(ii(w, v));
    }
}

int prim(int root) {
    int mst_cost = 0;
    memset(onTree, 0, sizeof onTree);
    process(root);
    parent[root] = root;
    while(!pq.empty()) {
        ii top = pq.top();
        pq.pop();
        int w = top.first, u = top.second;
        if(!onTree[u]) {
            mst_cost += w;
            process(u);
        }
    }
    return mst_cost;
}

int main() {

    // G must be a connected, undirected graph
    scanf("%d %d", &V, &E);

    adj.resize(V + 5);
    for(int i = 0; i < E; ++i) {
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);
        adj[u].push_back(ii(v, w));
        adj[v].push_back(ii(u, w));
    }

    int root = 1;
    int mst_cost = prim(root);
    printf("mst_cost = %d\n", mst_cost);

    return 0;
}
