/*
 * vec2.h
 * 
 * Created : 1/9/2018
 *  Author : n-is
 *   email : 073bex422.nischal@pcampus.edu.np
 */

#ifndef _VEC2_H_
#define _VEC2_H_

#include "vec3.h"
#include <math.h>

template <class T>
class Vec2
{
public:
        Vec2() { set_Values(0,0); }
        Vec2(T x, T y) { set_Values(x,y); }

        Vec2(Vec3<T> v) { set_Values(v.getX(), v.getY()) ;}

        Vec2(Vec2 &&) = default;
        Vec2 &operator=(Vec2 &&) = default;
        ~Vec2() { }

        T getX() const { return x_; }
        T getY() const { return y_; }
        void setX(T x) { x_ = x; }
        void setY(T y) { y_ = y; }

        void set_Values(T x, T y) {
                setX(x);
                setY(y);
        }


        Vec2 mult_EW(float num) {
                Vec2 temp(*this);
                temp.x_ *= num;
                temp.y_ *= num;

                return temp;
        }

        template <typename T1>
        Vec2 mult_EW(Vec2<T1> v) {
                Vec2 temp(v);
                temp.x_ *= x_;
                temp.y_ *= y_;

                return temp;
        }


        Vec2 add_EW(float num) {
                Vec2 temp(*this);
                temp.x_ += num;
                temp.y_ += num;

                return temp;
        }

        template <typename T1>
        Vec2 add_EW(Vec2<T1> v) {
                Vec2 temp(v);
                temp.x_ += x_;
                temp.y_ += y_;

                return temp;
        }


        Vec2 sub_EW(float num) {
                Vec2 temp(*this);
                temp.x_ -= num;
                temp.y_ -= num;

                return temp;
        }

        template <typename T1>
        Vec2 sub_EW(Vec2<T1> v) {
                Vec2 temp(v);
                temp.x_ -= x_;
                temp.y_ -= y_;

                return temp;
        }


        Vec2 div_EW(float num) {
                Vec2 temp(*this);
                temp.x_ /= (float)num;
                temp.y_ /= (float)num;

                return temp;
        }

        template <typename T1>
        Vec2 div_EW(Vec2<T1> v) {
                Vec2 temp(*this);
                temp.x_ /= (float)v.x_;
                temp.y_ /= (float)v.y_;

                return temp;
        }

        
        Vec2(const Vec2 &v) {
                x_ = v.x_;
                y_ = v.y_;
        }
        
        Vec2 &operator=(const Vec2 &v) {
                Vec2 temp(v);
                swap(*this, temp);

                return *this;
        }

        Vec2 &operator+=(const Vec2 &rhs) {
                x_ += rhs.x_;
                y_ += rhs.y_;

                return *this;
        }
        
        Vec2 &operator-=(const Vec2 &rhs) {
                x_ -= rhs.x_;
                y_ -= rhs.y_;

                return *this;
        }

        friend Vec2 operator+(Vec2 lhs, const Vec2 &rhs) {
                lhs += rhs;
                return lhs;
        }

        friend Vec2 operator-(Vec2 lhs, const Vec2 &rhs) {
                lhs -= rhs;
                return lhs;
        }

        Vec2 polar() {
                float r = sqrtf(x_*x_ + y_*y_);
                float theta = atan2f(y_, x_);
                Vec2<float> pol(r, theta);
                return pol;
        }

        void print() const {
                printf("%ld, %ld", (int32_t)x_, (int32_t)y_);
        }

private:
        T x_,y_;

        friend void swap(Vec2 &first, Vec2 &second) {
                swap_Element(first.x_, second.x_);
                swap_Element(first.y_, second.y_);
        }
};

#endif // !_VEC2_H_
