/*
 * calculus.h
 *
 * Created : 23/2/2019
 *  Author : n-is
 *   email : 073bex422.nischal@pcampus.edu.np
 */

#ifndef _CALCULUS_H_
#define _CALCULUS_H_

template <size_t N>
void polyder(float (&der)[N-1], const float (&poly)[N])
{
        for (size_t i = 1; i < N; ++i) {
                der[i-1] = poly[i]*i;
        }
}

#endif // !_CALCULUS_H_
