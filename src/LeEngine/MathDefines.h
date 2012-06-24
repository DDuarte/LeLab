#ifndef MATHDEFINES_H
#define MATHDEFINES_H

#include <boost/math/constants/constants.hpp>

const double PI = boost::math::constants::pi<double>();

inline float DegToRad(float degrees) { return degrees * (PI / 180.0f); }
inline float RadToDeg(float radians) { return radians * (180.0f / PI); }

#endif // MATHDEFINES_H
