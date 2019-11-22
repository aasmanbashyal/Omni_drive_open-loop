/*
 * vec4.h
 * 
 * Created : 1/9/2018
 *  Author : n-is
 *   email : 073bex422.nischal@pcampus.edu.np
 */

#ifndef _VEC4_H_
#define _VEC4_H_

#include "vec4.h"

template <class T>
class Vec4
{
public:
        Vec4() { set_Values(0,0,0); }
        Vec4(T x, T y, T z, T w) { set_Values(x,y,z,w); }

        Vec4(Vec4 &&) = default;
        Vec4 &operator=(Vec4 &&) = default;
        ~Vec4() { }

        T getX() const { return x_; }
        T getY() const { return y_; }
        T getZ() const { return z_; }
        T getW() const { return w_; }
        void setX(T x) { x_ = x; }
        void setY(T y) { y_ = y; }
        void setZ(T z) { z_ = z; }
        void setW(T w) { w_ = w; }

        void set_Values(T x, T y, T z, T w) {
                setX(x);
                setY(y);
                setZ(z);
                setW(w);
        }


        Vec4 mult_EW(float num) {
                Vec4 temp(*this);
                temp.x_ *= num;
                temp.y_ *= num;
                temp.z_ *= num;
                temp.w_ *= num;

                return temp;
        }

        template <typename T1>
        Vec4 mult_EW(Vec4<T1> v) {
                Vec4 temp(v);
                temp.x_ *= x_;
                temp.y_ *= y_;
                temp.z_ *= z_;
                temp.w_ *= w_;

                return temp;
        }


        Vec4 add_EW(float num) {
                Vec4 temp(*this);
                temp.x_ += num;
                temp.y_ += num;
                temp.z_ += num;
                temp.w_ += num;

                return temp;
        }

        template <typename T1>
        Vec4 add_EW(Vec4<T1> v) {
                Vec4 temp(v);
                temp.x_ += x_;
                temp.y_ += y_;
                temp.z_ += z_;
                temp.w_ += w_;

                return temp;
        }


        Vec4 sub_EW(float num) {
                Vec4 temp(*this);
                temp.x_ -= num;
                temp.y_ -= num;
                temp.z_ -= num;
                temp.w_ -= num;

                return temp;
        }

        template <typename T1>
        Vec4 sub_EW(Vec4<T1> v) {
                Vec4 temp(v);
                temp.x_ -= x_;
                temp.y_ -= y_;
                temp.z_ -= z_;
                temp.w_ -= w_;

                return temp;
        }


        Vec4 div_EW(float num) {
                Vec4 temp(*this);
                temp.x_ /= (float)num;
                temp.y_ /= (float)num;
                temp.z_ /= (float)num;
                temp.w_ /= (float)num;

                return temp;
        }

        template <typename T1>
        Vec4 div_EW(Vec4<T1> v) {
                Vec4 temp(*this);
                temp.x_ /= (float)v.x_;
                temp.y_ /= (float)v.y_;
                temp.z_ /= (float)v.z_;
                temp.w_ /= (float)v.w_;

                return temp;
        }

        
        Vec4(const Vec4 &v) {
                x_ = v.x_;
                y_ = v.y_;
                z_ = v.z_;
                w_ = v.w_;
        }
        
        Vec4 &operator=(const Vec4 &v) {
                Vec4 temp(v);
                swap(*this, temp);

                return *this;
        }

        Vec4 &operator+=(const Vec4 &rhs) {
                x_ += rhs.x_;
                y_ += rhs.y_;
                z_ += rhs.z_;
                w_ += rhs.w_;

                return *this;
        }
        
        Vec4 &operator-=(const Vec4 &rhs) {
                x_ -= rhs.x_;
                y_ -= rhs.y_;
                z_ -= rhs.z_;
                z_ -= rhs.w_;

                return *this;
        }

        friend Vec4 operator+(Vec4 lhs, const Vec4 &rhs) {
                lhs += rhs;
                return lhs;
        }

        friend Vec4 operator-(Vec4 lhs, const Vec4 &rhs) {
                lhs -= rhs;
                return lhs;
        }

        void print() const {
                printf("%ld, %ld, %ld", (int32_t)x_, (int32_t)y_, (int32_t)z_);
        }

private:
        T x_,y_,z_,w_;

        friend void swap(Vec4 &first, Vec4 &second) {
                swap_Element(first.x_, second.x_);
                swap_Element(first.y_, second.y_);
                swap_Element(first.z_, second.z_);
                swap_Element(first.w_, second.w_);
        }
};

#endif // !_VEC4_H_
