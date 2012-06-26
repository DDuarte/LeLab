#ifndef MATRIX2_H
#define MATRIX2_H

#include "Vector2.h"
#include <cstring> // memcpy, memset
#include <cassert>
#include <cstdarg>

#include <boost/shared_array.hpp>
using boost::shared_array;

template <int Size, typename T = int>
class Matrix
{
private:
    T M[Size][Size];
public:
    Matrix() { memset(M, 0, Size*Size*sizeof(T)); }
    Matrix(const T arr[Size][Size]) { memcpy(M, arr, Size*Size*sizeof(T)); }
    Matrix(const Matrix<Size, T>& matrix) { memcpy(M, matrix.M, Size*Size*sizeof(T)); }

    Matrix(const T vals[Size*Size])
    {
        for (int i = 0; i < Size; ++i)
            for (int j = 0; j < Size; ++j)
                M[i][j] = vals[Size*i+j];
    }

    T Determinant()
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
            return M[0][0] * (M[1][1] * (M[2][2] * M[3][3] - M[2][3] * M[3][2]) -
                M[1][2] * (M[2][1] * M[3][3] - M[2][3] * M[3][1]) +
                M[1][3] * (M[2][1] * M[3][2] - M[2][2] * M[3][1])) -
                M[0][1] * (M[1][0] * (M[2][2] * M[3][3] - M[2][3] * M[3][2]) -
                M[1][2] * (M[2][0] * M[3][3] - M[2][3] * M[3][0]) +
                M[1][3] * (M[2][0] * M[3][2] - M[2][2] * M[3][0])) +
                M[0][2] * (M[1][0] * (M[2][1] * M[3][3] - M[2][3] * M[3][1]) -
                M[1][1] * (M[2][0] * M[3][3] - M[2][3] * M[3][0]) +
                M[1][3] * (M[2][0] * M[3][1] - M[2][1] * M[3][0])) -
                M[0][3] * (M[1][0] * (M[2][1] * M[3][2] - M[2][2] * M[3][1]) -
                M[1][1] * (M[2][0] * M[3][2] - M[2][2] M[3][0]) +
                M[1][2] * (M[2][0] * M[3][1] - M[2][1] M[3][0]));
        }
        else
        {
            return -1;
            // Implement Laplace expansion
        }
    }

    //Matrix(int num, ...)
    Matrix(int num, ...)
    {
        assert(num == Size*Size);

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

    shared_array<T> GetRow(int row) const
    {
        assert(row < Size);

        shared_array<T> r(new T[Size]);
        memcpy(r, M[row], Size);

        return r;
    }

    shared_array<T> GetColumn(int column) const
    {
        assert(column < Size);

        shared_array<T> col(new T[Size]);

        T col[Size];
        for (int i = 0; i < Size; ++i)
            col[i] = M[i][column];
        return col;
    }
};

#endif // MATRIX2_H
