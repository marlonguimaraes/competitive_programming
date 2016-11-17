// SPOJ - INVCNT

#include <bits/stdc++.h>

#define debug(x) cout << " >>> " << #x << " = " << x << endl
#define debug_at(arr, at) cout << " >>> " << #arr << "[" << at << "] = " << arr[at] << endl

using namespace std;

typedef long long ll;

// Sorts array in interval [left, right]
inline ll merge(vector<int>& arr, int left, int right) {

    int mid = (left + right) / 2;

    int left_index = left;
    int right_index = mid + 1;
    ll inv_cont = 0;
    vector<int> merged_arr;

    while(left_index <= mid and right_index <= right) {
        if(arr[left_index] <= arr[right_index]) {
            merged_arr.push_back(arr[left_index]);
            ++left_index;
        }
        else {
            merged_arr.push_back(arr[right_index]);
            ++right_index;

            inv_cont += (mid - left_index + 1);
        }
    }
    while(left_index <= mid) {
        merged_arr.push_back(arr[left_index]);
        ++left_index;
    }

    while(right_index <= right) {
        merged_arr.push_back(arr[right_index]);
        ++right_index;
    }

//    const int expected_size = (right - left + 1);
//    debug(expected_size);
//    debug(merged_arr.size());
//    assert(expected_size == (int) merged_arr.size());

    for(int i = 0; i < (int) merged_arr.size(); ++i) {
        arr[left + i] = merged_arr[i];
    }
    
    return inv_cont;
}

inline ll merge_sort(vector<int>& arr, int left, int right) {
	ll cont_inv = 0;
	if(left < right) {
		int mid = (left + right) / 2;

		cont_inv += merge_sort(arr, left, mid);
		cont_inv += merge_sort(arr, mid + 1, right);
		cont_inv += merge(arr, left, right);
	}
	return cont_inv;
}

inline ll solve(vector<int> arr) {

    int n = (int) arr.size();

	ll res = merge_sort(arr, 0, n - 1);
	return res;
}

int main() {

	int tests;
	scanf("%d", &tests);

	for(int t = 1; t <= tests; ++t) {
		int n;
		scanf("%d", &n);

		vector<int> arr(n);
		for(int i = 0; i < n; ++i)
			scanf("%d", &arr[i]);

		ll ans = solve(arr);
		printf("%lld\n", ans);
	}

    return 0;
}
