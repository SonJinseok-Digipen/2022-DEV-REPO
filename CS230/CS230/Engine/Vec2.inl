/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Vec2.inl
Author: Jinseok Son
Creation date: 2022-03-10
-----------------------------------------------------------------*/
#include"Vec2.h"
namespace math
{
    [[nodiscard]]constexpr vec2 operator+(const vec2& left, const vec2& right) noexcept
    {
        const double new_x = left.x + right.x;
    	const double new_y = left.y + right.y;
    	return vec2{ new_x,new_y };
    }
    constexpr vec2& vec2::operator+=(const vec2& right) noexcept
    {
        *this = *this + right;
        return *this;
       
    }
    [[nodiscard]]constexpr vec2 operator-(const vec2& left, const vec2& right) noexcept
    {
        const double new_x = left.x - right.x;
        const double new_y = left.y - right.y;
        return vec2{ new_x,new_y };
    }
    constexpr vec2& vec2::operator-=(const vec2& right) noexcept
    {
        *this = *this - right;
        return *this;
    }
    [[nodiscard]] constexpr vec2 vec2:: operator-() const noexcept
    {
        const double new_x = x * -1;
        const double new_y = y * -1;
        return vec2{ new_x,new_y };
    }
    
    [[nodiscard]]constexpr vec2 operator*(const vec2& left, const double value) noexcept
    {
        const double new_x = left.x*value;
        const double new_y = left.y*value;
        return vec2{ new_x,new_y };
    }
    [[nodiscard]] constexpr vec2 operator*(double value, const vec2& right) noexcept
    {
        const double new_x =  value*right.x;
        const double new_y =  value*right.y;
        return vec2{ new_x,new_y };
    }
    constexpr vec2& vec2::operator*=(const double value) noexcept
    {
        *this = *this * value;
        return *this;
    }
	[[nodiscard]] constexpr vec2 operator/(const vec2& left, const double value) noexcept
    {
        const double new_x = left.x/value;
        const double new_y = left.y/value;
        return vec2{ new_x,new_y };
    }
    constexpr vec2& vec2::operator/=(const double value) noexcept
    {
        *this = *this / value;
        return *this;
    }
    [[nodiscard]] constexpr double vec2::LengthSquared() const noexcept
    {
        const double length = (x * x) + (y * y);
        return length;
    }
    [[nodiscard]] constexpr bool operator==(const vec2& left, const vec2& right) noexcept
    {
        const bool IsXequal = is_equal(left.x, right.x);
        const bool IsYequal = is_equal(left.y, right.y);
        return (IsXequal==true && IsYequal==true);
    }
    [[nodiscard]] constexpr bool operator!=(const vec2& left, const vec2& right) noexcept
    {
        const bool IsXequal = is_equal(left.x, right.x);
        const bool IsYequal = is_equal(left.y, right.y);
        return (IsXequal==false ||  IsYequal==false);
    }
     inline vec2& vec2::Normalize()  noexcept
    {
        double length = sqrt(this->LengthSquared());

        return *this /= length;

    }

    /*---------------------------------------------------------------------*/

    [[nodiscard]] constexpr ivec2 operator+(const ivec2& left, const ivec2& right) noexcept
    {
        const int new_x = left.x + right.x;
        const int new_y = left.y + right.y;
        return ivec2{ new_x,new_y };
    }
    constexpr ivec2& ivec2::operator+=(const ivec2& right) noexcept
    {
        *this = *this + right;
        return *this;
    }
    [[nodiscard]] constexpr ivec2 operator-(const ivec2& left, const ivec2& right) noexcept
    {
        const int new_x = left.x - right.x;
        const int new_y = left.y - right.y;
        return ivec2{ new_x,new_y };
    }
	constexpr ivec2& ivec2::operator-=(const ivec2& right) noexcept
    {
        *this = *this - right;
        return *this;
    }
    [[nodiscard]] constexpr ivec2 ivec2::operator-() const noexcept
    {
        const int new_x = x * -1;
        const int new_y = y * -1;
        return ivec2{ new_x,new_y };
    }

   
    [[nodiscard]] constexpr ivec2 operator*(const ivec2& left, const double value) noexcept
    {
        const int new_x = static_cast<int>(left.x * value);
        const int new_y = static_cast<int>(left.y * value);
        return ivec2{ new_x,new_y };
    }
    [[nodiscard]] constexpr ivec2 operator*(const double value, const ivec2& right) noexcept
    {
        return right * value;
    }
    constexpr ivec2& ivec2::operator*=(const double value) noexcept
    {
        *this = *this * value;
        return *this;

    }
    [[nodiscard]] constexpr ivec2 operator/(const ivec2& left, const double value) noexcept
    {
        const int new_x = static_cast<int>(left.x / value);
        const int new_y = static_cast<int>(left.y / value);
        return ivec2{ new_x,new_y };
    }
    constexpr ivec2& ivec2::operator/=(const double value) noexcept
    {
        *this = *this / value;
        return *this;
    }
    [[nodiscard]] constexpr bool operator==(const ivec2& left, const ivec2& right) noexcept
    {
        const bool IsXequal = is_equal(left.x, right.x);
        const bool IsYequal = is_equal(left.y, right.y);
        return IsXequal && IsYequal;
    }
    [[nodiscard]] constexpr bool operator!=(const ivec2& left, const ivec2& right) noexcept
    {
        const bool IsXequal = is_equal(left.x, right.x);
        const bool IsYequal = is_equal(left.y, right.y);
        return IsXequal == false || IsYequal == false;
    }
    [[nodiscard]] constexpr int ivec2::LengthSquared() const noexcept
    {
        const int length = (x * x) + (y * y);
        return length;
    }
   inline ivec2& ivec2::Normalize()  noexcept
    {
        double length = sqrt(this->LengthSquared());

        return *this /= length;
    }
    [[nodiscard]] constexpr ivec2::operator vec2() noexcept
    {
        return vec2{ static_cast<double>(x),static_cast<double>(y) };
    }
}
