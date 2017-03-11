// Reference: https://e-maxx-eng.appspot.com/num_methods/ternary_search.html
#include <bits/stdc++.h>

#define fori(i, ini, lim) for(int i = int(ini); i < int(lim); i++)
#define ford(i, ini, lim) for(int i = int(ini); i >= int(lim); i--)

#define debug(x) cout << "> " << #x << " = " << x << endl;
#define debug_at(arr, at) cout << "> " << #arr << "[" << at << "] = " << arr[at] << endl;
#define debug_pair(p) cout << "> " << #p << " = (" << p.first << ", " << p.second << ")" << endl;

using namespace std;

/**
  * Ternary search: the problem of finding a minimum or maximum local of a unimodal* function f(x) : x e [A, B];
    A function f is unimodal if for some x, f(x) is monotonic as x increases and monotonic as x decreases
    In other words: f(x) stricly increases, reaches a maximum, and start strictly decreasing
                or  f(x) stricly decreases, reaches a minimum, and start strictly increasing


    Let's find a maximum local of f(x) for x in interval [A, B], f is unimodal
    The ideia is that if you take two different values: m1 < m2;
    We can reduce the search space of x by noting that:
    if(f(m1) < f(m2))
        then the maximum local is definetely not before m1, so we can reduce the search space
        from [A, B] to [m1, B]
    else if(f(m1) == f(m2))
        we assumed that f(x) is strictly icreasing, and then starts strictly decreasing
        so f(m1) == f(m2) for m1 != m2 is only valid if f(m1) = f(m2) = a local maximum
        i.e: f(m1) is the answer
    else if(f(m1) > f(m2))
        this is symmetrical to the first case.
        the space is reduced from [A, B] to [A, m2]
*/

inline double f(const double x) {
    // TODO: replace this function with your problem's function
    return 0.0;
}

double ts() {
    double l = 1.0;
    double r = 1e9;
    // if f(x) accepts only integer arguments, then the search space [A, B] can't be reduced forever:
    // it needs to stop when (r - l) < 3

    // if f(x) accepts real arguments, the search space can be reduced indeterminately,
    // so the number of iterations depend on the precision you need, 300 iterations is more then enough for practical problems
    fori(i, 0, 300) {
        double m1 = l + (r - l) / 3.0;
        double m2 = r - (r - l) / 3.0;
        if(f(m1) < f(m2)) {
            r = m2;
        }
        else {
            l = m1;
        }
    }
    return f(l);
}

int main() {
    ios_base::sync_with_stdio(false);

    return 0;
}
