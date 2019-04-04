#include <optional>

template<typename T>
struct Circle {
    static std::optional<Circle>
    from_2_points_and_r(const Point<T>& P, const Point<T>& Q, T r)
    {
        double d2 = (P.x - Q.x) * (P.x - Q.x) + (P.y - Q.y) * (P.y - Q.y);
        double det = r * r / d2 - 0.25;

        if (det < 0.0)
            return { };

        double h = sqrt(det);

        auto x = (P.x + Q.x) * 0.5 + (P.y - Q.y) * h;
        auto y = (P.y + Q.y) * 0.5 + (Q.x - P.x) * h;

        return Circle { Point(x, y), r };
    }
}

