#include "gtest/gtest.h"
#include <LeEngine/Vector.h>

template <class T>
class VectorTest : public testing::Test
{
};

typedef testing::Types<float, double, int> TestTypes;
TYPED_TEST_CASE(VectorTest, TestTypes);

TYPED_TEST(VectorTest, Identities3) {
    using MyVector = Vector<3, TypeParam>;

    const MyVector u(1, 2, 3);
    const MyVector v(6, 6, 6);
    const MyVector w(-8, -8, -8);

    EXPECT_EQ(v + u, u + v); // u + v = v + u
    EXPECT_EQ(u + (v + w), (u + v) + w); // (u + v) + w = u + (v + w)
    EXPECT_EQ(u + (-v), u - v); // u - v = u + (-v)
    EXPECT_EQ(v, -(-v)); // -(-v) = v
    EXPECT_EQ(MyVector::ZERO, v + (-v)); // v + (-v) = 0
    EXPECT_EQ(MyVector::ZERO + v, v + MyVector::ZERO); // v + 0 = 0 + v = v
    EXPECT_EQ(MyVector::ZERO + v, v); // v + 0 = 0 + v = v

    const TypeParam r = 3;
    const TypeParam s = -5;

    EXPECT_EQ((r * s) * v, r * (s * v)); // r(sv) = (rs)v
    EXPECT_EQ(r * v + s * v, (r + s) * v); // (r + s)v = rv + sv
    EXPECT_EQ(s * u + s * v, s * (u + v)); // s(u + v) = su + sv
    EXPECT_EQ(v, static_cast<TypeParam>(1.0) * v); // 1v = v
}

TYPED_TEST(VectorTest, IdentitiesDot3) {
	using MyVector = Vector<3, TypeParam>;

    const MyVector u(1, 2, 3);
    const MyVector v(6, 6, 6);
    const MyVector w(-8, -8, -8);

    EXPECT_EQ(u.X() * v.X() + u.Y() * v.Y() + u.Z() * v.Z(), u.DotProduct(v)); // u . v = u1v1 + u2v2 + ... + unvn
    EXPECT_EQ(u.Magnitude() * v.Magnitude() * Math<typename MyVector::Real>::Cos(u.AngleBetween(v)), u.DotProduct(v)); // u . v = ||u|| ||v|| cos o
    EXPECT_EQ(u.MagnitudeSqr(), u.DotProduct(u)); // u . u = ||u||^2
    EXPECT_EQ(v.DotProduct(u), u.DotProduct(v)); // u . v = v . u
    EXPECT_EQ(u.DotProduct(v) + u.DotProduct(w), u.DotProduct(v + w)); // u . (v + w) = u . v + u . w
    EXPECT_EQ(u.DotProduct(v) - u.DotProduct(w), u.DotProduct(v - w)); // u . (v - w) = u . v - u . w

    const TypeParam r = 3;
    const TypeParam s = -5;

    EXPECT_EQ(r * s * u.DotProduct(v), (r * u).DotProduct(s * v)); // ru . sv = rs(u . v)
}

TYPED_TEST(VectorTest, IdentitiesCross3) {
	using MyVector = Vector<3, TypeParam>;

    const MyVector u(1, 2, 3);
    const MyVector v(6, 6, 6);
    const MyVector w(-8, -8, -8);
    const MyVector x(10, -100, -50);

    EXPECT_EQ(-(v.CrossProduct(u)), u.CrossProduct(v)); // u x v = -(v x u)
    EXPECT_EQ(MyVector::ZERO, u.CrossProduct(u)); // u x u = 0
    EXPECT_EQ(MyVector::ZERO.CrossProduct(u), u.CrossProduct(MyVector::ZERO)); // u x 0 = 0 x u = 0
    EXPECT_EQ(MyVector::ZERO.CrossProduct(u), MyVector::ZERO); // u x 0 = 0 x u = 0
    EXPECT_EQ(v.DotProduct(u.CrossProduct(v)), u.DotProduct(u.CrossProduct(v))); // u . (u x v) = v . (u x v) = 0 (u x v is perpendicular to both u and v)
    EXPECT_EQ(0, v.DotProduct(u.CrossProduct(v))); // u . (u x v) = v . (u x v) = 0 (u x v is perpendicular to both u and v)
    EXPECT_EQ(u.CrossProduct(v).DotProduct(w), u.DotProduct(v.CrossProduct(w))); // u . (v x w) = (u x v) . w
    EXPECT_EQ(u.CrossProduct(v) + u.CrossProduct(w), u.CrossProduct(v + w)); // u x (v + w) = u x v + u x w
    EXPECT_EQ(u.CrossProduct(v) - u.CrossProduct(w), u.CrossProduct(v - w)); // u x (v - w) = u x v - u x w
    EXPECT_EQ(u.CrossProduct(w) + v.CrossProduct(w), (u + v).CrossProduct(w)); // (u + v) x w = u x w + v x w
    EXPECT_EQ(u.CrossProduct(w) - v.CrossProduct(w), (u - v).CrossProduct(w)); // (u - v) x w = u x w - v x w
    EXPECT_EQ(w.CrossProduct(v.CrossProduct(u)), u.CrossProduct(v).CrossProduct(w)); // (u x v) x w = w x (v x u) = (u . w)v - (v . w)u (a vector in the plane of u and v)
    EXPECT_EQ(u.DotProduct(w) * v - v.DotProduct(w) * u, w.CrossProduct(v.CrossProduct(u))); // (u x v) x w = w x (v x u) = (u . w)v - (v . w)u (a vector in the plane of u and v)
    EXPECT_EQ(w.CrossProduct(v).CrossProduct(u), u.CrossProduct(v.CrossProduct(w))); // u x (v x w) = (w x v) x u = (u . w)v - (u . v)w (a vector in the plane of v and w)
    EXPECT_EQ(u.CrossProduct(v.CrossProduct(w)), u.DotProduct(w) * v - u.DotProduct(v) * w); // u x (v x w) = (w x v) x u = (u . w)v - (u . v)w (a vector in the plane of v and w)
    EXPECT_NEAR(u.Magnitude() * v.Magnitude() * Math<typename MyVector::Real>::Sin(u.AngleBetween(v)), u.CrossProduct(v).Magnitude(), Math<typename MyVector::Real>::EPSILON * 100); // ||u x v|| = ||u| ||v|| sin o
    EXPECT_EQ(u.DotProduct(w) * v.DotProduct(x) - v.DotProduct(w) * u.DotProduct(x), u.CrossProduct(v).DotProduct(w.CrossProduct(x))); // (u x v) . (w x x) = (u . w)(v . x) - (v . w)(u . x) (Lagrange's identity)
    EXPECT_EQ(MyVector::ZERO, u.CrossProduct(v.CrossProduct(w)) + v.CrossProduct(w.CrossProduct(u)) + w.CrossProduct(u.CrossProduct(v))); // u x (v x w) + v x (w x u) + w x (u x v) = 0 (Jacobi's identity)

    const TypeParam r = 3;
    const TypeParam s = -5;

    EXPECT_EQ(r * s * u.CrossProduct(v), (r * u).CrossProduct(s * v)); // ru x sv = rs(u x v)
}

TYPED_TEST(VectorTest, IdentitiesScalarTripeProduct3) {
	using MyVector = Vector<3, TypeParam>;

    const MyVector u(1, 2, 3);
    const MyVector v(6, 6, 6);
    const MyVector z(-8, -8, -8);
    const MyVector x(10, -100, -50);
    const MyVector w(-5, 5, -22);
    const MyVector y(-1, -1, 1);

#define STP MyVector::ScalarTripleProduct

    EXPECT_EQ(-STP(w, v, u), STP(u, v, w)); // [uvw] = [vwu] = [wuv] = -[uwv] = -[vuw] = -[wvu]
    EXPECT_EQ(-STP(w, v, u), STP(v, w, u));
    EXPECT_EQ(-STP(w, v, u), STP(w, u, v));
    EXPECT_EQ(-STP(w, v, u), -STP(u, w, v));
    EXPECT_EQ(-STP(w, v, u), -STP(v, u, w));
    EXPECT_EQ(0, STP(v, u, v)); // [uuv] = [vuv] = 0
    EXPECT_EQ(0, STP(u, u, v));
    EXPECT_EQ(STP(u.CrossProduct(v), v.CrossProduct(w), w.CrossProduct(u)), Math<typename MyVector::Real>::Sqr(STP(u, v, w))); // [uvw]^2 = [(u x v)(v x w)(w x u)]
    EXPECT_EQ(MyVector::ZERO, u * STP(v, w, x) - v * STP(w, x, u) + w * STP(x, u, v) - x * STP(u, v, w)); // u[vwx] - v[wxu] + w[xuv] - x[uvw] = 0
    EXPECT_EQ(v * STP(u, w, x) - u * STP(v, w, x), u.CrossProduct(v).CrossProduct(w.CrossProduct(x))); // (u x v) x (w x x) = v[uwx] - u[vwx]
    EXPECT_EQ(STP(v, y, z) * STP(u, w, x) - STP(u, y, z) * STP(v, w, x), STP(u.CrossProduct(v), w.CrossProduct(x), y.CrossProduct(z))); // [(u x v)(w x x)(y x z)] = [vyz][uwx] - [uyz][vwx]
    EXPECT_EQ(2 * STP(u, v, w), STP(u + v, v + w, w + u)); // [(u+v)(v+w)(w+u)] = 2[uvw]
    EXPECT_EQ(STP(u - x, v, w) - STP(v - w, x, u), STP(u - x, v - x, w - x)); // [(u - x)(v - x)(w - x)] = [uvw] - [uv x] - [uxw] - [xvw] = [(u - x)vw] - [(v - w)xu]
    EXPECT_EQ(STP(u - x, v, w) - STP(v - w, x, u), STP(u, v, w) - STP(u, v, x) - STP(u, x, w) - STP(x, v, w));
#undef STP
}
