#include <bits/stdc++.h>

#define debug(x) cout << "> " << #x << " = " << x << endl;
#define debugat(arr, at) cout << "> " << #arr << "[" << at << "] = " << arr[at] << endl;
#define debugpair(p) cout << "> " << #p << " = " << "(" << p.first << ", " << p.second << ")" << endl;

using namespace std;

int main() {

    const unsigned val = 85;
    const unsigned size = log2(val) + 1;

    bitset<size> b(val);                // will fill the last log2(val) bits with values of binary representation of val;
                                        // there will be leading zeros if there are left spaces;
    cout << b.to_string() << "\n";
    return 0;
}
