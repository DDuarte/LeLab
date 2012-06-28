#ifndef MATRIX_H
#define MATRIX_H

#include "Vector.h"
#include <cstring> // memcpy, memset
#include <cassert>
#include <cstdarg>
#include <vector>

#include <boost/shared_array.hpp>
using boost::shared_array;

template <int Size, typename T = int>
class Matrix
{
private:
    T M[Size][Size];

public:
    Matrix() { memset(M, 0, Size * Size * sizeof(T)); }

    Matrix(const T arr[Size][Size]) { memcpy(M, arr, Size * Size * sizeof(T)); }

    Matrix(const Matrix<Size, T>& matrix) { memcpy(M, matrix.M, Size * Size * sizeof(T)); }

    Matrix(const T vals[Size * Size])
    {
        for (int i = 0; i < Size; ++i)
            for (int j = 0; j < Size; ++j)
                M[i][j] = vals[Size * i + j];
    }

    Matrix(int num, ...)
    {
        assert(num == Size * Size);

        va_list arguments;

        // Non portable hack to use this without requiring argument num:
        // int a = ((int)this) - 228;
        // arguments = (va_list)a + sizeof(a);
        va_start(arguments, num);

        for (int i = 0; i < Size; ++i)
            for (int j = 0; j < Size; ++j)
                M[i][j] = va_arg(arguments, T);

        va_end(arguments); 
    }

    T* operator[](int row) const { assert(row < Size); return (T*)M[row]; }

    Matrix<Size, T>& operator =(const Matrix<Size, T>& other) { memcpy(M, other.M, Size * Size * sizeof(T)); return *this; }

    bool operator ==(const Matrix<Size, T>& other) const { return memcmp(M, other.M, Size * Size * sizeof(T)) == 0; }
    bool operator !=(const Matrix<Size, T>& other) const { return !operator ==(other); }

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

    template <typename S>
    Matrix<Size, T> operator *(const S& scalar) const
    {
        Matrix<Size, T> result;
        for (int row = 0; row < Size; ++row)
            for (int col = 0; col < Size; ++col)
                result[row][col] = M[row][col] * scalar;
        return result;
    }

    shared_array<T> GetRow(int row) const
    {
        assert(row < Size);

        shared_array<T> r(new T[Size]);
        memcpy(r, M[row], Size * sizeof(T));

        return r;
    }

    shared_array<T> GetColumn(int column) const
    {
        assert(column < Size);

        shared_array<T> col(new T[Size]);
        for (int i = 0; i < Size; ++i)
            col[i] = M[i][column];
        return col;
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
            shared_array<T> aux = GetColumn(column1);
            SetColumn(column1, GetColumn(column2).get());
            SetColumn(column2, aux.get());
        }

        return *this;
    }

    double Determinant() const
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

            double det = 1;
            for (int i = 0; i < Size; ++i)
                det *= m[i][i];

            return det * pow(-1.0, colEx);
        }
    }

    Matrix<Size, T>& Transpose()
    {
        Matrix<Size, T> aux(*this);

        for (size_t i = 0; i < Size; ++i)
            SetRow(i, aux.GetColumn(i).get());

        return *this;
    }

    Matrix<Size, T> GetTransposed() const
    {
        Matrix<Size, T> aux(*this);
        return aux.Transpose();
    }

    double Cofactor(int l, int c) const
    {
        const Matrix<Size,T>& M = *this;
        std::vector<double> Mij;
        
        for (int i = 0; i < Size; i++)
            if (i != l)
                for (int j = 0; j < Size; j++)
                    if (j != c)
                        Mij.push_back(M[i][j]);

        Matrix<Size-1, double> Mat(&Mij[0]);

        return pow(-1, l+c) * Mat.Determinant(); 
    }

    Matrix<Size, T> CofactorsMatrix() const
    {
        Matrix<Size,T> Mat();

        const Matrix<Size,T>& M = *this;

        if (Size == 1)
            Mat = M;
        else if (Size == 2)
            Mat = Matrix<Size,T>( { M[1][1], -M[1][0], -M[0][1], M[0][0] } );
        else if (Size == 3)
            Mat = Matrix<Size,T>( { M[1][1]*M[2][2]-M[1][2]*M[2][1], 
                                    M[1][2]*M[2][0]-M[1][0]*M[2][2],
                                    M[1][0]*M[2][1]-M[1][1]*M[2][0],
                                    M[0][2]*M[2][1]-M[0][1]*M[2][2],
                                    M[0][0]*M[2][2]-M[0][2]*M[2][0],
                                    M[0][1]*M[2][0]-M[0][0]*M[2][1],
                                    M[0][1]*M[1][2]-M[0][2]*M[1][1],
                                    M[0][2]*M[1][0]-M[0][0]*M[1][2],
                                    M[0][0]*M[1][1]-M[0][1]*M[1][0] } );
        else
        {
            std::vector<T> CM;
            for (int i = 0; i < Size; i++)
                for (int j = 0; j < Size; j++)
                    CM.push_back(M.Cofactor(i,j));
            Mat = &CM[0];
        }

        return Mat;
    }

    //! Returns true if matrix is invertible. Result is stored in first argument, result.
    bool Inverse(Matrix<Size, T>& result) const
    {
        double determinant = Determinant();

        if (IsZero(determinant))
            return false;

        Matrix<Size, T> mcopy(*this);

        determinant = 1.0 / determinant;
        result = mcopy.Transpose().CofactorsMatrix() * (T)determinant;
        return true;
    }

    
};

#endif // MATRIX_H
