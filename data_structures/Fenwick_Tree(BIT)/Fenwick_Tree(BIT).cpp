#include <bits/stdc++.h>

#define debug(x) cout << "> " << #x << " = " << x << endl;
#define debug_at(arr, at) cout << "> " << #arr << "[" << at << "] = " << arr[at] << endl;
#define debug_pair(p) cout << "> " << #p << " = (" << p.first << ", " << p.second << ")" << endl;

using namespace std;

const int N = 1e5 + 23;

/**
 * Let pos be the position (0 indexed) of the least significant bit
 * which is set (1) in binary representation of i
 * lsb(i) returns 2 ^ pos
 * i > 0

 * EXAMPLES
 * i = 22 = 10110 (binary)
 * pos = 1
 * lsb(22) = 2 ^ 1 = 2
 */
inline int lsb(int i) {
    return (i & (-i));
}

/**
 * ft[i] is responsable for sum in interval [i - lsb(i) + 1, i]
 * Examples: ft[14] = sum[14 - 2 + 1, 14] = [13, 14]
 *           ft[16] = sum[16 - 16 + 1, 16] = [1, 16]
 *           ft[11] = sum[11 - 1 + 1, 11] = [11], 11]
 * note that ft[i] is always responsable for a subarray whose length is a power of two
 * this subarray "ends" with i'th element (including it), and starts at [i - somePowerOfTwo + 1, i]
 */
int ft[N];

// Sum of all elements in interval [1, b]
inline int sum(int b) {
    int res = 0;
    while(b > 0) {
        res += ft[b];
        b -= lsb(b);
    }
    return res;
}

// Sum of all elements in interval [a, b]
inline int sum(int a, int b) {
    return sum(b) - sum(a - 1);
}

// Adds k to all subarrays which are responsable for i
inline void update(int i, int k) {
    while(i < N) {
        ft[i] += k;
        i += lsb(i);
    }
}

/* Intuition for sum(b):
 * If ft[i] is responsable for [i - lsb(i) + 1, i]
 * This means that to the final answer = res for sum(b) we add ft[i]
 * The next interval which was not covered is [i - lsb(i) + 1 - 1] = [i - lsb(i)]
 *
 * Examples: ft[14] = is responsable for [14 - 2 + 1, 14] = [13, 14]
 *
 * So we add ft[14] to the answer. The next non covered-interval ends at [13 - 1] = [12] = [14 - lsb(14)]
 * Add everything ft[12] is responsable for and move to the next non covered interval
 * ft[12] covers [9, 12], the next is interval ends with [8] = [12 - lsb(12)], add ft[12] to the answer
 * ft[8] covers [1, 8] = [8 - lsb(8) + 1], add ft[8], algorithm ends
 *
 * Since all intervals are disjoint and subsequent, sum(b) calculates sum[1, n]
 */

int main() {

    vector<int> arr({7, 3, -5, 16, 11, 0});
    for(int i = 0; i < (int) arr.size(); ++i) {
        update(i + 1, arr[i]);
    }

    // All operations are 1 indexed
    int n = arr.size();
    debug(sum(n));
    debug(sum(1, n));
    debug(sum(3, 4));
    debug(sum(n, n));

	return 0;
}
