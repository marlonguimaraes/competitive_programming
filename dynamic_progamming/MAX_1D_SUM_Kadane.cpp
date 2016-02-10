#include <bits/stdc++.h>

using namespace std;

// works even if all elements of the array is negative;
int maxSum(vector<int> &a) {
    int sum = a[0], maxS = sum;
    for(int i = 1; i < (int) a.size(); ++i) {
        sum = max(a[i], sum + a[i]);
        maxS = max(maxS, sum);
    }
    return maxS;
}

int main() {
    int n;
    cin >> n;

    vector<int> a(n);
    for(int i = 0; i < n; ++i) cin >> a[i];
    
    cout << "maxSum = " << maxSum(a) << "\n";
    
    return 0;
}
