template<typename T>
struct Circle
{
    double perimeter() const
    {
        return 2.0 * PI * r;
    }

    double area() const
    {
        return PI * r * r;
    }

    double arc(double theta) const
    {
        return theta * r;
    }

    double chord(double theta) const
    {
        return 2 * r * sin(theta/2);
    }

	double sector(double theta) const
    {
        return (theta * r * r)/2;
    }

    double segment(double a) const
    {
        auto c = chord(a);
        auto s = (r + r + c)/2.0;
        auto T = sqrt(s*(s - r)*(s - r)*(s - c));

        return sector(a) - T;
    }

};
