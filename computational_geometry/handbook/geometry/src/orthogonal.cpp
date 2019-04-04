template<typename T>
struct Line
{
    bool orthogonal(const Line& r) const
    {
        return equals(a * r.a + b * r.b, 0);
    }
};
