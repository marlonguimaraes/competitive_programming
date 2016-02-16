#include <bits/stdc++.h>

#define DEBUG
#ifdef DEBUG
    #define debug(x) cout << "> " << #x << " = " << x << endl;
#else
    #define debug(x)
#endif

using namespace std;

/*  Problem: given N coins, the value of the i'th coin is c[i], and an amount of money V, how many ways you can choose coins such that they sum V?
             or, how many ways you can write V as a linear combination of all subsets of N?'
 *           You have an infinite amount of coins of each value.
 *  Solution: DP O(N * V);
 *
 *  Intuition: Supose that there is a way to use i'th coin to represent V.
               Now, the subprolem is: how many ways you can represent V - c[i] considering all coins (including the i'th one)?
               
               If the i'th coin is not used in some representation of V, the subproblem left is:
               how many ways you can represent V cosidering i - 1 coins?
               So you just have to sum the answer for both scenarios.
    
               Why all representations are included in this approach? Because you can assume that given a coin, it's either used or not used in
               some representation. So, if you have the number of combinations to both cases, you have the final solution.
            
     Function : ways(i, value) = ways(i, value - c[i]) + ways(i + 1, value);
                ways(n, value) = 0;
                ways(i, 0) = 1;
    
 */
    

const int INF = 1 << 30;
const int N = 1234;

int n, a[N], c[N], ans = 0;
int dp[N][N];

int waysTopDown(int i, int value) {
    if(i == n or value < 0) return 0;
    if(value == 0) return 1;
    if(dp[i][value] == -1)
        dp[i][value] = waysTopDown(i, value - c[i]) + waysTopDown(i + 1, value);
    return dp[i][value];
}

int waysBottonUp(int value) {
    for(int v = 1; v <= value; ++v)
        dp[0][v] = 0;
    for(int i = 1; i <= n; ++i)
        dp[i][0] = 1;

    for(int i = 1; i <= n; ++i) {
        for(int v = 1; v <= value; ++v) {
            dp[i][v] = dp[i - 1][v];
            if(c[i - 1] <= v)
                dp[i][v] += dp[i][v - c[i - 1]];
        }
    }
    return dp[n][value];
}

int main() {
    //ios_base::sync_with_stdio(false);

    int value;
    cin >> n >> value;
    for(int i = 0; i < n; ++i) cin >> c[i];

    memset(dp, -1, sizeof dp);
    cout << waysTopDown(0, value) << "\n";
    cout << waysBottonUp(value) << "\n";
    return 0;
}
