/*
 * mat.h
 * 
 * Created : 12/31/2018
 *  Author : n-is
 *   email : 073bex422.nischal@pcampus.edu.np
 */

#ifndef _MAT_H_
#define _MAT_H_

#include <math.h>
#include "vec3.h"

#define MAX_MATRIX_ROWS         (6)
#define MAX_MATRIX_COLS         (6)

class Mat
{
public:
        Mat() : Mat(0,0) { }
        
        template <size_t M, size_t N>
        Mat(const float (&mat)[M][N]) : Mat(M,N){
                fill(mat);
        }

        Mat(uint8_t rows, uint8_t columns);
        Mat(Mat &&) = default;
        Mat &operator=(Mat &&) = default;
        ~Mat() { }

        uint8_t rows() const { return rows_; }
        uint8_t cols() const { return cols_; }

        inline float &at(uint8_t i, uint8_t j) {
                if (!(i < rows_ && j < cols_)) {
                        _Error_Handler(__FILE__, __LINE__);
                }
                return matrix_[i][j];
        }


        Mat(const Mat &m);

        Mat &operator=(const Mat &m) {
                Mat temp(m);
                swap(*this, temp);

                return *this;
        }

        Mat &operator+=(const Mat &rhs);
        Mat &operator-=(const Mat &rhs);
        Mat &operator*=(const Mat &rhs);
        Mat &operator*=(const Vec3<float> &rhs);

        friend Mat operator+(Mat lhs, const Mat &rhs) {
                lhs += rhs;
                return lhs;
        }

        friend Mat operator-(Mat lhs, const Mat &rhs) {
                lhs -= rhs;
                return lhs;
        }

        friend Mat operator*(Mat lhs, const Mat &rhs) {
                lhs *= rhs;
                return lhs;
        }

        friend Mat operator*(Mat lhs, const Vec3<float> &rhs) {
                lhs *= rhs;
                return lhs;
        }

        Mat mult(const Mat &m);
        Mat mult_EW(float num);
        Mat transpose();

        // Just an alias for getting transpose of a matrix
        inline Mat trans() { return transpose(); }

        void fill(float num) {
                for (uint8_t i = 0; i < rows_; ++i) {
                        for (uint8_t j = 0; j < cols_; ++j) {
                                matrix_[i][j] = num;
                        }
                }
        }

        template <size_t M, size_t N>
        void fill(const float (&mat)[M][N]) {
                if (M != rows_ && N != cols_) {
                        _Error_Handler(__FILE__, __LINE__);
                }
                for (uint8_t i = 0; i < M; ++i) {
                        for (uint8_t j = 0; j < N; ++j) {
                                matrix_[i][j] = mat[i][j];
                        }
                }
        }

        void add_Rows(uint8_t r) {
                if (r + rows_ <= MAX_MATRIX_ROWS) {
                        rows_ += r;
                }
        }

        void add_Cols(uint8_t c) {
                if (c + cols_ <= MAX_MATRIX_COLS) {
                        cols_ += c;
                }
        }

        static Mat eye(uint8_t n);

        bool is_Zero() const;
        void swap_Rows(uint8_t a, uint8_t b);
        void swap_Cols(size_t a, size_t b);        
        bool inv(Mat &inv) const;

        Mat inv() const
        {
                Mat i(rows_, cols_);
                if(inv(i)) {
                        return i;
                }

                i.fill(0);
                return i;
        }

        void print() const {
                for (uint8_t i = 0; i < rows_; ++i) {
                        for (uint8_t j = 0; j < cols_; ++j) {
                                printf("%ld\t", (int32_t)matrix_[i][j]);
                        }
                        printf("\n");
                }
        }

private:
        float matrix_[MAX_MATRIX_ROWS][MAX_MATRIX_COLS];
        uint8_t rows_, cols_;
        
        friend void swap(Mat &first, Mat &second);
};

Mat solve(Mat A, Mat B);


#endif // !_MAT_H_
