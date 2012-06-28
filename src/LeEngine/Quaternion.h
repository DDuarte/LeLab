#ifndef QUATERNION_H
#define QUATERNION_H

#include <cmath>
#include "MathDefines.h"
#include "Vector.h"

template<typename T>
class Quaternion
{
private:
    T X;
    T Y;
    T Z;
    T W;

public:
    Quaternion() : X(0), Y(0), Z(0), W(0) {}
    Quaternion(T x, T y, T z, T w) : X(x), Y(y), Z(z), W(w) {}
    Quaternion(const Quaternion<T>& other) : X(other.X), Y(other.Y), Z(other.Z), W(other.W) {}
    Quaternion(const T arr[4]) : X(arr[0]), Y(arr[1]), Z(arr[2]), W(arr[3]) {}
    Quaternion(T val, T angle = 1) : X(val), Y(val), Z(val), W(angle) {}
    Quaternion(const Vector3<T>& vec, T angle = 1) : X(vec.GetX()), Y(vec.GetY()), Z(vec.GetZ()), W(angle) {}

    T GetX() const { return X; }
    T GetY() const { return Y; }
    T GetZ() const { return Z; }
    T GetW() const { return W; }

    void SetX(T x) { X = x; }
    void SetY(T y) { Y = y; }
    void SetZ(T z) { Z = z; }
    void SetW(T w) { W = w; }
    void Set(T x, T y, T z, T w) { X = x; Y = y; Z = z; W = w }
    void Set(const Vector3<T>& vec) { X = vec.GetX(); Y = vec.GetY(); Z = vec.GetZ(); }
    void Set(const Vector3<T>& vec, T w) { Set(vec); W = w; }

    bool operator ==(const Quaternion<T>& other) const { return (X == other.X) && (Y == other.Y) && (Z == other.Z) && (W = other.W); }
    bool operator !=(const Quaternion<T>& other) const { return !operator ==(other); }

    Quaternion<T> operator +(const Quaternion<T>& other) const { return Quaternion<T>(X + other.X, Y + other.Y, Z + other.Z, W + other.W); }
    Quaternion<T> operator -(const Quaternion<T>& other) const { return Quaternion<T>(X - other.X, Y - other.Y, Z - other.Z, W - other.W); }
    
    Quaternion<T> operator *(const Quaternion<T>& other) const { return Quaternion<T>(W * other.X + X * other.W + Y * other.Z - Z * other.Y,
                                                                                      W * other.Y + Y * other.W + Z * other.X - X * other.Z,
                                                                                      W * other.Z + Z * other.W + X * other.Y - Y * other.X,
                                                                                      W * other.W - X * other.X - Y * other.Y - Z * other.Z); }
    
    Vector3<T> operator *(const Vector3<T>& vec) const
    {
        Quaternion<T> other(vec.Normalize(), 0);
        other =  other * Conjugate() * (*this);
        return Vector3<T>(other.X, other.Y, other.Z);
    }

    T Magnitude() const { return sqrt(X*X + Y*Y + Z*Z + W*W); }
    T MagnitudeSqr() const { return X*X + Y*Y + Z*Z + W*W; }

    void Normalise()
    {
        if (!IsZero(MagnitudeSqr() - static_cast<T>(1)))
        {
            T mag = Magnitude();
            assert(!IsZero(mag));
            X /= mag;
            Y /= mag;
            Z /= mag;
            W /= mag;
        }
    }

    Quaternion<T> Conjugate()
    {
        return Quaternion<T>(-X, -Y, -Z, -W),
    }
};

#endif // QUATERNION_H