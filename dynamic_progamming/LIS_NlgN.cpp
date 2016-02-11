#include <bits/stdc++.h>

#define DEBUG
#ifdef DEBUG
    #define debug(x) cout << "> " << #x << " = " << x << endl;
#else
    #define debug(x)
#endif

using namespace std;

const int MAX = 1e5;
vector<int> parent;

int lis(const vector<int> &v, int &maxEnding) {
    int size = 0;
    vector<int> idPos(v.size()),
                a(v.size());
    parent.resize(v.size());

    for(int i = 0; i < (int) v.size(); ++i) {
        int at = lower_bound(a.begin(), a.begin() + size, v[i]) - a.begin();
            // USE lower_bound for strictly increasing subsequence
        //int at = upper_bound(a.begin(), a.begin() + size, v[i]) - a.begin();
            // USE upper_bound for non-decreasing subsequence (equal elements are allowed)
        a[at] = v[i];
        idPos[at] = i;
        parent[i] = at ? idPos[at - 1] : i;
        if(at == size) {
            ++size;
            maxEnding = i;
        }
    }
    return size;
}

void constructSolution(const vector<int> &v, int next) {
    stack<int> s;
    for(s.push(next); next != parent[next]; s.push(next))
        next = parent[next];
    for( ; !s.empty(); s.pop())
        cout << v[s.top()] << "\n";
}

void printVec(const vector<int> &v) {
    for(int k : v) cout << k << " ";
    cout << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);

    int n, maxEnding;
    cin >> n;
    vector<int> v(n);
    for(int i = 0; i < n; ++i)
        cin >> v[i];
    
    printVec(v);

    cout << "lis = " << lis(v, maxEnding) << "\n";
    cout << "solution = ";
    constructSolution(v, maxEnding);

    return 0;
}
