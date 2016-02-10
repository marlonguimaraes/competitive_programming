#include <bits/stdc++.h>

#define DEBUG
#ifdef DEBUG
    #define debug(x) cout << "> " << #x << " = " << x << endl;
#else
    #define debug(x)
#endif

using namespace std;

const int MAX = 1e5;

int a[MAX], dp[MAX], parent[MAX];

int lis(int size, int &maxEnding) {
    int maxLen = 0;
    dp[0] = 1;
    parent[0] = 0;
    for(int i = 1; i < size; ++i) {
        dp[i] = 1;
        parent[i] = i;
        for(int j = 0; j < i; ++j) {
            if(a[i] > a[j] and dp[j] + 1 > dp[i]) {
                dp[i] = dp[j] + 1;
                parent[i] = j;
            }
            if(dp[i] > maxLen) {
                maxLen = dp[i];
                maxEnding = i;
            }
        }
    }
    return maxLen;
}

void constructSolution(int maxEnding) {
    int next = maxEnding;
    stack<int> s;
    for(s.push(next); next != parent[next]; s.push(next))
        next = parent[next];
    for( ; !s.empty(); s.pop())
        cout << a[s.top()] << " ";
    cout << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    int n, maxEnding;
    cin >> n;

    for(int i = 0; i < n; ++i)
        cin >> a[i];
    
    cout << "lis = " << lis(n, maxEnding) << "\n";
    cout << "solution = ";
    constructSolution(maxEnding);

    return 0;
}
