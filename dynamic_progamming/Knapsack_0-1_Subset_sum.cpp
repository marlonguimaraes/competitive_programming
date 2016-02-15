#include <bits/stdc++.h>

#define DEBUG
#ifdef DEBUG
    #define debug(x) cout << "> " << #x << " = " << x << endl;
#else
    #define debug(x)
#endif

using namespace std;

/* 
    Problem: given N itens, the i'th iten weight is w[i], it's value is v[i], and a maximum capacity W, what is the maximum value you can get
             using some (or all) of the N itens without exceding W?
    
    Solution: Dynammic Progamming O(N * W);
            
    Intuition: For each item i, you have 2 options: take it, or leave it!

               Assume that taking the i'th is the optimal choice for the final solution
               After taking item i, there is (remW - w[i]) weight left to represent.
               Since we assume that this is part of the optimal solution, the solution for the (remW - w[i]) must also be optimal.
               This is the problem optimal substructure. (Formal proof is by contradiction).
               So, the solution for taking i'th item is knapsack(i, remW) = knapsack(i + 1, remW - w[i]) + v[i];
               Of course, if i == n or w[i] > remW, the answer is 0, since we neither have more itens to consider nor space left to use.
            
               For the second scenario (not taking the i'th item) the solution is obvious, just go to the next item.
               knapsack(i, remW) = knapsack(i + 1, remW);
               (Base cases are the same as the first scenario).
               The solution for (i + 1, remW) must also be optimal.
    
    Optimal substructure: the optimal solution for knapsack(i, remW) uses the optimal solution for knapsack(i + 1, remW - w[i]),
                          or the optimal solution for knapsack(i + 1, remW);
    Problem overlapping:  The are 2 ** n choices (all the subsets of n).
                          This is naive because some of the subsets uses more than W weight.
                          In fact, we can only represent all the weights in the interval [0, W], using only all itens i [0, n],
                          so there are only n * W possible scenarios.
                          Some of those scenarios are used more than once.
    
    Final solution:
                Best of taking i'th or item, or leavint it.
                knapsack(i, remW) = max(knapsack(i + 1, remW),
                                        knapsack(i + 1, W - w[i]) + v[i]);
                or

                knapsack(i, remW) = 0, if i == n, remW == 0 or w[i] > remW;
    PS: Top-down is usually faster. Since it will visit only necessary states. Botton-up will visist all.
            
 */


const int N = 1234;

int dp[N][N],
    w[N], v[N],
    n, total;

// solution = knapDown(0, W);
// 1 indexed for practical reason
int knapDown(int i, int remW) {
    if(i > n or remW == 0) return 0;
    if(dp[i][remW] != -1)   return dp[i][remW];
    if(w[i] > remW)         return knapDown(i + 1, remW);
    return dp[i][remW] = max(knapDown(i + 1, remW),
                             knapDown(i + 1, remW - w[i]) + v[i]);
}

// solution = dp[n][totalW];
// 1 indexed for practical reason
int knapUp(int n, int totalW) {
    for(int i = 0; i <= n; ++i) {
        for(int j = 0; j <= totalW; ++j) {
            if(i == 0 or j == 0)
                dp[i][j] = 0;
            else if(w[i] > j)
                dp[i][j] = dp[i - 1][j];
            else
                dp[i][j] = max(dp[i - 1][j], dp[i - 1][j - w[i]] + v[i]);
        }
    }
    return dp[n][totalW];
}

int main() {
    ios_base::sync_with_stdio(false);

    memset(dp, -1, sizeof dp);
    cin >> n >> total;
    for(int i = 1; i <= n; ++i) cin >> w[i];
    for(int i = 1; i <= n; ++i) cin >> v[i];

    cout << knapDown(0, total) << "\n";
    cout << knapUp(n, total) << "\n";

    return 0;
}
