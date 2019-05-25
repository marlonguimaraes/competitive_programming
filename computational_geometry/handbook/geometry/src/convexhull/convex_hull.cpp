#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int, int> ii;

ll cross(const ii &O, const ii &A, const ii &B){
    return (A.first - O.first) * (B.second - O.second) - (A.second - O.second) * (B.first - O.first);
}

// Return the points of the convex-hull (CH) of P, in the counter-clockwise order.
// The first point of the return value is the left most (smallest x value) point of the CH.
// Each edge of the returned CH contains no 3 collinear points.
// There are no duplicated points in the return value unless the input contains duplicates already
vector<ii> convex_hull(vector<ii> P) {
    int n = P.size(),
        k=0;
    vector<ii> H(2 * n);
    sort(P.begin(), P.end());

    for(int i=0; i<n; ++i){
        while(k >= 2 && cross(H[k-2], H[k-1], P[i]) <= 0) {
            k--;
        }
        H[k++] = P[i];
    }

    for(int i= n - 2, t = k + 1; i >= 0; --i){
        while(k >= t && cross(H[k-2], H[k-1], P[i]) <= 0) {
            k--;
        }
        H[k++] = P[i];
    }
    H.resize(k - 1); // Avoids duplicating the first and last point of the convex hull.
                     // Do H.resize(k) if you want the first and last points of the convex hull to be the same
    return H;
}

inline void print(const vector<ii> &P) {
    cout << "P.size() = " << P.size() << endl;
    cout << "P = ";
    for(auto p : P) {
        cout << "(" << p.first << ", " << p.second << "), ";
    }
    cout << endl;
}

int main() {
    vector<ii> P({
            {1, 9}, {2, 4}, {3, 12}, {4, 2}, {4, 6}, {5, 7}, {5, 14},
            {6, 5}, {6, 9}, {6, 12}, {7, 1}, {7, 8}, {7, 10}, {8, 15},
            {9, 11}, {10, 4}, {11, 3}, {11, 13}, {12, 6}, {12, 9}, {13, 7},
            });
    sort(P.begin(), P.end());
    print(P);

    vector<ii> ch = convex_hull(P);
    print(ch);

    vector<ii> triangle({{1, 3}, {5, 6}, {7, 4}});
    ch = convex_hull(triangle);
    print(ch);
    return 0;
}
