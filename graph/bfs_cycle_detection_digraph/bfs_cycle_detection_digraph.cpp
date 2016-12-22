#include <bits/stdc++.h>

#define fori(i, ini, lim) for(int i = int(ini); i < int(lim); i++)
#define ford(i, ini, lim) for(int i = int(ini); i >= int(lim); i--)

#define debug(x) cout << "> " << #x << " = " << x << endl;
#define debug_at(arr, at) cout << "> " << #arr << "[" << at << "] = " << arr[at] << endl;
#define debug_pair(p) cout << "> " << #p << " = (" << p.first << ", " << p.second << ")" << endl;

using namespace std;

const int N = 1e4;

vector<int> adj[N];

int V, E;

int vis[N];
bool dfs(int u) {
    bool cycle = false;
    vis[u] = 1;
    for(int v : adj[u]) {
        if(vis[v] == 0) {
            cycle = cycle or dfs(v);
        }
        else if(vis[v] == 1) {
            cycle = true;
        }
    }
    vis[u] = 2;
    return cycle;
}

int main() {
    ios_base::sync_with_stdio(false);

    cin >> V >> E;

    fori(i, 0, E) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
    }

    bool cyclic = false;
    fori(u, 1, V) {
        if(!vis[u] and !cyclic) {
            cyclic = dfs(u);
        }
    }
    debug(cyclic);
    return 0;
}
