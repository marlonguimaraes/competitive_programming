#include <bits/stdc++.h>

#define debug(x) cout << "> " << #x << " = " << x << endl;
#define debugat(arr, at) cout << "> " << #arr << "[" << at << "] = " << arr[at] << endl;
#define debugpair(p) cout << "> " << #p << " = " << "(" << p.first << ", " << p.second << ")" << endl;

using namespace std;

typedef vector<vector<int> > matrix;

// For matrices A, B, they must have dimensions A(n, m) * B(m, p) = AB(n, p) for arbitraty n, p;

inline matrix matrix_mult(const matrix &a, const matrix &b) {
    if(a.empty() or b.empty())
        return matrix();

    int n = a.size(),
        p = b[0].size(),
        m = a[0].size();
    matrix res(n, vector<int>(p));
    
    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < p; ++j) {
            for(int k = 0; k < m; ++k) {
                res[i][j] += a[i][k] * b[k][j];
            }
        }
    }
    return res;
}

inline void print_matrix(const matrix &a) {
    for(auto line : a) {
        for(auto col : line) {
            cout << " " << col;
        }
        cout << "\n";
    }
}

// returns A ^ b, A must be squared
inline matrix matrix_power(matrix a, int b) {
    int n = a.size();
    matrix res(n, vector<int>(n));
    for(int i = 0; i < n; ++i)
        res[i][i] = 1;
    while(b) {
        if(b & 1)
            res = matrix_mult(res, a);
        a = matrix_mult(a, a);
        b >>= 1;
    }
    return res;
}

int main() {
    ios_base::sync_with_stdio(false);

    matrix A({ {1,  2,   4},
               {8,  16,  32},
               {64, 128, 256},
             });

    matrix B({ {2,  3,  5},
               {7,  11, 13},
               {17, 23, 29},
             });

    matrix AB(matrix_mult(A, B));
    print_matrix(AB);
    cout << "\n\n";

    matrix fib_base({ {1,  1},
                      {1,  0},
                   });
    int n = 20;
    fib_base = matrix_power(fib_base, n - 1);
    print_matrix(fib_base);

    return 0;
}
