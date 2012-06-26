#ifndef VECTOR3_H
#define VECTOR3_H

#include <cmath>
#include "MathDefines.h"

template<typename T>
class Vector3
{
private:
    T X;
    T Y;
    T Z;

public:
    Vector3() : X(0), Y(0), Z(0) {}
    Vector3(T x, T y, T z) : X(x), Y(y), Z(z) {}
    Vector3(const Vector3<T>& other) : X(other.X), Y(other.Y), Z.(other.Z) {}
    Vector3(const T arr[3]) : X(arr[0]), Y(arr[1]), Z(arr[2]) {}
    Vector3(T val) : X(val), Y(val), Z(val) {}

    T GetX() const { return X; }
    T GetY() const { return Y; }
    T GetZ() const { return Z; }

    void SetX(T x) { X = x; }
    void SetY(T y) { Y = y; }
    void SetZ(T z) { Z = z; }
    void Set(T x, T y, T z) { X = x; Y = y; Z = z; }

    bool operator ==(const Vector3<T>& other) const { return (X == other.X) && (Y == other.Y) && (Z == other.Z); }
    bool operator !=(const Vector3<T>& other) const {return !operator ==(other); }

    Vector3<T> operator +(const Vector3<T>& other) const { return Vector3<T>(X + other.X, Y + other.Y, Z + other.Z); }
    Vector3<T> operator -(const Vector3<T>& other) const { return Vector3<T>(X - other.X, Y - other.Y, Z - other.Z); }

    Vector3<T> operator *(const T scalar) const { return Vector3<T>(X * scalar, Y * scalar, Z * scalar); }
    Vector3<T> operator /(const T scalar) const { assert(!IsZero(scalar)); return Vector3<T>(X / scalar, Y / scalar, Z / scalar); }

    Vector3<T> operator +() const { return *this; }
    Vector3<T> operator -() const { return Vector3<T>(-X, -Y, -Z); }

    Vector3<T>& operator =(const Vector3<T>& other)
    {
        X = other.X;
        Y = other.Y;
        Z = other.Z;
        return *this;
    }

    Vector3<T>& operator =(const T& val)
    {
        X = val;
        Y = val;
        Z = val;
        return *this;
    }

    Vector3<T>& operator =(const T arr[3])
    {
        X = arr[0];
        Y = arr[1];
        Z = arr[2];
        return *this;
    }
    
    Vector3<T>& operator +=(const Vector3<T>& other)
    {
        X += other.X;
        Y += other.Y;
        Z += other.Z;
        return *this;
    }

    Vector3<T>& operator -=(const Vector3<T>& other)
    {
        X -= other.X;
        Y -= other.Y;
        Z -= other.Z;
        return *this;
    }

    Vector3<T>& operator +=(const T& scalar)
    {
        X += scalar;
        Y += scalar;
        Z += scalar;
        return *this;
    }

    Vector3<T>& operator -=(const T& scalar)
    {
        X -= scalar;
        Y -= scalar;
        Z -= scalar;
        return *this;
    }

    Vector3<T>& operator *=(const T& scalar)
    {
        X *= scalar;
        Y *= scalar;
        Z *= scalar;
        return *this;
    }

    Vector3<T>& operator /=(const T& scalar)
    {
        assert(!IsZero(scalar));
        X /= scalar;
        Y /= scalar;
        Z /= scalar;
        return *this;
    }

    //! The magnitude or length of this vector
    T Magnitude() const { return sqrt(X*X + Y*Y + Z*Z); }
    //! The squared magnitude or length of this vector (more efficient)
    T MagnitudeSqr() const { return X*X + Y*Y + Z*Z; }

    //! The distance of this vector to other vector
    T Distance(const Vector3<T>& other) const { return (*this - other).Magnitude(); }
    //! The squared distance of this vector to other vector (more efficient)
    T DistanceSqr(const Vector3<T>& other) const { return (*this - other).MagnitudeSqr(); }

	//! Normalizes this vector
    void Normalize()
    {
        if (!IsZero(MagnitudeSqr() - static_cast<T>(1))
        {
            T length = Magnitude();
            assert (!IsZero(length));
            X /= length;
            Y /= length;
            Z /= length;
            assert(IsZero(MagnitudeSqr() - static_cast<T>(1.0)));
        }
    }

	//! Returns the dot product (a scalar) between this vector and some other
    T DotProduct(const Vector3<T>& other) const { return X*other.X + Y*other.Y + Z*other.Z; }

	//! Returns the cross product (a vector) between this vector and some other
    Vector3<T> CrossProduct(const Vector3<T>& other) const
    {
        return Vector3<T>(Y * other.Z - Z * other.Y,
                          Z * other.X - X * other.Z,
                          X * other.Y - Y * other.X);
    }

	//! Returns the angle in radians of this vector and other
	float AngleBetween(const Vector3<T>& other) const
	{
		T dotP = DotProduct(other);
		T lengthP = Magnitude() * other.Magnitude();

		assert(!IsZero(lengthP));

		return acos((float)dotP / lengthP);
	}

	//! Returns a vector that is perpendicular to this vector
	//! There are many solutions, this will only get one of those
	Vector3<T> Perpendicular()
	{
		Vector3<t> try1 = CrossProduct(Vector3(1, 0, 0));

		if (IsZero(try1.MagnitudeSqr()))
			return CrossProduct(Vector3(0, 1, 0));

		return try1;
	}
};

#endif // VECTOR3_H
