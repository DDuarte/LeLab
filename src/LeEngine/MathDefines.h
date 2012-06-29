#ifndef MATHDEFINES_H
#define MATHDEFINES_H

#include <boost/math/constants/constants.hpp>
#include <boost/math/special_functions/fpclassify.hpp>
#include <limits>

const float PI = boost::math::constants::pi<float>();

//! Convert degrees to radians
inline float DegToRad(float degrees) { return degrees * (PI / 180.0f); }
//! Convert radians to degrees
inline float RadToDeg(float radians) { return radians * (180.0f / PI); }

//! Absolute value
template <typename T>
inline T Abs(T val) { return val > 0 ? val : -val; }

//! True if value is zero (within an epsilon)
template <typename T>
inline bool IsZero(T val, T epsilon = std::numeric_limits<T>::epsilon()) { return !val || (Abs(val) <= epsilon); }

//! True if value is not a number (useful for floats and doubles)
template <typename T>
inline bool IsNaN(T val)  { return boost::math::fpclassify(val) == FP_NAN; }

//! True if value represents infinity (useful for floats and doubles)
template <typename T>
inline bool IsInfinite(T val) { return boost::math::fpclassify(val) == FP_INFINITE; }

//! Returns the square of a number
template <typename T>
inline T Sqr(T val) { return val * val; }

//! Limits a number between min and max
template <typename T>
inline T Clamp(T val, T min, T max) { return (val < min ? min : (val > max ? max : val)); }

#endif // MATHDEFINES_H
