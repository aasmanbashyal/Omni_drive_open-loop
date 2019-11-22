/*
 * interpolation.h
 *
 * Created : 4/14/2019
 *  Author : n-is
 *   email : 073bex422.nischal@pcampus.edu.np
 */

#ifndef _INTERPOLATION_H_
#define _INTERPOLATION_H_

#include "vec3.h"

float lerp(float x, float y, float t);
float cubic_herp(float x, float y, float t);

Vec3<float> lerp(Vec3<float> x, Vec3<float> y, float t);
Vec3<float> cubic_herp(Vec3<float> x, Vec3<float> y, float t);

#endif //! _INTERPOLATION_H_
