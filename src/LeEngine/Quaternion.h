#ifndef QUATERNION_H
#define QUATERNION_H

#include <cmath>
#include "MathDefines.h"
#include "Vector.h"
#include "Matrix.h"

class Quaternion
{
private:
    float X;
    float Y;
    float Z;
    float W;

public:
    Quaternion() : X(0), Y(0), Z(0), W(0) {}
    Quaternion(float x, float y, float z, float w) : X(x), Y(y), Z(z), W(w) {}
    Quaternion(const Quaternion& other) : X(other.X), Y(other.Y), Z(other.Z), W(other.W) {}
    Quaternion(const float arr[4]) : X(arr[0]), Y(arr[1]), Z(arr[2]), W(arr[3]) {}
    Quaternion(float val, float angle = 1) : X(val), Y(val), Z(val), W(angle) {}
    Quaternion(const Vector<3, float>& vec, float angle = 1) : X(vec.X()), Y(vec.Y()), Z(vec.Z()), W(angle) {}

    float GetX() const { return X; }
    float GetY() const { return Y; }
    float GetZ() const { return Z; }
    float GetW() const { return W; }

    void SetX(float x) { X = x; }
    void SetY(float y) { Y = y; }
    void SetZ(float z) { Z = z; }
    void SetW(float w) { W = w; }
    void Set(float x, float y, float z, float w) { X = x; Y = y; Z = z; W = w; }
    void Set(const Vector<3, float>& vec) { X = vec.X(); Y = vec.Y(); Z = vec.Z(); W = 0.0f; }
    void Set(const Vector<3, float>& vec, float w) { Set(vec); W = w; }

    bool operator ==(const Quaternion& other) const { return IsZero(X - other.X) && IsZero(Y - other.Y) && IsZero(Z - other.Z) && IsZero(Z - other.Z); }
    bool operator !=(const Quaternion& other) const { return !operator ==(other); }

    Quaternion operator +(const Quaternion& other) const { return Quaternion(X + other.X, Y + other.Y, Z + other.Z, W + other.W); }
    Quaternion& operator +=(const Quaternion& other) { X += other.X; Y += other.Y; Z += other.Z; W += other.W; return *this; }

    Quaternion operator -(const Quaternion& other) const { return Quaternion(X - other.X, Y - other.Y, Z - other.Z, W - other.W); }
    Quaternion& operator -=(const Quaternion& other) { X -= other.X; Y -= other.Y; Z -= other.Z; W -= other.W; return *this; }

    Quaternion operator *(const Quaternion& other) const { return Quaternion(W * other.X + X * other.W + Y * other.Z - Z * other.Y,
                                                                             W * other.Y + Y * other.W + Z * other.X - X * other.Z,
                                                                             W * other.Z + Z * other.W + X * other.Y - Y * other.X,
                                                                             W * other.W - X * other.X - Y * other.Y - Z * other.Z); }

    Quaternion operator *(float val) const { return Quaternion(X * val, Y * val, Z * val, W * val); }
    Quaternion& operator *=(float val) { X *= val; Y *= val; Z *= val; W *= val; return *this; }

    Vector<3, float> operator *(const Vector<3, float>& vec) const
    {
        Quaternion other(vec.NormalizeCopy(), 0);
        other = other * Conjugate();
        other = (*this) * other;
        return Vector<3, float>(other.X, other.Y, other.Z);
    }

    //! Convert from axis angles
    void FromAxis(const Vector<3, float>& vec, float angle)
    {
        float sinAngle;
        angle *= 0.5f;
        Vector<3, float> vn(vec);
        vn.Normalize();

        sinAngle = sin(angle);

        X = (vn.X() * sinAngle);
        Y = (vn.Y() * sinAngle);
        Z = (vn.Z() * sinAngle);
        W = cos(angle);
    }

    //! Convert from Euler angles
    void FromEuler(float pitch, float yaw, float roll)
    {
        const float f = (PI / 180.0f) / 2.0f;
        float p = pitch * f;
        float y = yaw * f;
        float r = roll * f;

        float sinp = sin(p);
        float siny = sin(y);
        float sinr = sin(r);
        float cosp = cos(p);
        float cosy = cos(y);
        float cosr = cos(r);

        X = sinr * cosp * cosy - cosr * sinp * siny;
        Y = cosr * sinp * cosy + sinr * cosp * siny;
        Z = cosr * cosp * siny - sinr * sinp * cosy;
        W = cosr * cosp * cosy + sinr * sinp * siny;

        Normalize();
    }

    Matrix<4, float> GetMatrix() const
    {
        float x2 = X * X;
        float y2 = Y * Y;
        float z2 = Z * Z;
        float xy = X * Y;
        float xz = X * Z;
        float yz = Y * Z;
        float wx = W * X;
        float wy = W * Y;
        float wz = W * Z;

        // TODO: Verify that this is setting the right columns/rows
        return Matrix<4, float>(16, 1.0f - 2.0f * (y2 + z2), 2.0f * (xy - wz), 2.0f * (xz + wy), 0.0f,
            2.0f * (xy + wz), 1.0f - 2.0f * (x2 + z2), 2.0f * (yz - wx), 0.0f,
            2.0f * (xz - wy), 2.0f * (yz + wx), 1.0f - 2.0f * (x2 + y2), 0.0f,
            0.0f, 0.0f, 0.0f, 1.0f);
    }

    void GetAxisAngles(Vector<3, float>* axis, float* angle) const
    {
        float scale = sqrt(X*X + Y*Y + Z*Z);
        axis->SetX(X / scale);
        axis->SetY(Y / scale);
        axis->SetZ(Z / scale);
        *angle = acos(W) * 2.0f;
    }

    //! The magnitude or length of this vector
    float Magnitude() const { return sqrt(X*X + Y*Y + Z*Z + W*W); }
    //! The squared magnitude or length of this vector (more efficient)
    float MagnitudeSqr() const { return X*X + Y*Y + Z*Z + W*W; }

    void Normalize()
    {
        if (!IsZero(MagnitudeSqr() - 1.0f))
        {
            float mag = Magnitude();
            assert(!IsZero(mag));
            X /= mag;
            Y /= mag;
            Z /= mag;
            W /= mag;
            
            assert(IsZero(MagnitudeSqr() - 1.0f)); // validation
        }
    }

    Quaternion Conjugate() const { return Quaternion(-X, -Y, -Z, W); }


};

#endif // QUATERNION_H
