#pragma once

#include <cmath>

#ifndef M_PI
  #define M_PI  3.141592653589793238462643383279502884 /* pi */
#endif

namespace labyrinth::misc
{
  inline int xy_to_angle(float x, float y)
    { return ((atan2(x, y) * M_PI) / (2.f * M_PI)) * 360.f; }
}
