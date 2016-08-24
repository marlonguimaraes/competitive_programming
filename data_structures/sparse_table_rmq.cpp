#include <bits/stdc++.h>

#define debug(x) cout << "> " << #x << " = " << x << endl;
#define debugat(arr, at) cout << "> " << #arr << "[" << at << "] = " << arr[at] << endl;
#define debugpair(p) cout << "> " << #p << " = " << "(" << p.first << ", " << p.second << ")" << endl;

using namespace std;

/*
 *	Sparse table - RMQ (Range minimum query);
 *	RMQ(i, j) = minimum element's index in the range [i, j]
 *	
 *	SPARSE TABLE = M[i][j] O(NlgN);
 *	M[i][j] = index of the minimum element in the interval [i, i + (2 ^ j) - 1]
 *  (Subarray starting at i, with length 2 ^ j (including i));

 *  Note that we can divide the subarray in two parts of (2 ^ (j - 1)),
 *  since (2 ^ (j - 1)) + (2 ^ (j - 1)) = 2 ^ j
 *  So we can safely say that the minimum element in the subarray,
 *  starting at i, with length 2 ^ j, is either in the first or second half;
 *
 *  This observation leads to a recursion:
 *	M[i][j] = M[i][j - 1], or				// first half of the subarray
 *			  M[i + 2 ^ (j - 1)][j - 1]		// seocnd half of the subarray;
 *		
 *	Note that the base case is j == 0, So M[i][0] = i;
 *
 *  RMQ(i, j);
 *	Using the sparse table M[i][j], we can then get RMQ(i, j) in O(1);
 *	
 *	RMQ(i, j) = M[i][k], or
 *	            M[j - 2 ^ k + 1][k]
 *	for k = log_2(j - i + 1);

 *	if (j - i + 1) is a power of two, we have floor(k) = k, and M[i][k] will correctly give the answer;

 *	If it's not a power of two, we have 
 *	k = floor(log_2(j - i + 1));
 *	since k is "floored", 2 ^ k < (j - i + 1) < 2 ^ (k + 1)
 *	Once we take 2 subarrays of length 2 ^ k, one starting at i, and the second starting at (j - 2 ^ k + 1);
 *	We will definetly have an overlap inside [i, j], since 2 * (2 ^ k) = 2 ^ (k + 1) < (j - i + 1),
 *	thus, it's guaranted that the whole interval [i, j] is covered by both arrays;
 *	It's also important to see that, although the sum of length of both arrays is greater than (j - i + 1),
 *	no element outside [i, j] will be considered in the RMQ(i, j) query because both subarrays have an overlap

 */

inline int log_2(int i) {
	return 31 - __builtin_clz(i);
}

const int N = 1e5 + 10;
const int LOG_N = 32;

int M[N][LOG_N];
int arr[N];
int n;


inline void build_sparse_table() {
	for(int i = 0; i < n; ++i) {
		M[i][0] = i;
	}
	for(int j = 1; (1 << j) <= n; ++j) {
		for(int i = 0; (i + (1 << j) - 1) < n; ++i) {
			int index_first_half = M[i][j - 1];
			int index_second_half = M[i + (1 << (j - 1))][j - 1];
			int &res = M[i][j];
			if(arr[index_first_half] < arr[index_second_half])
				res = index_first_half;
			else
				res = index_second_half;
		}
	}
}

inline int rmq(int i, int j) {
	int k = log_2(j - i + 1);
	int index_first_half = M[i][k];
	int index_second_half = M[j - (1 << k) + 1][k];
	int res = 0;
	if(arr[index_first_half] < arr[index_second_half])
		res = index_first_half;
	else
		res = index_second_half;
	return res;
}

int main() {

	scanf("%d", &n);
	for(int i = 0; i < n; ++i)
		scanf("%d", arr + i);

	build_sparse_table();

	int queries;
	scanf("%d", &queries);

	for(int q = 0; q < queries; ++q) {
		int i, j;
		scanf("%d %d", &i, &j);
		int ans = arr[rmq(i, j)];
		printf("%d\n", ans);
	}


    return 0;
}
