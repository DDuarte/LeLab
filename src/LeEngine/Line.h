#ifndef LINE_H
#define LINE_H

#include "Vector.h"
#include "Plane.h"

class Line3
{
protected: // _point + t * _direction
    Vector<3> _point;
    Vector<3> _direction;

public:
    //! Line with a point at origin, direction (i,j,k,..)
    Line3() : _point(0.0f), _direction(0.0f) {}
    //! Line defined by an origin point and direction
    Line3(const Vector<3>& point, const Vector<3>& direction) : _point(point), _direction(direction) {}
    //! Line copy constructor
    Line3(const Line3& other) : _point(other._point), _direction(other._direction) {}
    //! Line from two points
    Line3(const Vector<3>& pointA, Vector<3>& pointB) : _point(pointA), _direction(pointB - pointA) {}

    Line3& operator =(const Line3& other) { _point = other._point; _direction = other._direction; return *this; }

    Vector<3> GetPoint() const { return _point; } //!> Origin (const)
    Vector<3>& GetPoint() { return _point; } //!> Origin
    Vector<3> GetDirection() const { return _direction; } //!> Direction (const)
    Vector<3>& GetDirection() { return _direction; } //!> Direction

    void SetPoint(const Vector<3>& point) { _point = point; } //!> Changes origin
    void SetDirection(const Vector<3>& direction) { _direction = direction; }  //!> Changes direction

    //! Gets the position of a point t units along the line
    Vector<3> GetPoint(float t) const { return _point + _direction * t; }
    //! Gets the position of a point t units along the line
    Vector<3> operator *(float t) const { return GetPoint(t); }

    //! Distance of this line to a point
    float DistanceTo(const Vector<3>& point) const
    {
        // |_direction X (point - _point)|
        return _direction.CrossProduct(point - _point).Magnitude();
    }

    //! Closest point on the line to a point
    Vector<3> ClosestPoint(const Vector<3>& point) const
    {
        float t = _direction.DotProduct(point - _point);
        return _point + _direction * t;
    }

    //! Closest point and distance of two lines
    static Vector<3> ClosestPoint(const Line3& lineA, const Line3& lineB, float& distance);

    //! Intersection of this line with a plane (a point)
    bool Intersection(const Plane& plane, Vector<3>& resultPoint) const;

};

#endif // LINE_H
