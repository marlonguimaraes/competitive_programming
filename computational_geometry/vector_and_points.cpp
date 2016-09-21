#include <bits/stdc++.h>

#define debug(x) cout << "> " << #x << " = " << x << endl;
#define debug_at(arr, at) cout << "> " << #arr << "[" << at << "] = " << arr[at] << endl;
#define debug_pair(p) cout << "> " << #p << " = (" << p.first << ", " << p.second << ")" << endl;

using namespace std;

const double EPS = 1e-9;
const double PI = acos(-1.0);

inline bool equals(double a, double b) {
    return (a - b) < EPS;
}

inline bool less_than(double a, double b) {
    return (a - b) < -EPS;
}

struct Vector {
    double x, y;

    Vector(double xx = 0.0, double yy = 0.0) : x(xx), y(yy) {}

    Vector operator+(const Vector &vec) {
        Vector res(x + vec.x, y + vec.y);
        return res;
    }

    Vector operator*(double scalar) {
        Vector res(x * scalar, y * scalar);
        return res;
    }

    inline double angle() {
        double res = atan(y / x);
        if(less_than(x, 0.0)) { // You need this because you can't now if (x, y) is on the second or third quadrant
            res += PI;
        }
        return res;
    }

    inline void print() {
        pair<double, double> xy(x, y);
        debug_pair(xy);
    }
};

inline Vector translate(const Vector &vec, double dx, double dy) {
    Vector res(vec.x + dx, vec.y + dy);
    return res;
}

// angle in radians
inline Vector rotate(const Vector &vec, double angle) {
    double x = cos(angle) * vec.x - sin(angle) * vec.y;
    double y = sin(angle) * vec.x + cos(angle) * vec.y;
    Vector res(x, y);
    return res;
}

inline Vector rotate(const Vector &vec, double angle, const Vector &v) {
    Vector u = translate(vec, -v.x, -v.y);
    u = rotate(u, angle);
    u = translate(u, v.x, v.y);
    return u;
}

inline double degToRad(double deg) {
    return (PI * deg) / 180.0;
}

int main() {
    ios_base::sync_with_stdio(false);

    Vector v1(100.0, 0.0);
    v1.print();

    Vector v2(100.0, 0.0);
    v2 = v1 + v2;
    v2 = rotate(v2, degToRad(120.0), v1);
    v2.print();

    Vector v3(100.0, 0.0);
    v3 = rotate(v3, v2.angle());
    v3.print();
    v3 = rotate(v3, degToRad(120.0));
 	return 0;
}
