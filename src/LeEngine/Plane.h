#ifndef PLANE_H
#define PLANE_H

#include "Vector.h"

class Line3;

class Plane
{
protected: // _normal . X = _constant
    Vector<3> _normal;
    float _distance;

public:
    Plane(const Vector<3>& normal, float dist) : _normal(normal.NormalizeCopy()), _distance(dist) {}
    Plane(const Vector<3>& normal, const Vector<3>& point) : _normal(normal.NormalizeCopy()) { _distance = normal.DotProduct(point); }
    Plane(float a, float b, float c, float d) : _normal(a, b, c), _distance(d) {}
    Plane(const Vector<3>& point1, const Vector<3>& point2, const Vector<3>& point3);

    Vector<3>& GetNormal() { return _normal; }
    Vector<3> GetNormal() const { return _normal; }
    float& GetDistance() { return _distance; }
    float GetDistance() const { return _distance; }

    void SetNormal(const Vector<3>& normal) { _normal = normal; }
    void SetDistance(float dist) { _distance = dist; }
    void Set(const Vector<3>& normal, float dist) {_normal = normal; _distance = dist; }

    //! Returns a point belonging to the plane
    Vector<3> GetPoint() const { return Vector<3>(IsZero(_distance) ? 0.0f : (_distance / _normal.X()), 0.0f, 0.0f); }

    float DistanceTo(const Vector<3>& point) const
    {
        return _normal.DotProduct(point) - _distance;
    }

    enum Side
    {
        SIDE_NONE,
        SIDE_POSITIVE,
        SIDE_NEGATIVE,
    };

    Side WhichSide(const Vector<3>& point) const;

    bool Intersection(const Line3& line, Vector<3>& resultPoint) const;
};

#endif // PLANE_H
