#include <bits/stdc++.h>

using namespace std;

const int MAX = 500;
const int INF = 1 << 30;

int a[MAX][MAX];

int max1D(const vector<int> &b) {
    int sum = b[0], maxSum = sum;
    for(int i = 1; i < (int) b.size(); ++i) {
        sum = max(b[i], sum + b[i]);
        maxSum = max(maxSum, sum);
    }
    return maxSum;
}

int max2D(int m, int n) {
    int maxSum = -INF;
    for(int i = 0; i < n; ++i) {
        vector<int> b(m);
        for(int j = i; j < n; ++j) {
            for(int k = 0; k < m; ++k) {
                b[k] += a[k][j];
            }
            maxSum = max(maxSum, max1D(b));
        }
    }
    return maxSum;
}

void printMatrix(int m, int n) {
    for(int i = 0; i < m; ++i) {
        for(int j = 0; j < n; ++j)
            cout << a[i][j] << " ";
        cout << "\n";
    }
}

int main() {

    int n, m;
    cin >> m >> n;

    for(int i = 0; i < m; ++i)
        for(int j = 0; j < n; ++j)
            cin >> a[i][j];

    cout << "max2D for:\n";
    printMatrix(m, n);
    cout << " = " << max2D(m, n) << "\n";

    return 0;
}
