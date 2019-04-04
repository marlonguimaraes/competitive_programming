template<typename T>
double angle(const Point<T>& P, const Point<T>& Q, 
             const Point<T>& R, const Point<T>& S)
{
    auto ux = P.x - Q.x;
    auto uy = P.y - Q.y;

    auto vx = R.x - S.x;
    auto vy = R.y - S.y;

    auto num = ux * vx + uy * vy;
    auto den = hypot(ux, uy) * hypot(vx, vy);
    return acos(num / den);
}

