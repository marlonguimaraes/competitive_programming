const double EPS { 1e-9 };
bool equals(double a, double b)
{
    return fabs(a - b) < EPS;
}
