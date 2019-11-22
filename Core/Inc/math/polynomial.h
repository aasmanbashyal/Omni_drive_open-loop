/*
 * polynomial.h
 *
 * Created : 24/2/2019
 *  Author : n-is
 *   email : 073bex422.nischal@pcampus.edu.np
 */

#ifndef _POLYNOMIAL_H_
#define _POLYNOMIAL_H_

template <size_t N>
float polyval(float (&poly)[N], float indep)
{
        float val = 0;
        float last_indep = 1;

        for (size_t i = 0; i < N; ++i) {
                val += poly[i] * last_indep;
                last_indep *= indep;
        }

        return val;
}

#endif // !_POLYNOMIAL_H_
