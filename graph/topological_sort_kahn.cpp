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

class Solution {
public:
    vector<int> findOrder(int numCourses, vector<vector<int>>& prerequisites) {
        vector<int> indegree(numCourses);
        vector<vector<int>> adj(numCourses);
        for(const auto &p : prerequisites) {
            adj[p[1]].push_back(p[0]);
            indegree[p[0]]++;
        }
        
        vector<int> q;
        for(int u = 0; u < numCourses; u++) {
            if(indegree[u] == 0) {
                q.push_back(u);
            }
        }
        vector<int> res;
        while(!q.empty()) {
            const int u = q.back();
            q.pop_back();
            res.push_back(u);
            
            for(const int &v : adj[u]) {
                indegree[v]--;
                if(indegree[v] == 0) {
                    q.push_back(v);
                }
            }
        }
        if((int) res.size() != numCourses) {
            res.clear();
        }
        return res;
    }
};
