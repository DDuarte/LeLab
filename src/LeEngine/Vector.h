#ifndef VECTOR_H
#define VECTOR_H

#include "DMath.h"
#include "MathDefines.h"

#include <type_traits>
// #include <initializer_list>

template<int Size, typename T = float>
class Vector
{
    static_assert(std::is_scalar<T>::value, "Vector should use a scalar type.");
private:
    T V[Size];

public:
    typedef typename std::conditional<std::is_floating_point<T>::value, T, double>::type Real;
    typedef T Type;
    static const int Size = Size;
    static const Vector<Size, T> ZERO;

    Vector() { memset(V, 0, Size * sizeof(T)); }

    Vector(T x, T y)
    {
        static_assert(Size == 2, "T x, T y constructor requires Size == 2");
        V[0] = x;
        V[1] = y;
    }

    Vector(T x, T y, T z)
    {
        static_assert(Size == 3, "T x, T y, T z constructor requires Size == 3");
        V[0] = x;
        V[1] = y;
        V[2] = z;
    }

    Vector(T x, T y, T z, T w)
    {
        static_assert(Size == 4, "T x, T y, T z, T w constructor requires Size == 4");
        V[0] = x;
        V[1] = y;
        V[2] = z;
        V[3] = w;
    }

    // One day this will be properly supported by compilers...
    //template< typename... Arguments>
    //Vector(Arguments... parameters)
    //{
    //    static const unsigned short int size = sizeof...(Arguments);
    //    static_assert(size == Size, "The number of arguments of Vector should be the same of the templated Size");
    //
    //    int i = 0;
    //    std::initializer_list<T> args = { parameters... };
    //    for (auto arg : args)
    //        V[i++] = static_cast<T>(arg);
    //}

    Vector(const Vector<Size, T>& other) { memcpy(V, other.V, Size * sizeof(T)); }
    Vector(const T arr[Size]) { memcpy(V, arr, Size * sizeof(T)); }
    Vector(T val) { for (int i = 0; i < Size; ++i) V[i] = val; }

    const T& X() const { static_assert(Size >= 1, "const X() requires at least size 1"); return V[0]; }
    const T& Y() const { static_assert(Size >= 2, "const Y() requires at least size 2"); return V[1]; }
    const T& Z() const { static_assert(Size >= 3, "const Z() requires at least size 3"); return V[2]; }
    const T& W() const { static_assert(Size >= 4, "const W() requires at least size 4"); return V[3]; }

    T& X() { static_assert(Size >= 1, "X() requires at least size 1"); return V[0]; }
    T& Y() { static_assert(Size >= 2, "Y() requires at least size 2"); return V[1]; }
    T& Z() { static_assert(Size >= 3, "Z() requires at least size 3"); return V[2]; }
    T& W() { static_assert(Size >= 4, "W() requires at least size 4"); return V[3]; }

    const T& operator [](int index) const { assert(index < Size); return V[index]; }
    T& operator [](int index) { assert(index < Size); return V[index]; }

    operator const T* () const { return V; }
    operator T* () { return V; }

    void SetX(T x) { static_assert(Size >= 1, "SetX() requires at least size 1"); V[0] = x; }
    void SetY(T y) { static_assert(Size >= 2, "SetY() requires at least size 2"); V[1] = y; }
    void SetZ(T z) { static_assert(Size >= 3, "SetZ() requires at least size 3"); V[2] = z; }
    void SetW(T w) { static_assert(Size >= 4, "SetW() requires at least size 4"); V[3] = w; }
    void Set(T x) { static_assert(Size >= 2, "Set(T) requires at least size 1"); V[0] = x; }
    void Set(T x, T y) { static_assert(Size >= 2, "Set(T, T) requires at least size 2"); V[0] = x; V[1] = y; }
    void Set(T x, T y, T z) { static_assert(Size >= 3, "Set(T, T, T) requires at least size 3"); V[0] = x; V[1] = y; V[2] = z; }
    void Set(T x, T y, T z, T w) { static_assert(Size >= 4, , "Set(T, T, T, T) requires at least size 4"); V[0] = x; V[1] = y; V[2] = z; V[3] = w; }

    bool operator ==(const Vector<Size, T>& other) const { return memcmp(V, other.V, Size * sizeof(T)) == 0; }
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

    Vector<Size, T> operator *(const T& scalar) const
    {
        Vector<Size, T> result;
        for (int i = 0; i < Size; ++i)
            result[i] = V[i] * scalar;
        return result;
    }

    Vector<Size, T> operator /(const T& scalar) const
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
    Real Magnitude() const { return Math<Real>::Sqrt(MagnitudeSqr()); }
    //! The squared magnitude or length of this vector (more efficient)
    T MagnitudeSqr() const
    {
        T sum = (T)0;
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
        if (!IsZero(MagnitudeSqr() - static_cast<T>(1)))
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
        T sum = 0;
        for (int i = 0; i < Size; ++i)
            sum += V[i] * other[i];
        return sum;
    }

	//! Returns the cross product (a vector) between this vector and some other
    Vector<Size, T> CrossProduct(const Vector<Size, T>& other) const
    {
        static_assert(Size == 2 || Size == 3, "Cross product not defined for more than 3 dimensions");

        if (Size == 2) // this needs some sort of split
            return V[0] * other.V[1] - V[1] * other.V[0];
        else if (Size == 3)
            return Vector<Size, T>(V[1] * other.V[2] - V[2] * other.V[1],
                V[2] * other.V[0] - V[0] * other.V[2],
                V[0] * other.V[1] - V[1] * other.V[0]);
    }

	//! Returns the angle in radians of this vector and other
	Real AngleBetween(const Vector<Size, T>& other) const
	{
		T dotP = DotProduct(other);
		Real lengthP = Magnitude() * other.Magnitude();

		assert(!IsZero(lengthP));

        return Math<Real>::ACos(dotP / lengthP);
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
            static_assert(false && "Perpendicular vector is not defined for more than 3 dimensions");
            return Vector<Size, T>();
        }
	}

    //! Also named box product. Signed volume of a parallelepiped formed by u, v and w.
    static T ScalarTripleProduct(const Vector<Size, T>& u, const Vector<Size, T>& v, const Vector<Size, T>& w)
    {
        return u.CrossProduct(v).DotProduct(w);
    }
};

template<int Size, typename T>
const Vector<Size, T> Vector<Size, T>::ZERO;

typedef Vector<2, float> Vector2f;
typedef Vector<2, double> Vector2d;
typedef Vector<2, int> Vector2i;
typedef Vector<3, float> Vector3f;
typedef Vector<3, double> Vector3d;
typedef Vector<3, int> Vector3i;

// Helpers for scalar multiplications
template <int Size, typename T> Vector<Size, T> operator *(const T& scalar, const Vector<Size, T>& rhs) { return rhs * scalar; }
template <int Size, typename T> Vector<Size, T> operator /(const T& scalar, const Vector<Size, T>& rhs) { return rhs / scalar; }

#endif // VECTOR_H
