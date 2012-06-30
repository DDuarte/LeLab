#ifndef DMATH_H
#define DMATH_H

// Kitties are murdered if you rename this file to "Math.h"

#include <cmath>
#include <boost/static_assert.hpp>
#include <boost/math/constants/constants.hpp>
#include <boost/type_traits.hpp>
#include <limits>

template <class Real>
class Math
{
public:
    // Constants
    static const Real EPSILON;
    static const Real PI;
    static const Real TWO_PI;
    static const Real HALF_PI;
    static const Real INV_PI;
    static const Real PI_OVER_180; // degrees to radians
    static const Real INV_PI_OVER_180; // radians to degrees
    static const Real SQRT_PI;
    static const Real SQR_PI;
    static const Real E;

    // Trigonometric
    static Real Cos(Real val) { return cos(val); }
    static Real Sin(Real val) { return sin(val); }
    static Real Tan(Real val) { return tan(val); }
    static Real ACos(Real val) { return acos(val); }
    static Real ASin(Real val) { return asin(val); }
   
    // Hyperbolic
    static Real Sinh(Real val) { return sinh(val); }
    static Real Cosh(Real val) { return cosh(val); }
    static Real Tanh(Real val) { return tanh(val); }

    // Exponential and logarithmic
    static Real Exp(Real val) { return exp(val); }
    static Real Log(Real val) { return log(val); }
    static Real Log10(Real val) { return log10(val); }
    static Real ModF(Real val, Real* intPart) { return modf(val, intPart); }

    // Power
    static Real Pow(Real base, int exponent) { return pow(base, exponent); }
    static Real Powr(Real base, Real exponent) { return pow(base, exponent); }
    static Real Sqrt(Real val) { return sqrt(val); }
    static Real InvSqrt(Real val) { return 1/Sqrt(val); }
    static Real Sqr(Real val) { return val*val; }

    // Misc
    static Real Ceil(Real val) { return ceil(val); }
    static Real Floor(Real val) { return floor(val); }
    static Real Abs(Real val) { return abs(val); }
    static Real FMod(Real numerator, Real denominator) { return fmod(numerator, denominator); }
    static Real Clamp(Real val, Real min, Real max) { return (val < min ? min : (val > max ? max : val)); }
    static int Sign(Real val) { return (val > 0 ? 1 : (val < 0 ? -1 : 0)); }

private:
    BOOST_STATIC_ASSERT_MSG(boost::is_floating_point<Real>::value, "Math class requires real type.");
};

template<class Real> const Real Math<Real>::EPSILON      = std::numeric_limits<Real>::epsilon();
template<class Real> const Real Math<Real>::PI           = boost::math::constants::pi<Real>();
template<class Real> const Real Math<Real>::TWO_PI       = boost::math::constants::two_pi<Real>();
template<class Real> const Real Math<Real>::HALF_PI      = (Real)(PI/2.0);
template<class Real> const Real Math<Real>::INV_PI       = (Real)(1.0/PI);
template<class Real> const Real Math<Real>::PI_OVER_180  = (Real)(PI/180.0);
template<class Real> const Real Math<Real>::INV_PI_OVER_180 = (Real)(1.0/PI_OVER_180);
template<class Real> const Real Math<Real>::SQRT_PI      = boost::math::constants::root_pi<Real>();
template<class Real> const Real Math<Real>::SQR_PI       = (Real)(PI*PI);
template<class Real> const Real Math<Real>::E            = boost::math::constants::e<Real>();

typedef Math<float> Mathf;
typedef Math<double> Mathd;

#endif // DMATH_H
