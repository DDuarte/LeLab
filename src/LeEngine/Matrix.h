#ifndef MATRIX_H
#define MATRIX_H

#include "Vector.h"
#include "DMath.h"
#include "MathDefines.h"

#include <cassert>
#include <cstdarg>
#include <vector>
#include <algorithm>
#include <array>
#include <initializer_list>
#include <iostream>

template <int Size, typename T = float>
class Matrix
{
    static_assert(std::is_scalar<T>::value, "Matrix should use a scalar type.");
private:
    union
    {
        std::array<std::array<T, Size>, Size> M;
        std::array<T, Size * Size> _M;
    };

public:
    typedef typename std::conditional<std::is_floating_point<T>::value, T, double>::type Real;
    typedef T Type;
    static const int Size = Size;
    static const Matrix<Size, T> IDENTITY;
    static const Matrix<Size, T> ZERO;

    Matrix() { _M.fill(0); }

    Matrix(const T arr[Size][Size]) { memcpy(_M.data(), arr, sizeof(T) * Size * Size); }
    Matrix(const T arr[Size*Size]) { memcpy(_M.data(), arr, sizeof(T) * Size * Size); }
    Matrix(T arr[Size*Size]) { memcpy(_M.data(), arr, sizeof(T) * Size * Size); }
    Matrix(T arr[Size][Size]) { memcpy(_M.data(), arr, sizeof(T) * Size * Size); }

    Matrix(const Matrix<Size, T>& matrix) : M(matrix.M) { }

    template <typename... Arguments>
    Matrix(T first, Arguments... parameters)
    {
        // This isn't pretty but it is working on MSVC CTP Nov 2012
        auto arr = { first, parameters... };

        int i = 0;
        for (auto& a : arr)
            _M[i++] = a;
    }

    const std::array<T, Size>& operator[](int row) const { assert(row < Size); return M[row]; }
    std::array<T, Size>& operator[](int row) { assert(row < Size); return M[row]; }

    Matrix<Size, T>& operator =(const Matrix<Size, T>& other) { memcpy(_M.data(), other._M.data(), Size * Size * sizeof(T)); return *this; }

    bool operator ==(const Matrix<Size, T>& other) const
    {
        if (std::is_floating_point<T>::value)
        {
            for (int i = 0; i < Size * Size; ++i)
                if (!Math<Real>::IsFuzzyEqual(_M[i], other._M[i]))
                    return false;
            return true;
        }
        else
            return memcmp(_M.data(), other._M.data(), Size * Size * sizeof(T)) == 0;
    }
    bool operator !=(const Matrix<Size, T>& other) const { return !operator ==(other); }

    T operator ()(int row, int column) const { return M[row][column]; }
    T& operator ()(int row, int column) { return M[row][column]; }

    operator const T* () const { return _M.data(); }
    operator T* () { return _M.data(); }

    Matrix<Size, T> operator +(const Matrix<Size, T>& other) const
    {
        Matrix<Size, T> result;
        for (int row = 0; row < Size; ++row)
            for (int col = 0; col < Size; ++col)
                result.M[row][col] = M[row][col] + other.M[row][col];
        return result;
    }

    Matrix<Size, T> operator -(const Matrix<Size, T>& other) const
    {
        Matrix<Size, T> result;
        for (int row = 0; row < Size; ++row)
            for (int col = 0; col < Size; ++col)
                result.M[row][col] = M[row][col] - other.M[row][col];
        return result;
    }

    Matrix<Size, T> operator -() const
    {
        Matrix<Size, T> result;
        for (int row = 0; row < Size; ++row)
            for (int col = 0; col < Size; ++col)
                result.M[row][col] = -M[row][col];
        return result;
    }

    Matrix<Size, T> operator *(const Matrix<Size, T>& other) const
    {
        Matrix<Size, T> result;

        for (int row = 0; row < Size; ++row)
            for (int col = 0; col < Size; ++col)
                for (int i = 0; i < Size; ++i)
                    result.M[row][col] += M[row][i] * other.M[i][col];
        return result;
    }

    Vector<Size, T> operator *(const Vector<Size, T>& other) const
    {
        Vector<Size, T> result;
        for (int row = 0; row < Size; ++row)
            for (int i = 0; i < Size; ++i)
                result[row] += M[row][i] * other[i];
        return result;
    }

    Matrix<Size, T> operator *(const T& scalar) const
    {
        Matrix<Size, T> result;
        for (int row = 0; row < Size; ++row)
            for (int col = 0; col < Size; ++col)
                result[row][col] = M[row][col] * scalar;
        return result;
    }

    std::array<T, Size> GetRow(int row) const
    {
        assert(row < Size);
        return M[row];
    }

    std::array<T, Size> GetColumn(int column) const
    {
        assert(column < Size);

        std::array<T, Size> r;

        for (int i = 0; i < Size; ++i)
            r[i] = M[i][column];

        return r;
    }

    Matrix<Size, T>& SetRow(int row, const T arr[Size])
    {
        assert(row < Size);
        for (int i = 0; i < Size; ++i)
            M[row][i] = arr[i];

        return *this;
    }

    Matrix<Size, T>& SetColumn(int column, const T arr[Size])
    {
        assert(column < Size);
        for (int i = 0; i < Size; ++i)
            M[i][column] = arr[i];

        return *this;
    }

    Matrix<Size, T>& ExchangeColumn(int column1, int column2)
    {
        assert(column1 < Size && column2 < Size);
        if (column1 != column2)
        {
            std::array<T, Size> aux = GetColumn(column1);
            SetColumn(column1, GetColumn(column2).data());
            SetColumn(column2, aux.data());
        }

        return *this;
    }

    Real Determinant() const
    {
        if (Size == 1)
            return M[0][0];
        else if (Size == 2)
            return M[0][0] * M[1][1] - M[0][1] * M[1][0];
        else if (Size == 3)
        {
            return M[0][0] * (M[1][1]*M[2][2] - M[1][2]*M[2][1]) -
                M[0][1] * (M[1][0]*M[2][2] - M[1][2]*M[2][0]) +
                M[0][2] * (M[1][0]*M[2][1] - M[1][1]*M[2][0]);
        }
        else if (Size == 4)
        {
            return
                M[0][0] * (M[1][1] * (M[2][2] * M[3][3] - M[2][3] * M[3][2]) -
                M[1][2] * (M[2][1] * M[3][3] - M[2][3] * M[3][1]) +
                M[1][3] * (M[2][1] * M[3][2] - M[2][2] * M[3][1])) -
                M[0][1] * (M[1][0] * (M[2][2] * M[3][3] - M[2][3] * M[3][2]) -
                M[1][2] * (M[2][0] * M[3][3] - M[2][3] * M[3][0]) +
                M[1][3] * (M[2][0] * M[3][2] - M[2][2] * M[3][0])) +
                M[0][2] * (M[1][0] * (M[2][1] * M[3][3] - M[2][3] * M[3][1]) -
                M[1][1] * (M[2][0] * M[3][3] - M[2][3] * M[3][0]) +
                M[1][3] * (M[2][0] * M[3][1] - M[2][1] * M[3][0])) -
                M[0][3] * (M[1][0] * (M[2][1] * M[3][2] - M[2][2] * M[3][1]) -
                M[1][1] * (M[2][0] * M[3][2] - M[2][2] * M[3][0]) +
                M[1][2] * (M[2][0] * M[3][1] - M[2][1] * M[3][0]));
        }
        else
        {
            Matrix<Size, T> m(*this);
            int colEx = 0; // Number of columns exchange
            bool flag = true; // Has line of zeros
            int j;
            for (int k = 0; k < Size - 1; ++k)
            {
                j = k + 1;
                flag = true;
                while (flag && j <= Size)
                    if (m[k][j - 1] != 0)
                        flag = false;
                    else
                        ++j;

                if (flag) return 0.0;

                if (j != k + 1)
                {
                    ++colEx;
                    m.ExchangeColumn(k, j - 1);
                }

                for (int i = k + 2; i <= Size; ++i)
                {
                    for (int j = k + 2; j <= Size; ++j)
                        m[i - 1][j - 1] = m[i - 1][j - 1] - m[i - 1][k] * m[k][j - 1] / m[k][k];

                    m[i - 1][k] = 0;
                }
            }

            Real det = 1;
            for (int i = 0; i < Size; ++i)
                det *= m[i][i];

            return det * Math<Real>::Pow(-1.0, colEx);
        }
    }

    Matrix<Size, T>& Transpose()
    {
        Matrix<Size, T> aux(*this);

        for (int i = 0; i < Size; ++i)
            SetRow(i, aux.GetColumn(i).data());

        return *this;
    }

    Matrix<Size, T> GetTransposed() const
    {
        Matrix<Size, T> aux(*this);
        return aux.Transpose();
    }

    Real Cofactor(int l, int c) const
    {
        const Matrix<Size,T>& m = *this;
        std::vector<Real> subMatrixVec;
        
        for (int i = 0; i < Size; i++)
            if (i != l)
                for (int j = 0; j < Size; j++)
                    if (j != c)
                        subMatrixVec.push_back(m[i][j]);

        Matrix<Size-1, Real> subMat(&subMatrixVec[0]);

        return Math<Real>::Pow(-1.0, l+c) * subMat.Determinant(); 
    }

    Matrix<Size, T> CofactorsMatrix() const
    {
        Matrix<Size,T> mat;

        if (Size == 1)
            mat = (*this);
        else if (Size == 2)
        {
            T matArr[] = { M[1][1], -M[1][0], -M[0][1], M[0][0] };
            mat = matArr;
        }
        else if (Size == 3)
        {
            T matArr[] = { M[1][1]*M[2][2]-M[1][2]*M[2][1], 
                M[1][2]*M[2][0]-M[1][0]*M[2][2],
                M[1][0]*M[2][1]-M[1][1]*M[2][0],
                M[0][2]*M[2][1]-M[0][1]*M[2][2],
                M[0][0]*M[2][2]-M[0][2]*M[2][0],
                M[0][1]*M[2][0]-M[0][0]*M[2][1],
                M[0][1]*M[1][2]-M[0][2]*M[1][1],
                M[0][2]*M[1][0]-M[0][0]*M[1][2],
                M[0][0]*M[1][1]-M[0][1]*M[1][0] };
            mat = matArr;
        }
        else
        {
            std::vector<T> cofactorMatrixVec;
            for (int i = 0; i < Size; i++)
                for (int j = 0; j < Size; j++)
                    cofactorMatrixVec.push_back(static_cast<T>(Cofactor(i,j)));
            mat = cofactorMatrixVec.data();
        }

        return mat;
    }

    Matrix<Size, Real> GetInverse() const
    {
        Matrix<Size, T> m = GetTransposed().CofactorsMatrix();
        return m.ToReal() * (static_cast<Real>(1) / Determinant());
    }

    Matrix<Size, Real> ToReal() const
    {
        //if (std::is_floating_point<T>::value)
        //    return *this;

        Matrix<Size, Real> result;
        for (int i = 0; i < Size; ++i)
            for (int j = 0; j < Size; ++j)
                result[i][j] = static_cast<Real>(M[i][j]);
        return result;
    }

private:
    static Matrix<Size, T> BuildIdentityMatrix()
    {
        Matrix<Size, T> result;
        for (int row = 0; row < Size; ++row)
            for (int col = 0; col < Size; ++col)
                result(row, col) = (row == col) ? static_cast<T>(1) : static_cast<T>(0);
        return result;
    }
    
};

template <int Size, typename T>
const Matrix<Size, T> Matrix<Size, T>::ZERO;

template <int Size, typename T>
const Matrix<Size, T> Matrix<Size, T>::IDENTITY = BuildIdentityMatrix();

typedef Matrix<3, float> Matrix3f;
typedef Matrix<3, double> Matrix3d;
typedef Matrix<3, int> Matrix3i;
typedef Matrix<4, float> Matrix4f;
typedef Matrix<4, double> Matrix4d;
typedef Matrix<4, int> Matrix4i;

// Helpers for scalar multiplications
template <int Size, typename T> Matrix<Size, T> operator *(const T& scalar, const Matrix<Size, T>& rhs) { return rhs * scalar; }
template <int Size, typename T> Matrix<Size, T> operator /(const T& scalar, const Matrix<Size, T>& rhs) { return rhs / scalar; }

template <int Size, typename T>
::std::ostream& operator<<(::std::ostream& os, const Matrix<Size, T>& m)
{
    os << "(";
    for (int i = 0; i < Size; ++i)
        for (int j = 0; j < Size; ++j)
            os << m[i][j] << ", ";
    os << ")";
    
    return os;
}

inline Matrix4f CreateTranslasteMatrix(float x, float y, float z)
{
    float m[] = { 1, 0, 0, x,
                  0, 1, 0, y,
                  0, 0, 1, z,
                  0, 0, 0, 1 };
    return Matrix4f(m);
}

inline Matrix4f CreateScaleMatrix(float x, float y, float z)
{
    float m[] = { x, 0, 0, 0,
                  0, y, 0, 0,
                  0, 0, z, 0,
                  0, 0, 0, 1 };
    return Matrix4f(m);
}

inline Matrix4f CreateRotateMatrix(float rotation, Vector3f axis)
{
    float a = rotation * Math<float>::ACos(-1.0f) / 180.0f;
    float c = Math<float>::Cos(a);
    float s = Math<float>::Sin(a);

    axis.Normalize();

    Vector3f temp = axis * (1-c);

    float m[] = { axis[0] * temp[0] + c,
                  axis[1] * temp[0] - axis[2] * s,
                  axis[2] * temp[0] + axis[1] * s,
                  0,
                  axis[0] * temp[1] + axis[2] * s,
                  axis[1] * temp[1] + c,
                  axis[2] * temp[1] - axis[0] * s,
                  0,
                  axis[0] * temp[2] - axis[1] * s,
                  axis[1] * temp[2] + axis[0] * s,
                  axis[2] * temp[2] + c,
                  0,
                  0, 0, 0, 1 };

    return Matrix4f(m);
}

#endif // MATRIX_H
