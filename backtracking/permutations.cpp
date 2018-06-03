#include <bits/stdc++.h>

#define fori(i, ini, lim) for(int i = int(ini); i < int(lim); i++)
#define ford(i, ini, lim) for(int i = int(ini); i >= int(lim); i--)

#define debug(x) cout << "> " << #x << " = " << x << endl;
#define debug_at(arr, at) cout << "> " << #arr << "[" << at << "] = " << arr[at] << endl;
#define debug_pair(p) cout << "> " << #p << " = (" << p.first << ", " << p.second << ")" << endl;

using namespace std;

const int N = 123;

int arr[N];

void print(int n) {
    fori(i, 0, n) {
        printf("%2d", arr[i]);
    }
    puts("");
}

bool used[N];
void gen(int i, int n) {
    if(i == n) {
        print(n);
        return;
    }
    fori(j, 1, n + 1) {
        if(!used[j]) {
            arr[i] = j;
            used[j] = true;

            gen(i + 1, n);
            used[j] = false;
        }
    }
}

int main() {
    fori(i, 1, 5) {
        debug(i);
        gen(0, i);
        puts("\n");
    }

    return 0;
}
