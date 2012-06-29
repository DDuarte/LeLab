#ifndef VECTOR_H
#define VECTOR_H

#include <cmath>
#include "MathDefines.h"

template<int Size, typename T = float>
class Vector
{
private:
    T V[Size];

public:
    Vector() { memset(V, 0, Size * sizeof(T)); }
    Vector(T x, T y)
    {
        assert(Size == 2);
        V[0] = x;
        V[1] = y;
    }
    Vector(T x, T y, T z)
    {
        assert(Size == 3);
        V[0] = x;
        V[1] = y;
        V[2] = z;
    }
    Vector(T x, T y, T z, T w)
    {
        assert(Size == 4);
        V[0] = x;
        V[1] = y;
        V[2] = z;
        V[3] = w;
    }
    Vector(const Vector<Size, T>& other) { memcpy(V, other.V, Size * sizeof(T)); }
    Vector(const T arr[Size]) { memcpy(V, arr, Size * sizeof(T)); }
    Vector(T val) { for (int i = 0; i < Size; ++i) V[i] = val; }

    T X() const { assert(Size >= 1); return V[0]; }
    T Y() const { assert(Size >= 2); return V[1]; }
    T Z() const { assert(Size >= 3); return V[2]; }
    T W() const { assert(Size >= 4); return V[3]; }

    T operator [](int index) const { assert(index < Size); return V[index]; }
    T& operator [](int index) { assert(index < Size); return V[index]; }

    void SetX(T x) { assert(Size >= 1); V[0] = x; }
    void SetY(T y) { assert(Size >= 2); V[1] = y; }
    void SetZ(T z) { assert(Size >= 3); V[2] = z; }
    void SetW(T w) { assert(Size >= 4); V[3] = w; }
    void Set(T x, T y) { assert(Size >= 2); V[0] = x; V[1] = y; }
    void Set(T x, T y, T z) { assert(Size >= 3); V[0] = x; V[1] = y; V[2] = z; }
    void Set(T x, T y, T z, T w) { assert(Size >= 4); V[0] = x; V[1] = y; V[2] = z; V[3] = w; }

    bool operator ==(const Vector<Size, T>& other) const { return memcmp(V, other.V, Size * sizeof(T)) != 0; }
    bool operator !=(const Vector<Size, T>& other) const { return !operator ==(other); }

    Vector<Size, T> operator +(const Vector<Size, T>& other) const
    {
        Vector<Size, T> result;
        for (int i = 0; i < Size; ++i)
            result[i] = V[i] + other.V[i];
        return result;
    }

    Vector<Size, T> operator -(const Vector<Size, T>& other) const
    {
        Vector<Size, T> result;
        for (int i = 0; i < Size; ++i)
            result[i] = V[i] - other.V[i];
        return result;
    }

    Vector<Size, T> operator *(const T scalar) const
    {
        Vector<Size, T> result;
        for (int i = 0; i < Size; ++i)
            result[i] = V[i] * scalar;
        return result;
    }

    Vector<Size, T> operator /(const T scalar) const
    {
        assert(!IsZero(scalar));

        Vector<Size, T> result;
        for (int i = 0; i < Size; ++i)
            result[i] = V[i] / scalar;
        return result;
    }

    Vector<Size, T> operator +() const { return *this; }
    Vector<Size, T> operator -() const
    {
        Vector<Size, T> result;
        for (int i = 0; i < Size; ++i)
            result[i] = -V[i];
        return result;
    }

    Vector<Size, T>& operator =(const Vector<Size, T>& other) { memcpy(V, other.V, Size * sizeof(T)); return *this; }

    Vector<Size, T>& operator =(const T& val)
    {
        for (int i = 0; i < Size; ++i)
            V[i] = val;
        return *this;
    }

    Vector<Size, T>& operator =(const T arr[Size]) { memcpy(V, arr, Size * sizeof(T)); return *this; }
    
    Vector<Size, T>& operator +=(const Vector<Size, T>& other)
    {
        for (int i = 0; i < Size; ++i)
            V[i] += other[i];
        return *this;
    }

    Vector<Size, T>& operator -=(const Vector<Size, T>& other)
    {
        for (int i = 0; i < Size; ++i)
            V[i] -= other[i];
        return *this;
    }

    Vector<Size, T>& operator +=(const T& scalar)
    {
        for (int i = 0; i < Size; ++i)
            V[i] += scalar;
        return *this;
    }

    Vector<Size, T>& operator -=(const T& scalar)
    {
        for (int i = 0; i < Size; ++i)
            V[i] -= scalar;
        return *this;
    }

    Vector<Size, T>& operator *=(const T& scalar)
    {
        for (int i = 0; i < Size; ++i)
            V[i] *= scalar;
        return *this;
    }

    Vector<Size, T>& operator /=(const T& scalar)
    {
        assert(!IsZero(scalar));
        for (int i = 0; i < Size; ++i)
            V[i] /= scalar;
        return *this;
    }

    //! The magnitude or length of this vector
    T Magnitude() const { return sqrt(MagnitudeSqr()); }
    //! The squared magnitude or length of this vector (more efficient)
    T MagnitudeSqr() const
    {
        T sum;
        for (int i = 0; i < Size; ++i)
            sum += V[i] * V[i];
        return sum;
    }

    //! The distance of this vector to other vector
    T Distance(const Vector<Size, T>& other) const { return ((*this) - other).Magnitude(); }
    //! The squared distance of this vector to other vector (more efficient)
    T DistanceSqr(const Vector<Size, T>& other) const { return ((*this) - other).MagnitudeSqr(); }

	//! Normalizes this vector
    void Normalize()
    {
        if (!IsZero(MagnitudeSqr()) - static_cast<T>(1))
        {
            T length = Magnitude();
            for (int i = 0; i < Size; ++i)
                V[i] /= length;
            assert(IsZero(MagnitudeSqr() - static_cast<T>(1.0)));
        }
    }

    //! Return a normalized copy of this vector
    Vector<Size, T> NormalizeCopy() const
    {
        Vector<Size, T> copy(*this);
        copy.Normalize();
        return copy;
    }

	//! Returns the dot product (a scalar) between this vector and some other
    T DotProduct(const Vector<Size, T>& other) const
    {
        T sum;
        for (int i = 0; i < Size; ++i)
            sum += V[i] * other[i];
        return sum;
    }

	//! Returns the cross product (a vector) between this vector and some other
    Vector<Size, T> CrossProduct(const Vector<Size, T>& other) const
    {
        if (Size == 2)
            return Vector<1, T>(V[0] * other.V[1] - V[1] * other.V[0]);
        else if (Size == 3)
            return V[1] * other.V[2] - V[2] * other.V[1],
                V[2] * other.V[0] - V[0] * other.V[2],
                V[0] * other.V[1] - V[1] * other.V[0];
        else
        {
            assert(false && "Cross product not defined for more than 3 dimensions");
            return Vector<Size, T>;
        }
    }

	//! Returns the angle in radians of this vector and other
	float AngleBetween(const Vector<Size, T>& other) const
	{
		T dotP = DotProduct(other);
		T lengthP = Magnitude() * other.Magnitude();

		assert(!IsZero(lengthP));

		return acos((float)dotP / lengthP);
	}

	//! Returns a vector that is perpendicular to this vector
	//! There are many solutions, this will only get one of those
	Vector<Size, T> Perpendicular()
	{
        if (Size == 2)
            return Vector<Size, T>(-V[1], V[0]);
        else if (Size == 3)
        {
            Vector<Size, T> try1 = CrossProduct(Vector<Size, T>(1, 0, 0));

            if (IsZero(try1.MagnitudeSqr())) // vector is perpendicular to xx, pick a different one
                return CrossProduct(Vector<Size, T>(0, 1, 0));

            return try1;
        }
        else
        {
            assert(false && "Perpendicular vector is not defined for more than 3 dimensions");
            return Vector<Size, T>();
        }
	}
};

#endif // VECTOR_H
