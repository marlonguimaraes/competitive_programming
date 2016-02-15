#include <bits/stdc++.h>

#define DEBUG
#ifdef DEBUG
    #define debug(x) cout << "> " << #x << " = " << x << endl;
#else
    #define debug(x)
#endif

using namespace std;

/*  Problem: given N coins, the value of the i'th coin is c[i], and an amount of money V, what is the minimum number of coins that sum up V?
 *           You have an infinite amount of coins of each value.
 *  Solution: DP O(N * V);
 *
 *  Intuition: Supose that the i'th coin is used in the optimal solution to represent V.
 *             After using the coin for the first time (you can use multiple times) you have (V - c[i]) money left to represent.
 *             The solution for the subproblem (V - c[i]) must also be optimal. otherwise we could make a better solution (contradiction).
 *  
 *             Of course you don't know beforehand which coin will be used, so that's why you use DP: just try all of the coins and save
 *             the minium value;
 *              
 *             coins(V) = coins(V - c[i]) + 1, for every i such that c[i] <= V;
 *             coins(0) = 0;
 */
    

const int INF = 1 << 30;
const int N = 123456;

int n, dp[N], c[N];

int coinsTopDown(int value) {
    if(value == 0) return 0;
    if(value < 0) return INF;
    if(dp[value] != -1) return dp[value];

    dp[value] = INF;
    for(int i = 0; i < n; ++i)
        dp[value] = min(dp[value], coinsTopDown(value - c[i]) + 1);
    return dp[value];
}

int coinsBottonUp(int value) {
    dp[0] = 0;
    for(int v = 1; v <= value; ++v) {
        dp[v] = INF;
        for(int i = 0; i < n; ++i)
            if(c[i] <= v)
                dp[v] = min(dp[v], dp[v - c[i]] + 1);
    }
    return dp[value];
}

int main() {
    //ios_base::sync_with_stdio(false);

    memset(dp, -1, sizeof dp);
    int value;
    cin >> n >> value;

    for(int i = 0; i < n; ++i) cin >> c[i];

    printf("coinTopDown(%d) = %d\n", value, coinsTopDown(value));
    printf("coinBottonUp(%d) = %d\n", value, coinsBottonUp(value));

    return 0;
}
