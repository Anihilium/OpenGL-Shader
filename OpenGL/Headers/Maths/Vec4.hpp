#pragma once
#include <cmath>
#include <Maths/Vec3.hpp>

namespace Core::Maths
{
    class Vec4
    {
    public:
        union
        {
            struct
            {
                float x;
                float y;
                float z;
                float w;
            };
            struct
            {
                float centerX;
                float centerY;
                float centerZ;
                float radius;
            };
        };

        Vec4(const float x = 0.f, const float y = 0.f, const float z = 0.f, const float w = 0.f);
        Vec4(const Vec3 v3, const float w = 0.f);
        Vec4(const Vec4& copy);

        float DotProduct(const Vec4& Vec4) const;
        float Magnitude();
        float CrossProduct(const Vec4& Vec4) const;
        Vec4& Normalize();
        void Homogenize();

        Vec3 toVec3();

        friend Vec4 operator+(const Vec4& left, const Vec4& right);
        friend Vec4 operator-(const Vec4& left, const Vec4& right);
        friend Vec4 operator*(const Vec4& left, const float multiplier);
        friend Vec4 operator/(const Vec4& left, const float divider);

        friend Vec4& operator+=(Vec4& left, const Vec4& right);
        friend Vec4& operator-=(Vec4& left, const Vec4& right);
        friend Vec4& operator*=(Vec4& left, const float multipler);
        friend Vec4& operator/=(Vec4& left, const float divider);

        friend bool operator==(const Vec4& left, const Vec4& right);
        friend bool operator!=(const Vec4& left, const Vec4& right);

        friend bool operator<(const Vec4& left, const Vec4& right);
        friend bool operator<=(const Vec4& left, const Vec4& right);
        friend bool operator>(const Vec4& left, const Vec4& right);
        friend bool operator>=(const Vec4& left, const Vec4& right);
    };
    // Friends Vec4
    Vec4 operator+(const Vec4& left, const Vec4& right);
    Vec4 operator-(const Vec4& left, const Vec4& right);
    Vec4 operator*(const Vec4& Vec4, const float multiplier);
    Vec4 operator/(const Vec4& left, const float divider);

    Vec4& operator+=(Vec4& left, const Vec4& right);
    Vec4& operator-=(Vec4& left, const Vec4& right);
    Vec4& operator*=(Vec4& left, const float multipler);
    Vec4& operator/=(Vec4& left, const float divider);

    bool operator==(const Vec4& left, const Vec4& right);
    bool operator!=(const Vec4& left, const Vec4& right);

    bool operator<(const Vec4& left, const Vec4& right);
    bool operator<=(const Vec4& left, const Vec4& right);
    bool operator>(const Vec4& left, const Vec4& right);
    bool operator>=(const Vec4& left, const Vec4& right);
}