#ifndef VECTOR2_H
#define VECTOR2_H

#include <cmath>
#include "MathDefines.h"

template<typename T>
class Vector2
{
private:
    T X;
    T Y;

public:
    Vector2() : X(0), Y(0) {}
    Vector2(T x, T y) : X(x), Y(y) {}
    Vector2(const Vector2<T>& other) : X(other.X), Y(other.Y) {}
    Vector2(const T arr[2]) : X(arr[0]), Y(arr[1]) {}
    Vector2(T val) : X(val), Y(val) {}

    T GetX() const { return X; }
    T GetY() const { return Y; }

    void SetX(T x) { X = x; }
    void SetY(T y) { Y = y; }
    void Set(T x, T y, T z) { X = x; Y = y; }

    bool operator ==(const Vector2<T>& other) const { return (X == other.X) && (Y == other.Y); }
    bool operator !=(const Vector2<T>& other) const {return !operator ==(other); }

    Vector2<T> operator +(const Vector2<T>& other) const { return Vector2<T>(X + other.X, Y + other.Y); }
    Vector2<T> operator -(const Vector2<T>& other) const { return Vector2<T>(X - other.X, Y - other.Y); }

    Vector2<T> operator *(const T scalar) const { return Vector2<T>(X * scalar, Y * scalar); }
    Vector2<T> operator /(const T scalar) const { assert(!IsZero(scalar)); return Vector2<T>(X / scalar, Y / scalar); }

    Vector2<T> operator +() const { return *this; }
    Vector2<T> operator -() const { return Vector2<T>(-X, -Y); }

    Vector2<T>& operator =(const Vector2<T>& other)
    {
        X = other.X;
        Y = other.Y;
        return *this;
    }

    Vector2<T>& operator =(const T& val)
    {
        X = val;
        Y = val;
        return *this;
    }

    Vector2<T>& operator =(const T arr[2])
    {
        X = arr[0];
        Y = arr[1];
        return *this;
    }

    Vector2<T>& operator +=(const Vector2<T>& other)
    {
        X += other.X;
        Y += other.Y;
        return *this;
    }

    Vector2<T>& operator -=(const Vector2<T>& other)
    {
        X -= other.X;
        Y -= other.Y;
        return *this;
    }

    Vector2<T>& operator +=(const T& scalar)
    {
        X += scalar;
        Y += scalar;
        return *this;
    }

    Vector2<T>& operator -=(const T& scalar)
    {
        X -= scalar;
        Y -= scalar;
        return *this;
    }

    Vector2<T>& operator *=(const T& scalar)
    {
        X *= scalar;
        Y *= scalar;
        return *this;
    }

    Vector2<T>& operator /=(const T& scalar)
    {
        assert(!IsZero(scalar));
        X /= scalar;
        Y /= scalar;
        return *this;
    }

    //! The magnitude or length of this vector
    T Magnitude() const { return sqrt(X*X + Y*Y); }
    //! The squared magnitude or length of this vector (more efficient)
    T MagnitudeSqr() const { return X*X + Y*Y; }

    //! The distance of this vector to other vector
    T Distance(const Vector2<T>& other) const { return (*this - other).Magnitude(); }
    //! The squared distance of this vector to other vector (more efficient)
    T DistanceSqr(const Vector2<T>& other) const { return (*this - other).MagnitudeSqr(); }

    //! Normalizes this vector
    void Normalize()
    {
        T length = Magnitude();
        assert(length != 0);
        X /= length;
        Y /= length;

        assert(IsZero(MagnitudeSqr() - static_cast<T>(1.0)));
    }

    //! Returns the dot product (a scalar) between this vector and some other
    T DotProduct(const Vector2<T>& other) const { return X*other.X + Y*other.Y; }

    //! Returns the angle in radians of this vector and other
    float AngleBetween(const Vector2<T>& other) const
    {
        T dotP = DotProduct(other);
        T lengthP = Magnitude() * other.Magnitude();

        assert(!IsZero(lengthP));

        return acos((float)dotP / lengthP);
    }

    //! Returns a vector that is perpendicular to this vector
    Vector2<T> Perpendicular() { return Vector2<T>(-Y, X); }
};

#endif // VECTOR2_H
