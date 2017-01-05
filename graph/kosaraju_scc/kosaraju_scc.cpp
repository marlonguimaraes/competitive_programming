// SPOJ: WEBISL - Web islands
#include <bits/stdc++.h>

#define fori(i, ini, lim) for(int i = int(ini); i < int(lim); i++)
#define ford(i, ini, lim) for(int i = int(ini); i >= int(lim); i--)

#define debug(x) cout << "> " << #x << " = " << x << endl;
#define debug_at(arr, at) cout << "> " << #arr << "[" << at << "] = " << arr[at] << endl;
#define debug_pair(p) cout << "> " << #p << " = (" << p.first << ", " << p.second << ")" << endl;

using namespace std;

const int N = 123456;

vector<int> adj[N];

int V, E;

int vis[N];
list<int> ord;

void dfs1(int u) {
    vis[u] = 1;
    for(int v : adj[u]) {
        if(vis[v] == 0) {
            dfs1(v);
        }
    }
    ord.insert(ord.begin(), u);
}

vector<int> trans[N];
void dfs2(int u, vector<int>& component) {
    vis[u] = 2;
    component.push_back(u);
    for(int v : trans[u]) {
        if(vis[v] != 2) {
            dfs2(v, component);
        }
    }
}

vector<vector<int> > components;
void scc() {
    fori(u, 0, V) {
        if(vis[u] != 1) {
            dfs1(u);
        }
    }
    for(int u : ord) {
        if(vis[u] != 2) {
            vector<int> component;
            dfs2(u, component);
            components.push_back(component);
        }
    }
}

void solve() {
    scc();
    int ans[N];
    for(const vector<int>& component : components) {
        int mini = 1 << 30;
        for(int u : component) {
            mini = min(mini, u);
        }
        for(int u : component) {
            ans[u] = mini;
        }
    }
    fori(u, 0, V) {
        cout << ans[u] << "\n";
    }
}

int main() {
    ios_base::sync_with_stdio(false);

    cin >> V >> E;
    fori(i, 0, E) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        trans[v].push_back(u);
    }

    solve();

    return 0;
}
