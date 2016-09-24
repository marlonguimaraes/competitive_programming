// Based on https://github.com/edsomjr/TEP/blob/master/Geometria%20Computacional/Retas.md
#include <bits/stdc++.h>

#define debug(x) cout << "> " << #x << " = " << x << endl;
#define debug_at(arr, at) cout << "> " << #arr << "[" << at << "] = " << arr[at] << endl;
#define debug_pair(p) cout << "> " << #p << " = (" << p.first << ", " << p.second << ")" << endl;

using namespace std;

typedef pair<double, double> dd;

const double EPS = 1e-9;

bool equals(double a, double b) {
        return fabs(a - b) < EPS;
}

class Point {
public:
    double x;
    double y;

    Point(double xv = 0, double yv = 0) : x(xv), y(yv) {}
};

// D = 0: R pertence a reta PQ
// D > 0: R à esquerda da reta PQ
// D < 0: R à direita da reta PQ
double D(const Point& P, const Point& Q, const Point& R) {
    return (P.x * Q.y + P.y * R.x + Q.x * R.y) - (R.x * Q.y + R.y * P.x + Q.x * P.y);
}

class Segment {
public:
    Point A, B;

    Segment(const Point& Av, const Point& Bv) : A(Av), B(Bv) {}

    double length() const {
        return hypot(A.x - B.x, A.y - B.y);
    }

	bool contains(const Point& P) const {
		if(equals(A.x, B.x))
			return min(A.y, B.y) <= P.y and P.y <= max(A.y, B.y);
		else
			return min(A.x, B.x) <= P.x and P.x <= max(A.x, B.x);
	}

	bool intersect(const Segment& s) const {
		auto d1 = D(A, B, s.A);
		auto d2 = D(A, B, s.B);

		if ((equals(d1, 0) && contains(s.A)) || (equals(d2, 0) && contains(s.B)))
			return true;

		auto d3 = D(s.A, s.B, A);
		auto d4 = D(s.A, s.B, B);

		if ((equals(d3, 0) && s.contains(A)) || (equals(d4, 0) && s.contains(B)))
			return true;

		return (d1 * d2 < 0) && (d3 * d4 < 0);
	}

    inline void print() {
        cout << "\n";
        dd AA(A.x, A.y);
        dd BB(B.x, B.y);
        cout << "Segment:\n";
        debug_pair(AA);
        debug_pair(BB);
        cout << "\n";
    }
};

int main() {

    vector<Segment> segs;

    Point P1(1, 3), Q1(4, 0),
          P2(1, 1), Q2(3, 3);
    Segment r1(P1, Q1),
            s1(P2, Q2);
    segs.push_back(r1);
    segs.push_back(s1);

    Point P3(2, 2), Q3(4, 0),
          P4(2, -2), Q4(2, -4);
    Segment r2(P3, Q3),
            s2(P4, Q4);
    segs.push_back(r2);
    segs.push_back(s2);

    Point P5 = P2, Q5 = Q2,
          P6(4, 4), Q6(5, 4);
    Segment r3(P5, Q5),
            s3(P6, Q6);
    segs.push_back(r3);
    segs.push_back(s3);



    for(int i = 0; i < (int) segs.size(); i += 2) {
        Segment r = segs[i];
        Segment s = segs[i + 1];
        r.print();
        s.print();
        cout << r.intersect(s) << "\n";
    }

	return 0;
}
