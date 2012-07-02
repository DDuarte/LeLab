#include "Plane.h"
#include "Line.h"

Plane::Plane(const Vector<3>& point1, const Vector<3>& point2, const Vector<3>& point3)
{
    const Vector<3> AB = point2 - point1;
    const Vector<3> AC = point3 - point1;

    _normal = AB.CrossProduct(AC);//;.NormalizeCopy();
    _distance = _normal.DotProduct(point1);
}

Plane::Side Plane::WhichSide(const Vector<3>& point) const
{
    float sol = _normal.DotProduct(point) - _distance;
    if (sol > 0)
        return SIDE_POSITIVE;
    else if (sol < 0)
        return SIDE_NEGATIVE;
    else
        return SIDE_NONE;
}

bool Plane::Intersection(const Line3& line, Vector<3>& resultPoint) const
{
    return line.Intersection(*this, resultPoint);
}
