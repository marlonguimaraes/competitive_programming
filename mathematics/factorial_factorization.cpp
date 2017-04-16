#include <bits/stdc++.h>

#define fori(i, ini, lim) for(int i = int(ini); i < int(lim); i++)
#define ford(i, ini, lim) for(int i = int(ini); i >= int(lim); i--)

#define debug(x) cout << "> " << #x << " = " << x << endl;
#define debug_at(arr, at) cout << "> " << #arr << "[" << at << "] = " << arr[at] << endl;
#define debug_pair(p) cout << "> " << #p << " = (" << p.first << ", " << p.second << ")" << endl;

using namespace std;

typedef long long ll;
typedef map<int, int> mii;

const int N = 100;

vector<int> primes;
int prime[N];

void sieve() {
    memset(prime, -1, sizeof prime);
    fori(i, 2, N) {
        if(prime[i]) {
            primes.push_back(i);
            for(int j = i * i; j < N; j += i) {
                prime[j] = 0;
            }
        }
    }
}

inline mii factor(int n) {
    mii res;
    for(int p : primes) {
        int pp = p;
        while((n / pp) > 0) {
            res[p] += (n / pp);
            pp *= p;
        }
    }
    return res;
}

inline mii sum(mii a, mii b) {
    mii res;
    for(int p : primes) {
        int val = a[p] + b[p];
        if(val) {
            res[p] = val;
        }
    }
    return res;
}

inline mii divide(mii num, mii den) {
    mii res;
    for(int p : primes) {
        int val = num[p] - den[p];
        if(val) {
            res[p] = val;
        }
    }
    return res;
}

inline void print(mii a) {
    for(auto p : a) {
        printf("[%d] = %d\n", p.first, p.second);
    }
}

int main() {

    sieve();

    mii num = factor(97);
    mii den = sum(factor(40), factor(57));
    mii res = divide(num, den);

    printf("(97!) / (40! * 57!) =\n");
    print(res);
	return 0;
}
