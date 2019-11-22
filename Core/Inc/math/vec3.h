/*
 * vec3.h
 * 
 * Created : 11/9/2018
 *  Author : n-is
 *   email : 073bex422.nischal@pcampus.edu.np
 */

#ifndef _VEC3_H_
#define _VEC3_H_

#include "stm32f4xx_hal.h"
#include "main.h"

template <typename T>
void swap_Element(T &first, T &second)
{
        T temp = first;
        first = second;
        second = temp;
}

template <class T>
class Vec3
{
public:
        Vec3() { set_Values(0,0,0); }
        Vec3(T x, T y, T z) { set_Values(x,y,z); }

        Vec3(Vec3 &&) = default;
        Vec3 &operator=(Vec3 &&) = default;
        ~Vec3() { }

        T getX() const { return x_; }
        T getY() const { return y_; }
        T getZ() const { return z_; }
        void setX(T x) { x_ = x; }
        void setY(T y) { y_ = y; }
        void setZ(T z) { z_ = z; }

        void set_Values(T x, T y, T z) {
                setX(x);
                setY(y);
                setZ(z);
        }


        Vec3 mult_EW(float num) {
                Vec3 temp(*this);
                temp.x_ *= num;
                temp.y_ *= num;
                temp.z_ *= num;

                return temp;
        }

        template <typename T1>
        Vec3 mult_EW(Vec3<T1> v) {
                Vec3 temp(v);
                temp.x_ *= x_;
                temp.y_ *= y_;
                temp.z_ *= z_;

                return temp;
        }


        Vec3 add_EW(float num) {
                Vec3 temp(*this);
                temp.x_ += num;
                temp.y_ += num;
                temp.z_ += num;

                return temp;
        }

        template <typename T1>
        Vec3 add_EW(Vec3<T1> v) {
                Vec3 temp(v);
                temp.x_ += x_;
                temp.y_ += y_;
                temp.z_ += z_;

                return temp;
        }


        Vec3 sub_EW(float num) {
                Vec3 temp(*this);
                temp.x_ -= num;
                temp.y_ -= num;
                temp.z_ -= num;

                return temp;
        }

        template <typename T1>
        Vec3 sub_EW(Vec3<T1> v) {
                Vec3 temp(v);
                temp.x_ -= x_;
                temp.y_ -= y_;
                temp.z_ -= z_;

                return temp;
        }


        Vec3 div_EW(float num) {
                Vec3 temp(*this);
                temp.x_ /= (float)num;
                temp.y_ /= (float)num;
                temp.z_ /= (float)num;

                return temp;
        }

        template <typename T1>
        Vec3 div_EW(Vec3<T1> v) {
                Vec3 temp(*this);
                temp.x_ /= (float)v.x_;
                temp.y_ /= (float)v.y_;
                temp.z_ /= (float)v.z_;

                return temp;
        }

        
        Vec3(const Vec3 &v) {
                x_ = v.x_;
                y_ = v.y_;
                z_ = v.z_;
        }
        
        Vec3 &operator=(const Vec3 &v) {
                Vec3 temp(v);
                swap(*this, temp);

                return *this;
        }

        Vec3 &operator+=(const Vec3 &rhs) {
                x_ += rhs.x_;
                y_ += rhs.y_;
                z_ += rhs.z_;

                return *this;
        }
        
        Vec3 &operator-=(const Vec3 &rhs) {
                x_ -= rhs.x_;
                y_ -= rhs.y_;
                z_ -= rhs.z_;

                return *this;
        }

        // @return true if all the elements is less than tolerance value else false
        bool is_AbsLess(T tol) {
                if (abs(x_) <= tol && abs(y_) <= tol && abs(z_) <= tol) {
                        return true;
                }
                return false;
        }

        friend Vec3 operator+(Vec3 lhs, const Vec3 &rhs) {
                lhs += rhs;
                return lhs;
        }

        friend Vec3 operator-(Vec3 lhs, const Vec3 &rhs) {
                lhs -= rhs;
                return lhs;
        }

        void print() const {
                printf("%ld, %ld, %ld", (int32_t)x_, (int32_t)y_, (int32_t)z_);
        }

private:
        T x_,y_,z_;

        friend void swap(Vec3 &first, Vec3 &second) {
                swap_Element(first.x_, second.x_);
                swap_Element(first.y_, second.y_);
                swap_Element(first.z_, second.z_);
        }
};

#endif // !_VEC3_H_
