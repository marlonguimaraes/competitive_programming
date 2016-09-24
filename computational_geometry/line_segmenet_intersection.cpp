// Based on https://github.com/edsomjr/TEP/blob/master/Geometria%20Computacional/Retas.md
#include <bits/stdc++.h>

#define debug(x) cout << "> " << #x << " = " << x << endl;
#define debug_at(arr, at) cout << "> " << #arr << "[" << at << "] = " << arr[at] << endl;
#define debug_pair(p) cout << "> " << #p << " = (" << p.first << ", " << p.second << ")" << endl;

const int INF = -1;

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

    Point(double xv = 0.0, double yv = 0.0) : x(xv), y(yv) {}
};


class Segment {
public:
    Point A, B;
    double a, b, c;

    Segment(const Point& p = Point(), const Point& q = Point()) : A(p), B(q) {
        a = p.y - q.y;
        b = q.x - p.x;
        c = p.x * q.y - p.y * q.x;

        auto k = a ? a : b;

        a /= k;
        b /= k;
        c /= k;
    }

    bool operator==(const Segment& r) const {
        return equals(a, r.a) && equals(b, r.b) && equals(c, r.c);
    }

    bool parallel(const Segment& r) const
    {
        return equals(a, r.a) && equals(b, r.b) && !equals(c, r.c);
    }

    double length() const {
        return hypot(A.x - B.x, A.y - B.y);
    }

	bool contains(const Point& P) const {
		if(equals(A.x, B.x))
			return min(A.y, B.y) <= P.y and P.y <= max(A.y, B.y);
		else
			return min(A.x, B.x) <= P.x and P.x <= max(A.x, B.x);
	}

    // Segments may be on the same line, but have no intersection
    bool contains(const Segment& seg) const {
        return contains(seg.A) or contains(seg.B);
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

pair<int, Point> intersections(const Segment& r, const Segment& s) {
    auto det = r.a * s.b - r.b * s.a;

    if (equals(det, 0)) {
        // Coincidentes ou paralelas
        int qtd = (r == s) ? INF : 0;
        return pair<int, Point>(qtd, Point());
    } else {
        // Concorrentes
        auto x = (-r.c * s.b + s.c * r.b) / det;
        auto y = (-s.c * r.a + r.c * s.a) / det;
        return pair<int, Point>(1, Point(x, y));
    }
}

int main() {

	return 0;
}
