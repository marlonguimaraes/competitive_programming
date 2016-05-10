#include <bits/stdc++.h>

#define debug(x) cout << "> " << #x << " = " << x << endl;
#define debugat(arr, at) cout << "> " << #arr << "[" << at << "] = " << arr[at] << endl;

using namespace std;

typedef vector<int> vi;
typedef pair<int, int> ii;


const int N = 100056;

int V, E;
int num[N], low[N];
bool on[N];

vi in;
vector<vi> adj;
vector<vi> dag;
vector<vi> components;

void scc(int u, int &dfs_t, stack<int> &dfs_s) {
    num[u] = low[u] = ++dfs_t;
    dfs_s.push(u);
    on[u] = true;

    for(int v : adj[u]) {
        if(num[v] == -1)
            scc(v, dfs_t, dfs_s);
        if(on[v])
            low[u] = min(low[u], low[v]);
    }
    if(num[u] == low[u]) {
        vi next;
        while(true) {
            int v = dfs_s.top();
            dfs_s.pop();
            on[v] = false;
            next.push_back(v);
            if(u == v)
                break;
        }
        components.push_back(next);
    }
}

void makeDag() {
    vector<int> getComponent(V + 5);

    for(int i = 0; i < (int) components.size(); ++i) {
        for(int u : components[i])
            getComponent[u] = i;
    }

    set<ii> edges;
    for(vi next : components) {
        for(int u : next) {
            for(int v : adj[u]) {
                if(getComponent[u] != getComponent[v])
                    edges.insert(ii(getComponent[u], getComponent[v]));
            }
        }
    }

    dag.clear();
    dag.resize(components.size());
    in.clear();
    in.resize(components.size());

    for(ii p : edges) {
        dag[p.first].push_back(p.second);
        ++in[p.second];
    }
}

vi topological() {

    queue<int> q;
    for(int i = 0; i < (int) components.size(); ++i) {
        if(in[i] == 0)
            q.push(i);
    }

    vi sortedDag;
    while(!q.empty()) {
        int u = q.front();
        q.pop();
        sortedDag.push_back(u);
        for(int v : dag[u])
            if(--in[v] == 0)
                q.push(v);
    }
    return sortedDag;
}

int main() {

    scanf("%d %d", &V, &E);

    adj.clear();
    adj.resize(V + 5);

    for(int i = 0; i < E; ++i) {
        int u, v;
        scanf("%d %d", &u, &v);
        adj[u].push_back(v);
    }

    memset(num, -1, sizeof num);
    memset(low, -1, sizeof low);
    memset(on, 0, sizeof on);
    components.clear();

    int dfs_t = 0;
    stack<int> dfs_s;

    for(int u = 1; u <= V; ++u) {
        if(num[u] == -1)
            scc(u, dfs_t, dfs_s);
    }

    makeDag();
    vi sortedDag = topological();

    for(int i = 0; i < (int) components.size(); ++i) {
        printf("SCC[%d] =", i);
        for(int u : components[i])
            printf(" %d", u);
        puts("");
    }

    printf("Sorted dag:");
    for(int u : sortedDag)
        printf(" %d", u);
    puts("");

    return 0;
}
