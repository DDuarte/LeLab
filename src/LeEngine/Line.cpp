#include "Line.h"


Vector<3> Line3::ClosestPoint(const Line3& lineA, const Line3& lineB, float& distance)
{
    // Based on g3dlite code
    const Vector<3>& P1 = lineA.GetPoint();
    const Vector<3>& U1 = lineA.GetDirection();

    Vector<3> P2 = lineB.GetPoint();
    Vector<3> U2 = lineB.GetDirection();

    const Vector<3>& P21 = P2 - P1;
    const Vector<3>& M = U2.CrossProduct(U1);
    float m2 = M.Magnitude();

    Vector<3> R = P21.CrossProduct(M) / m2;

    float t1 = R.DotProduct(U2);

    distance = Math<float>::Abs(P21.DotProduct(M)) / Math<float>::Sqrt(m2);

    return P1 + U1 * t1;
}

bool Line3::Intersection(const Plane& plane, Vector<3>& resultPoint) const
{
    Vector<3> p0 = plane.GetPoint();
    Vector<3> l0 = _point;
    Vector<3> n = plane.GetNormal();
    Vector<3> l = _direction;

    float num = (p0 - l0).DotProduct(n);
    float dem = l.DotProduct(n);

    if (!IsZero(dem))
    {
        // intersection in a point
        float d = num/dem;
        resultPoint = GetPoint(d);
        return true;
    }
    else if (!IsInfinite(num) && !IsZero(num))
    {
        // no intersection
        return false;
    }
    else
    {
        // intersection is a line...
        resultPoint = (std::numeric_limits<float>::infinity(), 
            std::numeric_limits<float>::infinity(),
            std::numeric_limits<float>::infinity());
        return true;
    }
}
