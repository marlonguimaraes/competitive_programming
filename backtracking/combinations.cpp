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
    putchar('(');
    fori(i, 1, n + 1) {
        if(i > 1) {
            printf(", ");
        }
        printf("%d", arr[i]);
    }
    puts(")");
}

void gen(int i, int n, int k) {
    if(i > k) {
        print(k);
        return;
    }
    fori(j, arr[i - 1] + 1, n + 1) {
        arr[i] = j;
        gen(i + 1, n, k);
    }
}

int main() {
    int n = 5;
    arr[0] = 0;

    fori(i, 1, n + 1) {
        printf("(%d, %d) =\n", n, i);
        gen(1, n, i);
        puts("\n");
    }

    return 0;
}
