#include <bits/stdc++.h>

#define debug(x) cout << "> " << #x << " = " << x << endl;
#define debug_at(arr, at) cout << "> " << #arr << "[" << at << "] = " << arr[at] << endl;
#define debug_pair(p) cout << "> " << #p << " = (" << p.first << ", " << p.second << ")" << endl;

using namespace std;

const double EPS = 1e-9;

inline bool equals(const double& a, const double& b) {
    return abs(a - b) < EPS;
}

struct Point {
    double x, y;

    Point(double xx = 0.0, double yy = 0.0) : x(xx), y(yy) {}

    inline double distance(const Point& P) const {
        return hypot(x - P.x, y - P.y);
    }
};

struct Circle {
    Point center;
    double radius;

    Circle(const Point& cc = Point(), const double& rr = 1.0) : center(cc), radius(rr) {}

    Circle circle_from_3_points(const Point& P, const Point& Q, const Point& R) {
        auto a = 2.0 * (Q.x - P.x);
		auto b = 2.0 * (Q.y - P.y);
		auto c = 2.0 * (R.x - P.x);
		auto d = 2.0 * (R.y - P.y);

		auto det = a * d - b * c;

        // Points are colinear
		if(equals(det, 0.0))
			return Circle();

		auto k1 = (Q.x * Q.x + Q.y * Q.y) - (P.x * P.x + P.y * P.y);
		auto k2 = (R.x * R.x + R.y * R.y) - (P.x * P.x + P.y * P.y);

		auto cx = (k1 * d - k2 * b) / det;
		auto cy = (a * k2 - c * k1) / det;

		Point C(cx, cy);
		auto r = C.distance(P);

		return Circle(C, r);
    }
};

Point A, B, C;
inline void solve(double& x0, double& y0, double& r) {
    Circle circle;
    Circle res = circle.circle_from_3_points(A, B, C);

    x0 = res.center.x;
    y0 = res.center.y;
    r = res.radius;
}

inline void print(double x0, double y0, double r) {
    printf("Center = (%.3lf, %.3lf)\n", x0, y0);
    printf("Radius = %.3lf\n", r);
}

int main() {


// Given three nom colinear points, find it's center and radius
    while(scanf("%lf %lf", &A.x, &A.y) == 2) {
        scanf("%lf %lf", &B.x, &B.y);
        scanf("%lf %lf", &C.x, &C.y);

        double x0, y0, r;
        solve(x0, y0, r);
        print(x0, y0, r);
    }

	return 0;
}
