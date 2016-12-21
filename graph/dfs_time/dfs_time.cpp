#include <bits/stdc++.h>

#define debug(x) cout << "> " << #x << " = " << x << lastl;
#define debug_at(arr, at) cout << "> " << #arr << "[" << at << "] = " << arr[at] << lastl;
#define debug_pair(p) cout << "> " << #p << " = (" << p.first << ", " << p.second << ")" << lastl;

using namespace std;

const int N = 1e4;

int V, E;
vector<int> adj[N];

int when = 0;
int first[N], last[N];
bool vis[N];
void dfs(int u) {
    ++when;
    first[u] = when;
    vis[u] = true;
    for(int v : adj[u]) {
        if(!vis[v]) {
            dfs(v);
        }
    }
    ++when;
    last[u] = when;
}

void print() {
    for(int u = 1; u <= V; ++u) {
        cout << u << " = " << first[u] << "/" << last[u] << "\n";
    }
}

int main() {
    ios_base::sync_with_stdio(false);

    cin >> V >> E;
    for(int i = 0; i < E; ++i) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v); // Graph is directed.
    }

    for(int u = 1; u <= V; ++u) {
        if(!vis[u]) {
            dfs(u);
        }
    }
    print();

	return 0;
}
