#include <bits/stdc++.h>

#define debug(x) cout << "> " << #x << " = " << x << endl;
#define debugat(arr, at) cout << "> " << #arr << "[" << at << "] = " << arr[at] << endl;

using namespace std;

/* 
 *  
 */

const int N = 12345;

class UFDS {
public:
    int rank[N], parent[N];

    UFDS(int size) {
        memset(rank, 0, sizeof rank);
        for(int i = 1; i <= size; ++i)
            parent[i] = i;
    }

    int getParent(int i) {
        return i == parent[i] ? i : parent[i] = getParent(parent[i]);
    }

    bool sameSet(int i, int j) {
        return getParent(i) == getParent(j);
    }

    void unionSet(int i, int j) {
        if(!sameSet(i, j)) {
            int pi = getParent(i), pj = getParent(j);
            if(rank[pi] > rank[pj]) {
                parent[pj] = pi;
            }
            else {
                parent[pi] = pj;
                if(rank[pi] == rank[pj])
                    ++rank[pj];
            }
        }
    }
};

typedef pair<int, int> ii;
typedef pair<int, ii> tri;

int V, E;

int main() {

    // G must be a connected, undirected graph
    scanf("%d %d", &V, &E);

    vector<tri> edges;
    for(int i = 0; i < E; ++i) {
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);
        edges.push_back(tri(w, ii(u, v)));
    }
    sort(edges.begin(), edges.end());
    UFDS ufds(V);
    int mst_cost = 0;
    for(tri edge : edges) {
        int w = edge.first;
        int u = edge.second.first,
            v = edge.second.second;
        if(!ufds.sameSet(u, v)) {
            ufds.unionSet(u, v);
            mst_cost += w;
        }
    }

    printf("mst_cost = %d\n", mst_cost);

    return 0;
}
