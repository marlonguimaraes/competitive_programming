typedef pair<long long, long long> ii;

// D = 0: R lies on line PQ
// D > 0: R is to the left of line PQ
// D < 0: R is to the right of line PQ
long long D(const ii &a, const ii &b, const ii &c) {
    return (a.first * b.second + a.second * c.first + b.first * c.second)
	     - (c.first * b.second + c.second * a.first + b.first * a.second);
}
