#ifndef MATHEXT_H
#define MATHEXT_H

#include "Defines.h"
#include <boost/math/constants/constants.hpp>

const double PI = boost::math::constants::pi<double>();

inline float DegToRad(float degrees)
{
    return (float)(degrees * (PI / 180.0f));
}

#endif // MATHEXT_H