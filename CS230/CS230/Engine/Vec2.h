/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Vec2.h
Author: Jinseok Son
Creation date: 2022-03-10
-----------------------------------------------------------------*/
#pragma once
#include <cmath>
#include <limits>
#include "Vec2.h"





namespace math
{
	struct vec2;
    struct ivec2;
	[[nodiscard]] constexpr double abs(double d) noexcept { return (d < 0.0) ? -d : d; }

    [[nodiscard]] constexpr bool is_equal(double d1, double d2) noexcept
    {
        return abs(d1 - d2) <= std::numeric_limits<double>::epsilon() * abs(d1 + d2);
    }

    [[nodiscard]] constexpr bool is_equal(int i1, int i2) noexcept { return i1 == i2; }

    
    [[nodiscard]]constexpr vec2 operator+(const vec2& left, const vec2& right) noexcept;
    [[nodiscard]]constexpr vec2 operator-(const vec2& left, const vec2& right) noexcept;
    [[nodiscard]]constexpr vec2 operator*(const vec2& left, const double value) noexcept;
    [[nodiscard]] constexpr vec2 operator*(const double value, const vec2& right) noexcept;
    [[nodiscard]] constexpr vec2 operator/(const vec2& left, double value) noexcept;
    [[nodiscard]] constexpr bool operator==(const vec2& left, const vec2& right) noexcept;
    [[nodiscard]] constexpr bool operator!=(const vec2& left, const vec2& right) noexcept;
   
    struct[[nodiscard]]  vec2
    {
             
    	constexpr  vec2(double x_value, double y_value) noexcept : x(x_value), y(y_value)  {}
        constexpr  vec2(double value)  noexcept: vec2(value, value) {}  //delegating constructor
        constexpr  vec2() noexcept = default; //default constructor
       
    	double x=0;
        double y=0;
        constexpr vec2& operator+=(const vec2& right) noexcept;
        constexpr vec2& operator-=(const vec2& right) noexcept;
        constexpr vec2 operator-() const noexcept;
        constexpr vec2& operator*=(const double value) noexcept;
    	constexpr vec2& operator/=(const double value) noexcept;
    	[[nodiscard]]constexpr double LengthSquared() const noexcept;
    	vec2& Normalize()  noexcept;
      
            
     

    };


    [[nodiscard]] constexpr ivec2 operator+(const ivec2& left, const ivec2& right) noexcept;
    [[nodiscard]] constexpr ivec2 operator-(const ivec2& left, const ivec2& right) noexcept;
    [[nodiscard]] constexpr ivec2 operator*(const ivec2& left, double value) noexcept;
    [[nodiscard]] constexpr ivec2 operator*(double value, const ivec2& right) noexcept;
    [[nodiscard]] constexpr ivec2 operator/(const ivec2& left, double value) noexcept;
    [[nodiscard]] constexpr bool operator==(const ivec2& left, const ivec2& right) noexcept;
    [[nodiscard]] constexpr bool operator!=(const ivec2& left, const ivec2& right) noexcept;


    struct [[nodiscard]] ivec2
    {
        constexpr  ivec2(int x_value, int y_value) noexcept : x(x_value), y(y_value) {}
        constexpr  ivec2(int value)  noexcept : ivec2(value, value) {}  //delegating constructor
        constexpr  ivec2() noexcept = default; //default constructor

        int x = 0;
        int y = 0;

        constexpr ivec2& operator+=(const ivec2& right) noexcept;
    	constexpr ivec2& operator-=(const ivec2& right) noexcept;
    	constexpr ivec2 operator-() const noexcept;
    	constexpr ivec2& operator*=(const double value) noexcept;
        constexpr ivec2& operator/=(const double value) noexcept;
    	[[nodiscard]] constexpr int LengthSquared() const noexcept;
        

        inline ivec2& Normalize()  noexcept;
    	constexpr operator vec2() noexcept;
         
         
    };
 
    


}
#include "Vec2.inl"

