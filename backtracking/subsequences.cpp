#include <bits/stdc++.h>

#define fori(i, ini, lim) for(int i = int(ini); i < int(lim); i++)
#define ford(i, ini, lim) for(int i = int(ini); i >= int(lim); i--)

#define debug(x) cout << "> " << #x << " = " << x << endl;
#define debug_at(arr, at) cout << "> " << #arr << "[" << at << "] = " << arr[at] << endl;
#define debug_pair(p) cout << "> " << #p << " = (" << p.first << ", " << p.second << ")" << endl;

using namespace std;

const int N = 31;

inline bool on(int mask, int i) {
    return mask & (1 << i);
}

void print(int mask) {
    putchar('{');
    vector<int> res;
    fori(i, 0, N) {
        if(on(mask, i)) {
            res.push_back(i);
        }
    }
    fori(i, 0, res.size()) {
        if(i) {
            printf(", ");
        }
        printf("%d", res[i]);
    }
    puts("}");
}

void gen(int n) {
    fori(i, 0, 1 << n) {
        print(i);
    }
}

int main() {
    fori(i, 1, 5) {
        debug(i);
        gen(i);
        puts("\n");
    }

    return 0;
}
