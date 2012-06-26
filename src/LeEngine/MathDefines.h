#ifndef MATHDEFINES_H
#define MATHDEFINES_H

#include <boost/math/constants/constants.hpp>
#include <boost/math/special_functions/fpclassify.hpp>
#include <limits>

const float PI = boost::math::constants::pi<float>();

inline float DegToRad(float degrees) { return degrees * (PI / 180.0f); }
inline float RadToDeg(float radians) { return radians * (180.0f / PI); }

template <typename T>
inline T Abs(T val) { return val > 0 ? val : -val; }

template <typename T>
inline bool IsZero(T val, T epsilon = std::numeric_limits<T>::epsilon()) { return Abs(val) <= epsilon; }

template <typename T>
inline bool IsNaN(T val)  { return boost::math::fpclassify(val) == FP_NAN; }

template <typename T>
inline bool IsInfinite(T val) { return boost::math::fpclassify(val) == FP_INFINITE; }

template <typename T>
inline T Sqr(T val) { return val * val; }

#endif // MATHDEFINES_H
