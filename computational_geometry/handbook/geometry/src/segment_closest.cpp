template<typename T>
struct Segment {
    Point<T> A, B;

    bool contains(const Point<T>& P) const
    {
        if (equals(A.x, B.x))
            return min(A.y, B.y) <= P.y and P.y <= max(A.y, B.y);
        else
            return min(A.x, B.x) <= P.x and P.x <= max(A.x, B.x);
    }

    Point<T> closest(const Point<T>& P)
    {
        Line<T> r(A, B);
        auto Q = r.closest(P);

        if (this->contains(Q))
            return Q;

        auto distA = P.distanceTo(A);
        auto distB = P.distanceTo(B);

        if (distA <= distB)
            return A;
        else
            return B;
    }
}

