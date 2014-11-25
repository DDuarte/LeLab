#include "gtest/gtest.h"
#include <LeEngine/Matrix.h>

template <class T>
class MatrixTest : public testing::Test
{
};

typedef testing::Types<float, double, int> TestTypes;
TYPED_TEST_CASE(MatrixTest, TestTypes);

TYPED_TEST(MatrixTest, Identities3) {
	using MyMatrix = Matrix<3, TypeParam>;

    TypeParam a[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    TypeParam b[] = { 14, 2, 4, 94, -2, 10, 43, 8, 10 };
    TypeParam c[] = { 1, 1, 1, 1, 1, 1, 1, 1, 1 };

    const MyMatrix A(a);
    const MyMatrix B(b);
    const MyMatrix C(c);
    const TypeParam r = 3;
    const TypeParam s = -5;

    EXPECT_EQ(A + B, B + A); // A+B=B+A
    EXPECT_EQ(A + (B + C), (A + B) + C); // A+(B+C)=(A+B)+C
    EXPECT_EQ(A - B, A + (-B)); // A−B=A+(−B)
    EXPECT_EQ(-(-A), A); // −(−A)=A
    EXPECT_EQ(s * (A + B), s * A + s * B); // s(A±B)=sA±sB
    EXPECT_EQ(s * (A - B), s * A - (s * B));
    EXPECT_EQ((r + s) * A, r * A + s * A); // (r±s)A=rA±sA
    EXPECT_EQ((r - s) * A, r * A - s * A);
    EXPECT_EQ(r * (s * A), s * (r * A)); // r(sA)=s(rA)=(rs)A
    EXPECT_EQ(r * (s * A), (r * s) * A);

    EXPECT_EQ(A * MyMatrix::IDENTITY, MyMatrix::IDENTITY * A); // AI=IA=A
    EXPECT_EQ(A * MyMatrix::IDENTITY, A);
    EXPECT_EQ(A * (B * C), (A * B) * C); // A(BC)=(AB)C
    EXPECT_EQ(A * (B + C), A * B + A * C); // A(B±C)=AB±AC
    EXPECT_EQ(A * (B - C), A * B - A * C);
    EXPECT_EQ((A + B) * C, A * C + B * C); // (A±B)C=AC±BC
    EXPECT_EQ((A - B) * C, A * C - B * C);
    EXPECT_EQ((s * A) * B, s * (A * B)); // (sA)B=s(AB)=A(sB)
    EXPECT_EQ((s * A) * B, A * (s * B));

    EXPECT_EQ((A + B).GetTransposed(), A.GetTransposed() + B.GetTransposed()); // (A±B)^T=A^T±B^T
    EXPECT_EQ((A - B).GetTransposed(), A.GetTransposed() - B.GetTransposed());
    EXPECT_EQ((s * A).GetTransposed(), s * A.GetTransposed()); // (sA)^T=sA^T
    EXPECT_EQ((A * B).GetTransposed(), B.GetTransposed() * A.GetTransposed()); // (AB)^T=B^TA^T
}

TYPED_TEST(MatrixTest, Determinants3) {
	using MyMatrix = Matrix<3, TypeParam>;

    TypeParam a[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    TypeParam b[] = { 1, 2, 3, 0, 4, 5, 1, 0, 6 }; // invertible

    const MyMatrix A(a);
    const MyMatrix B(b);

    EXPECT_NEAR(MyMatrix::IDENTITY.Determinant(), 1, Math<typename MyMatrix::Real>::EPSILON * 100);
    EXPECT_NEAR(A.GetTransposed().Determinant(), A.Determinant(), Math<typename MyMatrix::Real>::EPSILON * 100);
    EXPECT_NEAR(B.GetInverse().Determinant(), 1.0 / B.Determinant(), Math<typename MyMatrix::Real>::EPSILON * 100);
}
