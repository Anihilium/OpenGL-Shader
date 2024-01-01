#pragma once
#include <cmath>

namespace Core::Maths
{
    class Vec2
    {
    public:
        union
        {
            struct
            {
                float x;
                float y;
            };
            struct
            {
                float min;
                float max;
            };
        };

        Vec2(const float x = 0.f, const float y = 0.f);
        Vec2(const Vec2& copy);

        float DotProduct(const Vec2& Vec2) const;
        float Magnitude() const;
        float CrossProduct(const Vec2& Vec2) const;
        Vec2& Normalize();

        friend Vec2 operator+(const Vec2& left, const Vec2& right);
        friend Vec2 operator-(const Vec2& left, const Vec2& right);
        friend Vec2 operator*(const Vec2& left, const float multiplier);
        friend Vec2 operator/(const Vec2& left, const float divider);

        friend Vec2& operator+=(Vec2& left, const Vec2& right);
        friend Vec2& operator-=(Vec2& left, const Vec2& right);
        friend Vec2& operator*=(Vec2& left, const float multipler);
        friend Vec2& operator/=(Vec2& left, const float divider);

        friend bool operator==(const Vec2& left, const Vec2& right);
        friend bool operator!=(const Vec2& left, const Vec2& right);

        friend bool operator<(const Vec2& left, const Vec2& right);
        friend bool operator<=(const Vec2& left, const Vec2& right);
        friend bool operator>(const Vec2& left, const Vec2& right);
        friend bool operator>=(const Vec2& left, const Vec2& right);
    };
    // Friends Vec4
    Vec2 operator+(const Vec2& left, const Vec2& right);
    Vec2 operator-(const Vec2& left, const Vec2& right);
    Vec2 operator*(const Vec2& Vec2, const float multiplier);
    Vec2 operator/(const Vec2& left, const float divider);

    Vec2& operator+=(Vec2& left, const Vec2& right);
    Vec2& operator-=(Vec2& left, const Vec2& right);
    Vec2& operator*=(Vec2& left, const float multipler);
    Vec2& operator/=(Vec2& left, const float divider);

    bool operator==(const Vec2& left, const Vec2& right);
    bool operator!=(const Vec2& left, const Vec2& right);

    bool operator<(const Vec2& left, const Vec2& right);
    bool operator<=(const Vec2& left, const Vec2& right);
    bool operator>(const Vec2& left, const Vec2& right);
    bool operator>=(const Vec2& left, const Vec2& right);
}