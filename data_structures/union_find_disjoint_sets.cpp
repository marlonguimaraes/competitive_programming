/* Union-find disjoint sets
 * Each set is given a representative (parent), if sizeOfSet(i) == 1, then parent[i] = i;
 *  These sets are stored in a tree-like structure
 *  Main operations are findSet(i) and unionSet(i, j), which are, respectively:
 *      returns the root of the current i's tree
 *      make sets i and j share the same root in a new tree,
 *
 *  This data structure is optimized using heuristics of rank and path compression
 *  rank: when unionSet(i, j) is called, if they are from different sets (trees),
 *        a new tree will be made, trying to reduce the new tree's rank, if possible.
 *        This is made by making the tree with lower rank point to the root of the tree if higher rank.
 *        This will make future queries faster since you'll have a tree if lower rank, you'll reach it's root faster.
 *  path compression:
 *          since the goal is to reach the root as soon as possible, to know which set a given element is located,
 *          let's make all nodes point directly to the root. We do this in findSet(i) recursive function,
 *          making parent[i] = findSet(parnet[i]);
 *          After enough queries, the tree will have rank 1, making queries in O(1).
 */

#include <bits/stdc++.h>

using namespace std;

const int N = 12345;

struct UFDS {

    int parent[N], rank[N],
        numElements[N],
        size, numDisjoint;

    UFDS(int n) {
        size = numDisjoint = 0;
        for(int i = 1; i <= n; ++i)
            makeSet(i);
    }

    void makeSet(int i) {
        parent[i] = i;
        rank[i] = 0;
        numElements[i] = 1;
        ++size;
        ++numDisjoint;
    }

    int findSet(int i) {
        return parent[i] == i ? i : (parent[i] = findSet(parent[i]));
    }

    bool isSameSet(int i, int j) {
        return findSet(i) == findSet(j);
    }

    int sizeOfSet(int i) {
        return numElements[findSet(i)];
    }

    void unionSet(int i, int j) {
        if(!isSameSet(i, j)) {
            --numDisjoint;
            int pi = findSet(i), pj = findSet(j);

            if(rank[pi] > rank[pj]) {
                parent[pj] = pi;
                numElements[pi] += numElements[pj];
            }
            else {
                numElements[pj] += numElements[pi];
                parent[pi] = pj;
                if(rank[pi] == rank[pj]) ++rank[pj];
            }
        }
    }
};

int main() {
    int n = 7;
    UFDS ufds(n);

    ufds.makeSet(8);
    for(int i = 1; i <= n + 1; ++i) {
        if(i & 1) ufds.unionSet(i, 1);
        else ufds.unionSet(i, 2);
    }

    for(int i = 1; i <= n + 1; ++i) {
        printf("parent[%d] = %d\n", i, ufds.findSet(i));
    }

    printf("numDisjoint sets = %d\n", ufds.numDisjoint);

    ufds.unionSet(1, 2);

    printf("numDisjoint sets = %d\n", ufds.numDisjoint);
    printf("numElements[%d] = %d\n", 1, ufds.sizeOfSet(1));
    printf("numElements[%d] = %d\n", 2, ufds.sizeOfSet(2));
    return 0;
}
